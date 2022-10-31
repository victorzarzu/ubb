fact_o(N, V, F, N) :- 
	V = F,
	!.
fact_o(N, V, F, Rez) :-
	V < F,
	N1 is N + 1,
	V1 is V * N1,
	fact_o(N1, V1, F, Rez).

fact_i(N, N, 1) :- !.
fact_i(N, I, F) :-
	I1 is I + 1,
	fact_i(N, I1, F1),
	F is F1 * I1.

% fact(N:integer, F:integer)
% (i, i), (i, o), (o, i)
fact(N, F) :-
	var(F),
	!,
	fact_i(N, 1, F).
fact(N, F) :-
	fact_o(1, 1, F, N).
