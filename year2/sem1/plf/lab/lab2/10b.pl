% cmmdc(A:integer, B:integer, Rez:integer)
% (i, i, i), (i, i, o)
cmmdc(A, 0, A) :- !.
cmmdc(A, B, Rez) :-
	C is A mod B,
	cmmdc(B, C, Rez).

% cmmdcAll(L:list, Rez:integer).
% (i, i), (i, o)
cmmdc([], 0) :- !.
cmmdcAll([E], E) :- !.
cmmdcAll([H|T], Rez) :-
	cmmdcAll(T, X),
	cmmdc(H, X, Rez).
