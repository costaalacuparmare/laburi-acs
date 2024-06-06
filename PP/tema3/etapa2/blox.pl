:- dynamic detailed_mode_disabled/0.
:- dynamic debug_moves/0.
:- ensure_loaded('files.pl').


% empty_state/1
% empty_state(-SNew)
% Construiește o stare goală (fără nicio informație), care va fi dată
% primului apel set/4
% [Block, Initial_pos, Target, [Tiles], [Fragile], [Switches]]
% Switch - [Pos, Type, Func, [Positions]]
empty_state([_, _, _, [], [], []]).

% coordonata (0, 0) este coltul din stanga/sus (chiar dacă nu există un
% tile acolo)

% set_tile/3
% set_tile(+S, +Pos, -SNew)
% Construiește starea SNew, care conține aceleași informații ca și S
% și în plus faptul că la poziția Pos se află o pătrățică normală.
set_tile([BlockPos, InitPos, Target, Tiles, Fragile, Switches], Pos, [BlockPos, InitPos, Target, [Pos|Tiles], Fragile, Switches]).

% set_blank/3
% set_blank(+S, +Pos, -SNew)
% Construiește starea SNew, care conține aceleași informații ca și S.
% Va fi apelat de tester doar pentru pozițiile fără pătrățele de la
% coordonate unde pentru același x și y mai mare, sau pentru același y
% și x mai mare, există pătrățele. Puteți să nu faceți nimic în acest
% predicat - depinde de cum vă reprezentați intern starea.
set_blank(S, _, S).

% set_target/3
% set_target(+S, +Pos, -SNew)
% Construiește starea SNew, care conține aceleași informații ca și S
% și în plus faptul că la poziția Pos se află gaura (scopul).
set_target([BlockPos, InitPos, _, Tiles, Fragile, Switches], Pos, [BlockPos, InitPos, Pos, Tiles, Fragile, Switches]).

% set_fragile/3
% set_fragile(+S, +Pos, -SNew)
% Construiește starea SNew, care conține aceleași informații ca și S
% și în plus faptul că la poziția Pos se o pătrățică fragilă, pe care
% blocul nu poate sta în picioare.
set_fragile([BlockPos, InitPos, Target, Tiles, Fragile, Switches], Pos, [BlockPos, InitPos, Target, Tiles, [Pos|Fragile], Switches]).

% set_block_initial/3
% set_block_initial(+S, +Pos, -SNew)
% Construiește starea SNew, care conține aceleași informații ca și S
% și în plus faptul că la poziția Pos se află inițial blocul, plasat în
% picioare.
set_block_initial([_, _, Target, Tiles, Fragile, Switches], Pos, [Pos, Pos, Target, Tiles, Fragile, Switches]).


% get_b_pos/2
% get_b_pos(+S, -BlockPos)
% Obtine pozitia sau pozitiile blocului (în funcție de dacă blocul este
% în picioare sau culcat, ca (X, Y) sau ca [(X1, Y1), (X2, Y2)]
get_b_pos([BlockPos, _, _, _, _, _], BlockPos).

% get_bounds/5
% get_bounds(+S, -Xmin, -Xmax, -Ymin, -Ymax).
% Obtine coordonatele limită de pe hartă la care exită celule.
get_bounds(state(Map, _), Xmin, Xmax, Ymin, Ymax) :-
    findall(X, member((X, _, _), Map), Xs),
    findall(Y, member((_, Y, _), Map), Ys),
    min_list(Xs, Xmin),
    max_list(Xs, Xmax),
    min_list(Ys, Ymin),
    max_list(Ys, Ymax).

% get_cell/3
% get_cell(S, Pos, Type).
% Leagă Type la tipul pătrățelei de la poziția Pos. Type trebuie legat
% la:
% tile - pentru o pătrățică obișnuită.
% fragile - pentru o pătrățică fragilă.
% target - pentru scop (gaura).
% oswitch - pentru switch de tip o.
% xswitch - pentru switch de tip x.
%
% Dacă la poziția respectivă nu se află nimic, sau este în afara
% limitelor date de get_bounds, predicatul întoarce false.
get_cell([_, _, (Xtarget, Ytarget), _, _, _], (X, Y), target) :- Xtarget == X, Ytarget == Y.
get_cell([_, (Xtarget, Ytarget), _, _, _, _], (X, Y), tile) :- Xtarget == X, Ytarget == Y.
get_cell([_, _, _, [(X, Y)|_], _, _], (X, Y), tile).
get_cell([_, _, _, _, [(X, Y)|_], _], (X, Y), fragile).
get_cell([_, _, _, _, _, [[(X, Y), Type, _, _]|_]], (X, Y), Type).
get_cell([_, _, T, [_|Rest], Fragile, Switches], (X, Y), Type) :- get_cell([_, _, T, Rest, Fragile, Switches], (X, Y), Type).
get_cell([_, _, T, [], [_|Rest], Switches], (X, Y), Type) :- get_cell([_, _, T, [], Rest, Switches], (X, Y), Type).
get_cell([_, _, T, [], [], [_|Rest]], (X, Y), Type) :- get_cell([_, _, T, [], [], Rest], (X, Y), Type).

% move/3
% move(S, Move, SNext)
% Calculează în SNext starea care rezultă din realizarea mutării Move în
% starea S.
% Mutarea este una dintre d, u, l, r.
% Întoarce false dacă mutarea duce la căderea blocului în vid (nu dacă
% blocul a ajuns la scop).
set_block([_, InitPos, Target, Tiles, Fragile, Switches], BlockPos, [BlockPos, InitPos, Target, Tiles, Fragile, Switches]).
move(S, Dir, SNext) :-
    get_b_pos(S, (X, Y)),
    neighbor((X, Y), Dir, P1),
    neighbor2((X, Y), Dir, P2),
	get_cell(S, P1, _),
	get_cell(S, P2, _),
	set_block(S, [P1, P2], SNext1),
	o_switch(SNext1, [P1, P2], SNext).
move(S, Dir, SNext) :-
    get_b_pos(S, [(X1, Y1), (X2, Y2)]),
    neighbor((X1, Y1), Dir, (X2, Y2)),
    neighbor((X2, Y2), Dir, P),
	get_cell(S, P, _), \+ get_cell(S, P, fragile),
	set_block(S, P, SNext1),
	x_switch(SNext1, P, SNext).
move(S, Dir, SNext) :-
    get_b_pos(S, [(X1, Y1), (X2, Y2)]),
    neighbor((X2, Y2), Dir, (X1, Y1)),
    neighbor((X1, Y1), Dir, P),
	get_cell(S, P, _), \+ get_cell(S, P, fragile),
	set_block(S, P, SNext1),
	x_switch(SNext1, P, SNext).
move(S, Dir, SNext) :-
    get_b_pos(S, [(X1, Y1), (X2, Y2)]),
    \+ neighbor((X1, Y1), Dir, (X2, Y2)), \+ neighbor((X2, Y2), Dir, (X1, Y1)),
	neighbor((X1, Y1), Dir, P1), neighbor((X2, Y2), Dir, P2),
	get_cell(S, P1, _), get_cell(S, P2, _),
	set_block(S, [P1, P2], SNext1),
	o_switch(SNext1, [P1, P2], SNext).

o_switch(S, [P1, P2], SNext) :-
    \+ get_cell(S, P1, oswitch), \+ get_cell(S, P2, oswitch),
    SNext = S.
o_switch(S, [P1, P2], SNext) :-
    get_cell(S, P1, oswitch), get_cell(S, P2, oswitch),
    execute_switch(S, P1, SNext1),
    execute_switch(SNext1, P2, SNext).
o_switch(S, [P1, P2], SNext) :-
    get_cell(S, P1, oswitch), \+ get_cell(S, P2, oswitch),
    execute_switch(S, P1, SNext).
o_switch(S, [P1, P2], SNext) :-
    \+ get_cell(S, P1, oswitch), get_cell(S, P2, oswitch),
    execute_switch(S, P2, SNext).

x_switch(S, P, SNext) :-
    \+ get_cell(S, P, xswitch), \+ get_cell(S, P, oswitch),
    SNext = S.
x_switch(S, P, SNext) :-
    get_cell(S, P, xswitch),
    execute_switch(S, P, SNext).
x_switch(S, P, SNext) :-
    get_cell(S, P, oswitch),
    execute_switch(S, P, SNext).

execute_switch(S, P, SNext) :-
    get_switch(S, P, [_, _, Func, Positions]), Func == uponly,
    activate_tails(S, Positions, SNext).
execute_switch(S, P, SNext) :-
    get_switch(S, P, [_, _, Func, Positions]), Func == dnonly,
    deactivate_tails(S, Positions, SNext).
execute_switch(S, P, SNext) :-
    get_switch(S, P, [_, _, Func, Positions]), Func == switch,
    change_tails(S, Positions, SNext).

get_switch([_, _, _, _, _, []], _, _) :- false.
get_switch([_, _, _, _, _, [[P, Type, Func, Positions]|_]], P, [P, Type, Func, Positions]).
get_switch([_, _, _, _, _, [_|Rest]], P, Switch) :- get_switch([_, _, _, _, _, Rest], P, Switch).

activate_tails(S, [], S).
activate_tails([BlockPos, InitPos, Target, Tiles, Fragile, Switches], [Pos|Rest], SNext) :-
    member(Pos, Tiles), activate_tails([BlockPos, InitPos, Target, Tiles, Fragile, Switches], Rest, SNext).
activate_tails([BlockPos, InitPos, Target, Tiles, Fragile, Switches], [Pos|Rest], SNext) :-
    \+ member(Pos, Tiles), activate_tails([BlockPos, InitPos, Target, [Pos | Tiles], Fragile, Switches], Rest, SNext).

deactivate_tails(S, [], S).
deactivate_tails([BlockPos, InitPos, Target, Tiles, Fragile, Switches], [Pos|Rest], SNext) :-
    member(Pos, Tiles), without(Tiles, Pos, NewTiles),
	deactivate_tails([BlockPos, InitPos, Target, NewTiles, Fragile, Switches], Rest, SNext).
deactivate_tails([BlockPos, InitPos, Target, Tiles, Fragile, Switches], [Pos|Rest], SNext) :-
    \+ member(Pos, Tiles),
    deactivate_tails([BlockPos, InitPos, Target, Tiles, Fragile, Switches], Rest, SNext).

change_tails(S, [], S).
change_tails([BlockPos, InitPos, Target, Tiles, Fragile, Switches], [Pos|Rest], SNext) :-
    member(Pos, Tiles), without(Tiles, Pos, NewTiles),
	change_tails([BlockPos, InitPos, Target, NewTiles, Fragile, Switches], Rest, SNext).
change_tails([BlockPos, InitPos, Target, Tiles, Fragile, Switches], [Pos|Rest], SNext) :-
    \+ member(Pos, Tiles), change_tails([BlockPos, InitPos, Target, [Pos|Tiles], Fragile, Switches], Rest, SNext).

without(Tiles, Pos, NewTiles):-
	findall(X, (member(X, Tiles), \+ X == Pos), NewTiles).

% is_final/1
% is_final(S)
% Întoarce adevărat dacă în starea S blocul este în picioare, pe aceeași
% poziție cu gaura (scopul).
is_final([(X, Y), _, (X, Y), _, _, _]).


%%%%%%%%%% Etapa 2

%% TODO
% set_switch/6
% set_switch(+S, +Pos, +Switch, +Func, +Positions, -SNew)
% Leagă starea SNew la o stare cu aceleași informații ca și S, și în
% plus un switch la poziția Pos, cu parametrii dați.
%
% Switch: oswitch sau xswitch.
% Func: switch, uponly sau dnonly.
% Positions: pozițiile podului.
set_switch([BlockPos, InitPos, Target, Tiles, Fragile, Switches], Pos, Type, Func, Positions, [BlockPos, InitPos, Target, Tiles, Fragile, [[Pos, Type, Func, Positions]|Switches]]).



%% TODO
% solve/2
% solve(+S, -Moves)
% Solve găsește o soluție pentru problema din starea S. Soluția este
% reprezentată ca secvența de mutări Moves.
%
% Pentru a fi soluție, mutările din Moves trebuie să ducă blocul în
% picioare pe poziția scop (target).
solve(S, Moves) :-
	get_b_pos(S, Bpos),
	get_point_target_switches(S, _, Target, _),
	all_points(S, [], AllPoints),
	bfs(Target, AllPoints, AllDistances),
    solve(AllDistances, S, [Bpos], 0, Moves).

solve(_, S, _, _, []) :- is_final(S), !.
solve(AllDistances, S, Visited, ClickedSwitch, [Move|Moves]) :-
	get_point_target_switches(S, Point, Target, Switches),
	directions(Directions),
	sorted_neighbors(AllDistances, Switches, Target, Point, Directions, SortedNeighbors),
	member((_, Move), SortedNeighbors),
    move(S, Move, SNext),
    get_b_pos(SNext, Bpos),
    can_visit(ClickedSwitch, Bpos, Visited),
	view_if_clicked(ClickedSwitch, SNext, Bpos, Visited, NewClickedSwitch),
    solve(AllDistances, SNext, [Bpos|Visited], NewClickedSwitch, Moves).

view_if_clicked(1, _, Bpos, Visited, 0) :- \+ member(Bpos, Visited).
view_if_clicked(1, _, Bpos, Visited, 1) :- member(Bpos, Visited).
view_if_clicked(0, S, Bpos, _, 1) :- on_swich(S, Bpos).
view_if_clicked(0, S, Bpos, _, 0) :- \+ on_swich(S, Bpos).

can_visit(0, Bpos, Visited) :- \+ member(Bpos, Visited).
can_visit(1, Bpos, Visited) :- only_one(Bpos, Visited).

only_one(_, []).
only_one(Elem, [Head|Tail]) :-
    \+ Elem == Head,
    only_one(Elem, Tail).
only_one(Elem, [Elem|Tail]) :-
    \+ member(Elem, Tail).

on_swich(S, (X, Y)) :- get_cell(S, (X, Y), oswitch); get_cell(S, (X, Y), xswitch).
on_swich(S, [P1, P2]) :- on_swich(S, P1); on_swich(S, P2).

get_point_target_switches([BlockPos, _, Target, _, _, Switch], BlockPos, Target, Switch).

sorted_neighbors(AllDistances, [], _, Point, Directions, SortedPairs) :-
	neighbor_distances(AllDistances, Point, Directions, Pairs),
	msort(Pairs, SortedPairs).

sorted_neighbors(_, _, Target, Point, Directions, SortedPairs) :-
	neighbor_distances1(Point, Directions, Target, Pairs),
	msort(Pairs, SortedPairs).

neighbor_distances1(Point, Directions, Target, Pairs) :-
	findall((Dist, Direction), (
		member(Direction, Directions),
		point_med(Point, PoindMed),
		neighbor(PoindMed, Direction, Neighbor),
		distance(Target, Neighbor, Dist)
	), Pairs).

point_med((X, Y), (X, Y)).
point_med([(X, Y), (X1, Y1)], (Xmed, Ymed)) :- Xmed is (X+X1)/2, Ymed = (Y+Y1)/2.

distance((X1, Y1), (X2, Y2), D) :-
	D is sqrt((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2)).

neighbor_distances(AllDistances, Point, Directions, Pairs) :-
	findall((Dist, Direction), (
		member(Direction, Directions),
		(my_neighbor(AllDistances, Point, Direction, Dist);
		Dist is 100)
	), Pairs).

my_neighbor(AllDistances, (X, Y), Direction, Dist) :-
	neighbor((X, Y), Direction, Neighbor),
	member((Neighbor, Dist), AllDistances).

my_neighbor(AllDistances, [P1, P2], Direction, Dist) :-
	neighbor(P1, Direction, Neighbor1),
	neighbor(P2, Direction, Neighbor2),
	P2 == Neighbor1,
	member((Neighbor2, Dist), AllDistances).
my_neighbor(AllDistances, [P1, P2], Direction, Dist) :-
	neighbor(P1, Direction, Neighbor1),
	neighbor(P2, Direction, Neighbor2),
	P1 == Neighbor2,
	member((Neighbor1, Dist), AllDistances).
my_neighbor(AllDistances, [P1, P2], Direction, Dist) :-
	neighbor(P1, Direction, Neighbor1),
	neighbor(P2, Direction, Neighbor2),
	\+ P1 == Neighbor2,
	\+ P2 == Neighbor1,
	member((Neighbor1, Dist1), AllDistances),
	member((Neighbor2, Dist2), AllDistances),
	min(Dist1, Dist2, Dist).

min(X, Y, Min) :- X =< Y -> Min = X ; Min = Y.

bfs(Target, Points, FinalDistances) :-
    bfs_helper([(Target, 0)], Points, [], [(Target, 0)], FinalDistances).

bfs_helper([], _, _, Distances, FinalDistances) :- sort(Distances, FinalDistances).
bfs_helper([(Point, Dist)|Queue], Points, Visited, Distances, FinalDistances) :-
    ( \+ member(Point, Visited) ->
        update_distances(Point, Dist, Points, Visited, NewDistances),
        append(Queue, NewDistances, NewQueue),
		append(Distances, NewDistances, NewDists),
        bfs_helper(NewQueue, Points, [Point|Visited], NewDists, FinalDistances)
    ; bfs_helper(Queue, Points, Visited, Distances, FinalDistances)).

update_distances(Point, Dist, Points, Visited, NewDistances) :-
    findall((Neighbor, NewDist), (
        directions(Directions),
		member(Direction, Directions),
        neighbor(Point, Direction, Neighbor),
        member(Neighbor, Points),
        \+ member(Neighbor, Visited),
        NewDist is Dist + 1
    ), NewDistances).

all_points([_, I, T, Tiles, Fragile, [[Pos, _, _, Positions]|Rest]], Points, L) :-
	append(Points, Positions, NewPoints),
	all_points([_, I, T, Tiles, Fragile, Rest], [Pos|NewPoints], L).
all_points([_, I, T, Tiles, [Pos|Rest], []], Points, L) :- all_points([_, I, T, Tiles, Rest, []], [Pos|Points], L).
all_points([_, I, T, [Pos|Rest], [], []], Points, L) :- all_points([_, I, T, Rest, [], []], [Pos|Points], L).
all_points([_, I, T, [], [], []], Points, [I,T|Points]).
