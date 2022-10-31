% numar(L:list, E:element, N:intreg)
% list=Element*
% (i, i, i), (i, i, o)

numar([], _, 0).
numar([H|T], E, N) :-
	H = E,
	!,
	numar(T, E, N1),
	N is N1 + 1.
numar([_|T], E, N) :-
	numar(T, E, N).

% eliminare(L:list, E:element, Rez:list)
% list=element*
% (i, i, i), (i, i, o)

eliminare([], _, []).
eliminare([H|T], E, [H|Rez]) :-
	H \= E,
	!,
	eliminare(T, E, Rez).
eliminare([_|T], E, Rez) :-
	eliminare(T, E, Rez).

% perechi(L:list, Rez:lista)
% list=Element*
% lista=list*
% (i, i), (i, o)

perechi([], []).
perechi([H|T], Rez) :-
	numar([H|T], H, Nr),
	eliminare(T, H, T1),
	perechi(T1, Rez1),
	Rez = [[H, Nr]|Rez1].

