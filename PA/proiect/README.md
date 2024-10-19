# Halite Project - Made for Algorithmic Design

### Constantinescu Vlad, Oprea George, Miclius Razvan

The archive contains:

- `utils` - framework provided by the faculty and the halite GitHub repository
- `hlt.py` - the halite functions pre implemented
- `MyBot.py` - the implementation of the bot that solves the challenge
- `run_local.sh` - personally written script that opens the game the bot/ bots are playing with the specified details
of the board
- `Makefile` - cleans cache and creates the archive
- `README.md` - the readme file

## Tasks and Implementation Details
- The purpose of the bot is to ocupy the whole territory of the map
- In a multiple bots match, the purpose is to eliminate the other boss
- Those tasks are accomplished occupying tiles based on potential, which is
a ratio between the strength value of the square and the production
- Main game loop initializes the map and enters a while True with the main game logic
- A while determines a potential map, determine the best moves for each tile across the whole map
- For each possible neighbouring case: owned or not owned tile, two formulas are applied
- NOT owned: neighbor_potential = (1 - alpha) * task.initial_potential + alpha * square_value(neighbor)
Here, alpha is a weighting factor that balances the importance of the initial potential and the current value of the
neighboring tile (calculated by square_value). This formula is designed to prioritize tiles that can be captured without
straying too far from the bot's established strategy.
- owned: neighbor_potential = task.initial_potential + potential_degradation_step * (task.distance + 1) ** 2
The formula incorporates a potential degradation based on the distance from the original square. This reflects that the
farther away the tile is, the less effective it becomes. The (task.distance + 1) ** 2 shows that as distance increases
the degradation in potential becomes significantly stronger, discouraging moving too far
- The differentiation in how owned vs. unowned neighbors are treated allows the bot to be aggressive in capturing enemy
tiles while also considering the risks of moving into less advantageous positions. This reflects a balance between
expansion and maintaining control over the territory already owned.

## Functions

- `calculate_best_move`: determines the best move for a tile by taking each valid mode
and determines the strength it would achieve after moving there, the potential
and returns the move with the highest potential

- `is_staying_bad`: implemented so that most owned tiles would advance, given that during
development certain tiles would stagnate even if better moves were possible

- `handle_staying_bad`: if the previous functions proves correctly, the square
moves to the neighbour with the highest potential, checking by distance to the border of the map

- `handle_staying_good`: checks if the next best move is an alternative, if it is
moves to the first best move, if not, checks if the strength of the owned tile is considerably
larger than the production, indicating it is strong enough to risk and move. If all else fails
it stays still

- `assign_move`: Integrates all the previous functions in a general move assignment

- `square_value`: determines the potential and depending on the game type indicates the potential
as infinite for no production tiles

- `initial_potential`: most useful in games against bots, prioritises enemy tiles over
neutral ones to increase aggressiveness, otherwise assigns the value determined by previous function