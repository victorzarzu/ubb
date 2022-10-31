% sterge(L:list, E:element, Rez:List)
% (i, i, i), (i, i, o)
sterge([], _, []).
sterge([E|T], E, Rez) :-
	!,
	sterge(T, E, Rez).
sterge([H|T], E, [H|Rez]) :- 
	!,
	sterge(T, E, Rez).

% multime(L:list, Rez:list)
% (i, i), (i, o)

multime([], []).
multime([H|T], [H|Rez]) :-
	sterge(T, H, X),
	multime(X, Rez).
