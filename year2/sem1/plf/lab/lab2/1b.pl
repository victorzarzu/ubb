% adaugDupaPar(L:list, Rez:list)
% list=Integer*
% (i, i), (i, o)
% L - lista in care se adauga 1 dupa fiecare element par
% Rez - lista rezultata prin adaugarea unui 1 dupa fiecare element par

adaugDupaPar([], []).
adaugDupaPar([H|T], [H, 1|Rez]) :-
	number(H),
	H mod 2 =:= 0,
	!,
	adaugDupaPar(T, Rez).
adaugDupaPar([H|T], [H|Rez]) :-
	adaugDupaPar(T, Rez).
