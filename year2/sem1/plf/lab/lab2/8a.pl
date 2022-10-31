% exista(L:list, E:element)
% list=element*
% (i, i), (i, o)
exista([E|_], E) :- !.
exista([_|T], E) :- exista(T, E).

% multime(L:list)
% list=element*
% (i)
multime([]).
multime([H|T]) :-
	\+ exista(T, H),
	multime(T).
