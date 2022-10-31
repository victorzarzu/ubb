% lista(M:integer, N:integer, L:list)
% list=integer*
% (i, i, i), (i, i, o)
lista(M, N, []) :-
	M > N,
	!.
lista(N, N, [N]) :- !.
lista(M, N, [M|Rez]) :-
	M1 is M + 1,
	lista(M1, N, Rez).
