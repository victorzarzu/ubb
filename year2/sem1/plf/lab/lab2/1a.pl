% exista(E:element, L:list)
% list=Element*
% (i, i), (i, o)
% L - lista in care se verifica daca exista E
% E - elementul care se verifica ca este in lista L

exista(E, [E|_]) :- !.
exista(E, [_|L]) :- exista(E, L).

% diff(L1:list, L2:list, Rez:list)
% list=Element*
% (i, i, i), (i, i, o)
% L1, L2 - multimile pe care se face operatia diferenta
% Rez - multimea rezultata in urma diferentei

diff([], _, []).
diff([H|T1], L2, [H|Rez]) :-
	not(exista(H, L2)),
	!,
	diff(T1, L2, Rez).
diff([_|T], L2, Rez) :-
	diff(T, L2, Rez).
