% cmmdc(A:integer, B:integer, Rez:integer)
% (i, i, i), (i, i, o)

cmmdc(A, 0, A) :- !.
cmmdc(A, B, Rez) :-
	B > 0,
	X is mod(A, B), 
	cmmdc(B, X, Rez).


% cmmmc(A:integer, B:integer, Rez:integer)
% (i, i, i), (i, i, o)
cmmmc(A, B, Rez) :-
	cmmdc(A, B, Rez1),
	Rez is A * B / Rez1.

% cmmmcAll(L:list, Rez:integer)
% (i, i), (i, o)

cmmmcAll([H|[]], H) :- !.
cmmmcAll([H|T], Rez) :- 
	cmmmcAll(T, X),
	cmmmc(H, X, Rez).

