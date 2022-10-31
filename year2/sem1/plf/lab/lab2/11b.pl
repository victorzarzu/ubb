% alter_sum(L:list, S:integer).
% L=integer*
% (i, i), (i, o)
alter_sum(L, S) :- aux_alter_sum(L, 1, S).

% alter_sum(L:list, Semn:integer, S:integer).
% L=integer*
% (i, i, i), (i, i, o)
aux_alter_sum([], _, 0) :- !.
aux_alter_sum([H|T], Semn, S) :-
	Semn1 is Semn * -1,
	aux_alter_sum(T, Semn1, S1),
	S is H * Semn + S1.
