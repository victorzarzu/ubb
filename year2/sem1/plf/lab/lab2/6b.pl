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

% max(E1:integer, E2:integer, M:integer)
% (i, i, i), (i, i, o)
max(E1, E2, E1) :- 
	E1 > E2,
	!.
max(E1, E2, E2) :- 
	E2 >= E1.

% maxim(L:list, M:element)
% list=integer*
% (i, i), (i, o)
% L - lista pentru care se determina elementul maxim
% M - maximul din lista L

maxim([H|[]], H) :- !.
maxim([H|T], M) :-
	maxim(T, M1),
	max(H, M1, M2),
	M = M2.

% eliminareMax(L:list, Rez:list)
% list=integer*
% (i, i), (i, o)
eliminareMax(L, Rez) :-
	maxim(L, M),
	eliminare(L, M, Rez).
