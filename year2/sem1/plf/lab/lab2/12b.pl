% sublistaM(L:list, M:integer, Rez:list)
%	list=element*
% (i, i, i), (i, i, o)
sublista([], _, []) :- !.
sublista(L, 1, L) :- !.
sublista(L, M, L) :-
	M =< 0,
	!.
sublista([_|T], M, Rez) :-
	M1 is M - 1,
	sublista(T, M1, Rez).
