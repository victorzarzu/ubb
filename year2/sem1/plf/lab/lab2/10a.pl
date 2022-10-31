% insereaza(L:list, N:integer, E:element, Rez:list)
% list=element*
% (i, i, i, i), (i, i, i, o)
insereaza(L, N, _, L) :-
	N =< 0,
	!.
insereaza(L, 1, E, [E|L]) :- !.
insereaza([], _, _, []) :- !.
insereaza([H|T], N, E, [H|Rez]) :-
	N1 is N - 1,
	insereaza(T, N1, E, Rez).
