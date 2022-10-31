% vale_aux(L:list, F:integer)
% list=integer*
% (i, i)
% vale_aux([], _) :- !.
vale_aux([_], _) :- !.
vale_aux([H1, H2|T], 0) :-
	H1 > H2,
	!,
	vale_aux([H2|T], 0).
vale_aux([H1, H2|T], 0) :-
	H1 < H2,
	!,
	vale_aux([H2|T], 1).
vale_aux([H1, H2|T], 1) :-
	H1 < H2,
	!,
	vale_aux([H2|T], 1).

% vale(L:list)
% list=integer*
% (i)
vale(L) :- vale_aux(L, 0).
