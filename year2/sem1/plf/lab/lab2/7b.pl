% pereche(L:list, E:element, P:list).
% list=element*
% (i, i, o), (i, i, i)
pereche([H|T], E, [H, E]).
pereche([H|_], E, P).

% perechi(L:list, Rez:list)
