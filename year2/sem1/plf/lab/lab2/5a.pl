% elimin(L:list, E:element, Rez:list).
% (i, i, i), (i, i, o)

elimin([], _, []) :- !.
elimin([H|T], E, Rez) :- 
	H == E,
	!,
	elimin(T, E, Rez).
elimin([H|T], E, [H|Rez]) :-
	elimin(T, E, Rez).
