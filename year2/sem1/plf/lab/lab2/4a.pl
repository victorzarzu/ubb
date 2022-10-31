% subst(L:list, E:element, P:list, Rez:list)
% (i, i, i, i), (i, i, i, o)

subst([], _, _, []).
subst([H|T], E, P, [P|Rez]) :- 
	E == H,
	!,
	subst(T, E, P, Rez).
subst([H|T], E, P, [H|Rez]) :-
	subst(T, E, P, Rez).
