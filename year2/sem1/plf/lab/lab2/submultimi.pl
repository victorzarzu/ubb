% submultimi(L:list, Rez:list)

submultimi(L, Rez) :-
	submultimi_aux(L, [], []).

submultimi_aux([], Sub, [Sub|Rez]) :- !.
submultimi_aux([H|T], Sub, Rez) :-
	submulitimi_aux(T, [H|Sub], Rez).
submultimi_aux([H|T], Sub, Rez) :-
	submultimi_aux(T, Sub, Rez).
