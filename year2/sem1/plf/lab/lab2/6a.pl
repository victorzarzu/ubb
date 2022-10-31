% exista(L:list, E:element)
% list=element*
% (i, i)
% L - lista in care se vede daca apare E.
% E - elementul care este verificat daca exista in lista L

exista([E|_], E) :- !.
exista([_|T], E) :- exista(T, E).

% eliminare(L:list, E:element, Rez:list)
% list=element*
% (i, i, i), (i, i, o)

eliminare([], _, []).
eliminare([H|T], E, [H|Rez]) :-
	H \= E,
	!,
	eliminare(T, E, Rez).
eliminare([_|T], E, Rez) :-
	eliminare(T, E, Rez).


% eliminareDuplicate(L:list, Rez:list)
% list=element*
% (i, i), (i, o)
% L - lista din care se elimina elementele care apar de mai multe ori
% Rez - lista rezultata prin eliminarea elementelor care apar de mai multe ori

eliminareDuplicate([], []).
eliminareDuplicate([H|T], [H|Rez]) :-
	\+ exista(T, H),
	!,
	eliminareDuplicate(T, Rez).
eliminareDuplicate([H|T], Rez) :-
	eliminare(T, H, T1),
	eliminareDuplicate(T1, Rez).
