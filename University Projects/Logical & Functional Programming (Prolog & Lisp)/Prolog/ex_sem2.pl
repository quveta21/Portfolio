% seminar 2

%nr_aparitii(El - element, L - lista, N - int)
nr_aparitii(El, [H|T], N):-
    El=H, !,
    nr_aparitii(El, T, Rez),
    N is Rez + 1.
    
nr_aparitii(El, [], 0).

nr_aparitii(El, [H|T], N):-
    El\=H,
    nr_aparitii(El, T, N).
    
% elimina(L - lista, LI - lista, Rez - lista)
elimina([], _, []).

elimina([H|T], LI, Rez):-
    nr_aparitii(H, LI, N),
    N>1, !,
    elimina(T, LI, RezT),
    Rez = [H|RezT].
    
elimina([H|T], LI, Rez):-
    elimina(T, LI, Rez).
    
% model de flux: (i, o), (i, i)
elimina_principal(L, Rez):-
    elimina(L, L, Rez).
    
    
% elimSecv(L - lista, F - int, Rez - lista)
elimSecv([], _, []).
elimSecv([H], 0, [H]).
elimSecv([H], 1, []).
elimSecv([H1,H2|T], F, Rez):-
    H1 < H2,
    elimSecv([H2|T], 1, Rez).
elimSecv([H1,H2|T], 1, Rez):-
    H1 >= H2,
    elimSecv([H2|T], 0, Rez).
elimSecv([H1,H2|T], 0, Rez),
    H1 >= H2,
    elimSecv([H2|T], 0, RezT),
    Rez = [H1|RezT].
    
elimSecvPrincipal(L, Rez):-
    elimSecv(L, 0, Rez).