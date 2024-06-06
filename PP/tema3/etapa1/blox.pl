:- dynamic detailed_mode_disabled/0.
:- dynamic debug_moves/0.
:- ensure_loaded('files.pl').


% empty_state/1
% empty_state(-SNew)
% Construiește o stare goală (fără nicio informație), care va fi dată
% primului apel set/4
empty_state(state([], _)).

% coordonata (0, 0) este coltul din stanga/sus (chiar dacă nu există un
% tile acolo)

% Folositoare pentru updatarea hartii
update_map([], (X, Y), Type, [(X, Y, Type)]).
update_map([H | T], Pos, Type, [H | NewT]) :-
    H \= (Pos, _),
    update_map(T, Pos, Type, NewT).

% set_tile/3
% set_tile(+S, +Pos, -SNew)
% Construiește starea SNew, care conține aceleași informații ca și S
% și în plus faptul că la poziția Pos se află o pătrățică normală.
set_tile(state(Map, BlockPos), Pos, state(NewMap, BlockPos)) :-
    update_map(Map, Pos, tile, NewMap).

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
set_target(state(Map, BlockPos), Pos, state(NewMap, BlockPos)) :-
    update_map(Map, Pos, target, NewMap).

% set_fragile/3
% set_fragile(+S, +Pos, -SNew)
% Construiește starea SNew, care conține aceleași informații ca și S
% și în plus faptul că la poziția Pos se o pătrățică fragilă, pe care
% blocul nu poate sta în picioare.
set_fragile(state(Map, BlockPos), Pos, state(NewMap, BlockPos)) :-
    update_map(Map, Pos, fragile, NewMap).

% set_block_initial/3
% set_block_initial(+S, +Pos, -SNew)
% Construiește starea SNew, care conține aceleași informații ca și S
% și în plus faptul că la poziția Pos se află inițial blocul, plasat în
% picioare.
set_block_initial(state(Map, _), Pos, state(NewMap, Pos)) :-
    update_map(Map, Pos, tile, NewMap).


% get_b_pos/2
% get_b_pos(+S, -BlockPos)
% Obtine pozitia sau pozitiile blocului (în funcție de dacă blocul este
% în picioare sau culcat, ca (X, Y) sau ca [(X1, Y1), (X2, Y2)]
get_b_pos(state(_, BlockPos), BlockPos).

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
get_cell(_S, (_X, _Y), _) :- false.
get_cell(state(Map, _), (X, Y), Type) :-
    member((X, Y, Type), Map).

% move/3
% move(S, Move, SNext)
% Calculează în SNext starea care rezultă din realizarea mutării Move în
% starea S.
% Mutarea este una dintre d, u, l, r.
% Întoarce false dacă mutarea duce la căderea blocului în vid (nu dacă
% blocul a ajuns la scop).
set_block(state(Map, _), BlockPos, state(Map, BlockPos)).
move(S, Move, SNext) :-
    get_b_pos(S, Pos),
    neighbor(Pos, Move, NeighPos1),
    neighbor2(Pos, Move, NeighPos2),
	get_cell(S, NeighPos1, _),
	get_cell(S, NeighPos2, _),
	set_block(S, [NeighPos1, NeighPos2], SNext).
move(S, Move, SNext) :-
    get_b_pos(S, [(X1, Y1), (X2, Y2)]),
    neighbor((X1, Y1), Move, (X2, Y2)),
    neighbor((X2, Y2), Move, NeighPos),
	get_cell(S, NeighPos, _), \+ get_cell(S, NeighPos, fragile),
	set_block(S, NeighPos, SNext).
move(S, Move, SNext) :-
    get_b_pos(S, [(X1, Y1), (X2, Y2)]),
    neighbor((X2, Y2), Move, (X1, Y1)),
    neighbor((X1, Y1), Move, NeighPos),
	get_cell(S, NeighPos, _), \+ get_cell(S, NeighPos, fragile),
	set_block(S, NeighPos, SNext).
move(S, Move, SNext) :-
    get_b_pos(S, [(X1, Y1), (X2, Y2)]),
    \+ neighbor((X1, Y1), Move, (X2, Y2)),
    \+ neighbor((X2, Y2), Move, (X1, Y1)),
	neighbor((X1, Y1), Move, NeighPos1),
	neighbor((X2, Y2), Move, NeighPos2),
	get_cell(S, NeighPos1, _),
	get_cell(S, NeighPos2, _),
	set_block(S, [NeighPos1, NeighPos2], SNext).

% is_final/1
% is_final(S)
% Întoarce adevărat dacă în starea S blocul este în picioare, pe aceeași
% poziție cu gaura (scopul).
is_final(state(_, Pos)) :-
    get_cell(state(_, _), Pos, target).

% pentru etapa 2
% set_switch(+S, +Pos, +Switch, +Func, +Positions, SOut)
% Switch: o sau x
% Func: switch, uponly sau dnonly
% Position: pozitiile podului
set_switch(S, P, _, _, _, SNew) :- set_tile(S, P, SNew).
