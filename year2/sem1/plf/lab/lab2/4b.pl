% elim(L:list, N:integer, Rez:list).
% (i, i, i), (i, i, o)

elim([], _, []) :- !.
elim([_|T], 1, T) :- !.
elim([H|T], N, [H|Rez]) :-
	N1 is N-1,
	elim(T, N1, Rez).
