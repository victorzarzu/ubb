% put2(X:integer)
% (i)

put2(1) :- !.
put2(X) :- 
	X mod 2 =:= 0,
	!,
	Y is X / 2,
	put2(Y).

% adauga(L:list, E:element, Rez:list).
% (i, i), (i, o)
adauga(L, E, Rez) :- adauga_aux(L, E, 1, Rez).

% adauga_aux(L:list, E:element, I:integer, Rez:list).
% (i, i, i), (i, i, o)
adauga_aux([], _, _, []) :- !.
adauga_aux([H|T], E, I, [H,E|Rez]) :-
	put2(I),
	!,
	J is I + 1,
	adauga_aux(T, E, J, Rez).
adauga_aux([H|T], E, I, [H|Rez]) :-
	J is I + 1,
	adauga_aux(T, E, J, Rez).
