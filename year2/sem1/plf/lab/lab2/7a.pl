% eliminare(L:list, E:element, Rez:list)
% list=element*
% (i, i, i), (i, i, o)
eliminare([], _, []).
eliminare([E|T], E, Rez) :-
	!,
	eliminare(T, E, Rez).
eliminare([H|T], E, [H|Rez]) :-
	eliminare(T, E, Rez).

% reuniune(L1:list, L2:list, Rez:list)
% list=element*
% (i, i, i), (i, i, o)
reuniune(L1, [], L1) :- !.
reuniune([], L2, L2) :- !.
reuniune([H1|T1], [H2|T2], [H1|Rez]) :-
	H1 =< H2,
	!,
	eliminare([H2|T2], H1, T21),
	reuniune(T1, T21, Rez).
reuniune([H1|T1], [H2|T2], [H2|Rez]) :-
	eliminare([H1|T1], H2, T11),
	reuniune(T11, T2, Rez).
