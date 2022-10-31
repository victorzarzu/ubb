% candidat(N:integer, Rez:integer)
% (i, o)
candidat(N, N).
candidat(N, Rez) :-
	N > 1,
	N1 is N - 1,
	candidat(N1, Rez).

% inserare(L:list, E:element, Rez:list)
% (i, i, o)
inserare(L, E, [E|L]).
inserare([H|T], E, [H|Rez]) :-
	inserare(T, E, Rez).

% perm_aux(N:integer, Lg:integer, L:list)
% (i, o)
perm_aux(N, N, L).
perm_aux(N, Lg, P) :-
	Lg < N,
	Lg1 is Lg + 1,
	candidat(N, X),
	inserare(E, L, P).
