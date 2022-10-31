% eliminan(L:list, E:element, N:integer, Rez:list)
% list=element*
% (i, i, i, i), (i, i, i, o)

eliminan(L, _, 0, L) :- !.
eliminan([], _, _, []).
eliminan([E|T], E, N, Rez) :-
	!,
	N1 is N - 1,
	eliminan(T, E, N1, Rez).
eliminan([H|T], E, N, [H|Rez]) :-
	eliminan(T, E, N, Rez).

% elimina3(L:list, E:element, Rez:list)
% list=element*
% (i, i, i), (i, i, o)
elimina3(L, E, Rez) :-
	eliminan(L, E, 3, Rez).
