% adaugaSf(List:list, E:element, Rez:list)
% (i, i, i), (i, i, o)

adaugaSf([], E, [E]).
adaugaSf([H|T], E, [H|Rez]) :-
	adaugaSf(T, E, Rez).

% descompunere(L:list, Rez:list, Pare:integer, Impare:integer).
% (i, i, i, i), (i, o, o, o).

descompunere([], [], 0, 0).
descompunere([H|T], [H|Rez], Pare, Impare) :-
	H mod 2 =:= 0,
	!,
	descompunere(T, Rez, PareRec, Impare),
	Pare is PareRec + 1.
descompunere([H|T], Rez, Pare, Impare) :-
	descompunere(T, X, Pare, ImpareRec),
	adaugaSf(X, H, Rez),
	Impare is ImpareRec + 1.
