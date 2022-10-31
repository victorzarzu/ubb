% exista(L:list, E:element)
% list=element*
% (i, i)
exista([E|_], E) :- !.
exista([_|T], E) :-
	exista(T, E).

% intersectie(L1:list, L2:element, Rez:list)
% list=element*
% (i, i, i), (i, i, o)
intersectie([], _, []).
intersectie([H|T], L2, [H|Rez]) :-
	exista(L2, H),
	!,
	intersectie(T, L2, Rez).
intersectie([_|T], L2, Rez) :-
	intersectie(T, L2, Rez).
