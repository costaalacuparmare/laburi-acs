#!/usr/bin/env python3

import hlt
from hlt import STILL, Move
from collections import defaultdict, deque

myID, game_map = hlt.get_init()

# Constants
potential_degradation_step = 0.5
players = game_map.starting_player_count
alpha = 0.15 + players * 0.1

hlt.send_init("Johnny_Bravo")


# Calculate the best move for a square based on potential
def calculate_best_move(square):
    valid_moves = [(direction, neighbor_square) for direction, neighbor_square in enumerate(game_map.neighbors(square))]
    potential_moves = []

    # Calculate potential for each valid move
    for direction, neighbor_square in valid_moves:
        # Calculate strength of the neighbor square if the current square moves there
        strength_with_dest = square.strength + destinations.get(neighbor_square, 0)

        # Calculate potential of the neighbor square based on the potential map
        potential = pf_map[neighbor_square] + (float('inf') if strength_with_dest > 255 else 0)

        # Append the potential move to the list
        potential_moves.append((potential, direction, neighbor_square))

    # Return the move with the highest potential
    return min(potential_moves)


# Check if staying is bad based on the square's potential and distance
def is_staying_bad(square):
    return (square.strength + square.production + destinations.get(square, 0)) > 255


# Handle staying decisions

# If staying is bad, move to the neighbor with the highest potential
def handle_staying_bad(square, best_move):
    if any(destinations[neighbor_square] + square.strength < 256 for _, neighbor_square in originations[square]):
        return Move(square, min(originations[square], key=lambda tup: destinations[tup[1]])[0])
    else:
        return Move(square, best_move[1])


# If staying is good, stay if the square is strong enough or move to the neighbor with the highest potential
def handle_staying_good(square, best_move):
    target_square = best_move[2]

    if target_square.owner != myID:
        if square.strength == 255 or square.strength > target_square.strength:
            return Move(square, best_move[1])
    elif square.strength >= square.production * 10:
        return Move(square, best_move[1])

    return Move(square, STILL)


def assign_move(square):
    # Calculate potential moves and find the best one
    best_move = calculate_best_move(square)

    # Check staying conditions
    staying_is_bad = is_staying_bad(square)

    # Handle staying decisions
    if staying_is_bad:
        return handle_staying_bad(square, best_move)
    else:
        return handle_staying_good(square, best_move)


# Calculate square value based on strength and production
def square_value(square):
    if square.production == 0:
        if players == 1:
            # used for 1 player games so that it doesn't ignore 0 production squares
            return 0
        else:
            return float('inf')
    else:
        # determine potential based on this formula
        return square.strength / square.production


# Calculate initial potential for a square based on its owner and strength
def initial_potential(square):
    if square.owner == square.strength == 0:
        # if the square is neutral and has no strength, return negative value based on the number of enemies
        return -len([neigh for neigh in game_map.neighbors(square) if (neigh.owner != 0 and neigh.owner != myID)])
    return square_value(square)


# Task class to keep track of potential calculations
class Task:
    def __init__(self, potential, init_potential, distance, square):
        self.potential = potential
        self.initial_potential = init_potential
        self.distance = distance
        self.square = square


turn = 0

# Game loop
while True:
    # basic logging

    # moves = number of moves made in the current turn
    # border = number of squares on the border of the map, which is a queue
    # pf_map = number of squares in the potential map, which is a dictionary

    turn += 1
    moves = []
    game_map.get_frame()
    border = deque([Task(initial_potential(square), initial_potential(square), 0, square)
                    for square in game_map if square.owner != myID])
    pf_map = dict()

    # Calculate potential map
    while len(pf_map) < game_map.width * game_map.height and border:
        # pop the leftmost element from the queue
        task = border.popleft()
        square = task.square
        # if the square is not in the potential map, calculate its potential
        if square not in pf_map:
            pf_map[square] = ((1 - alpha) * task.initial_potential + alpha * potential_degradation_step *
                              task.distance ** 2)
            for neighbor in game_map.neighbors(square):
                # if the neighbor is owned by myID, calculate potential with initial potential and square value
                if neighbor.owner != myID:
                    neighbor_potential = (1 - alpha) * task.initial_potential + alpha * square_value(neighbor)
                    border.append(Task(neighbor_potential, neighbor_potential, task.distance, neighbor))
                # if the neighbor is not owned by myID, calculate potential with the potential degradation step
                else:
                    neighbor_potential = task.initial_potential + potential_degradation_step * (task.distance + 1) ** 2
                    border.append(Task(neighbor_potential, task.initial_potential, task.distance + 1, neighbor))

    # Calculate moves

    # destinations = dictionary of destinations and their strength
    destinations = defaultdict(int)

    # originations = dictionary of originations and their direction and square
    originations = defaultdict(list)

    # my_squares = squares owned by myID
    my_squares = (square for square in game_map if square.owner == myID and square.strength > 0)

    # sorted_by_strength = squares sorted by strength
    sorted_by_strength = sorted(my_squares, key=lambda square: square.strength, reverse=True)

    # assign the move for each square in sorted_by_strength
    for square in sorted_by_strength:
        move = assign_move(square)
        moves.append(move)
        target = game_map.get_target(square, move.direction)
        destinations[target] += square.strength
        originations[target].append((hlt.opposite_cardinal(move.direction), square))

    # Send moves
    hlt.send_frame(moves)
