%diferenta a doua multimi


%apare(El - element, L - lista)
%verifica daca apare elementul in lista

apare(El, [El|_]):- !.

apare(El, [_|T]):-
      apare(El, T).

%diferenta(L1 - lista, L2 - lista, Rez - lista)
%face diferenta dintre 2 liste si o pune in Rez
%model de flux: (i,i,o), (i,i,i)

diferenta([], _, []).

diferenta([H|T], L2, Rez):-
	apare(H, L2), !,
	diferenta(T, L2, Rez).

diferenta([H|T], L2, [H|Rez]):-
	diferenta(T, L2, Rez).


%adauga1(L - lista, Rez - lista)
%adauga in lista dupa fiecare valoare para valoarea 1

adauga1([], []).

adauga1([H|T], [H|Rez]):-
	H mod 2 =:= 1, !,
	adauga1(T, Rez).

adauga1([H|T], [H,1|Rez]):-
	adauga1(T, Rez).

% elimina_k_aparitii(El - element, L - lista, Rez - lista, Cnt -
% aparitii) elimina primele 3 aparitii ale elementului

elimina_k_aparitii(_, [], [], _).

elimina_k_aparitii(El, [H|T], [H|Rez], Cnt):-
        H \= El, !,  % OPERATORUL INSEAMNA CA NU POT FI UNIFICATE
	elimina_k_aparitii(El, T, Rez, Cnt).

elimina_k_aparitii(El, [El|T], [El|Rez], Cnt):-
	Cnt =:= 0, !,
	elimina_k_aparitii(El, T, Rez, Cnt).

elimina_k_aparitii(El, [El|T], Rez, Cnt):-
	Cnt_Nou is Cnt - 1,
	elimina_k_aparitii(El, T, Rez, Cnt_Nou).

elimina_3_aparitii(El, L, Rez):-
	elimina_k_aparitii(El, L, Rez, 3), !.

%toate_apar(L1 - lista, L2 - lista)

toate_apar([], _).

toate_apar([H|T], L2):-
	apare(H, L2),
	toate_apar(T, L2).

%multimi_egale(L1 - lista, L2 - lista)
%verifica egalitatea a doua multimi

multimi_egale(L1, L2):-
	toate_apar(L1, L2),
	toate_apar(L2, L1).


%insereaza(El - element, L - lista, Rez - lista)
%insereaza elementul pe pozitia potrivita in L sortata!!!

insereaza(El, [], [El]):- !.

insereaza(El, [H|T], [H|Rez]):-
	El > H, !,  %daca nu e pe pozitia buna, mergem mai departe
	insereaza(El, T, Rez).

insereaza(El, [H|T], [El,H|T]):-
	El < H, !.  %daca e pe pozitia buna, inseram El si oprim bcktrck

insereaza(El, [H|T], [H|T]):-
	El = H, !.  %NECESAR PENTRU ELIMINAREA DUBLURILOR

%sorteaza(L - lista, Rez - lista)
%sorteaza o lista CU ELIMINAREA DUBLURILOR

sorteaza([], []):- !.

sorteaza([H|T], Rez):-
	sorteaza(T, TSortat),
	insereaza(H, TSortat, Rez).


%oglindit(L - lista, Acc - lista, Rez - lista)

oglindit([], Acc, Acc):- !.

oglindit([H|T], Acc, Rez):-
	oglindit(T, [H|Acc], Rez).

oglindit_main(L, Rez):-
	oglindit(L, [], Rez).

% produs_lista(L - lista inversata, Rez - rezultat inversat, Nr - numar
% natural, Carry - carry)

produs_lista(_, [0], 0, _):- !.

produs_lista([], [], _, 0):- !.  %cand lista e vida si n-avem carry

produs_lista([], [Carry], _, Carry):-
	Carry > 0, !.  %cand ajungem la final si inca avem carry

produs_lista([H|T], [R|RezT], Nr, Carry):-
	Prod is H * Nr + Carry,
	R is Prod mod 10,  %cifra pe care o adaugam la produs
	CarryNou is Prod // 10,
	produs_lista(T, RezT, Nr, CarryNou).


produs_lista_main(L, Nr, Rez):-
	oglindit_main(L, L_inversata),
	produs_lista(L_inversata, Rez_inversat, Nr, 0),
	oglindit_main(Rez_inversat, Rez).


% inloc(L1 - lista, El - element, L2 - lista cu elementele de inlocuit,
% Rez - lista rezultata)
% inlocuieste aparitiile lui El cu elementele lui L2

inloc([], _, _, []).

inloc([H|T], El, L2, Rez):-
	H = El, !,
	inloc(T, El, L2, RezT),
	append(L2, RezT, Rez).

inloc([H|T], El, L2, [H|Rez]):-
	inloc(T, El, L2, Rez).

%elimin dublurile

elimina_dubluri([], []):- !.

elimina_dubluri([H|T], Rez):-
	apare(H, T), !,
	elimina_dubluri(T, Rez).

elimina_dubluri([H|T], [H|Rez]):-
	elimina_dubluri(T, Rez).

%interclasare(L1 - lista, L2 - lista, Rez - lista)
%interclaseaza 2 liste sortate fara pastrarea dublurilor

interclasare([], L2, L2):- !.

interclasare(L1, [], L1):- !.

interclasare([H1|T1], [H2|T2], [H1|Rez]):-
	H1 < H2, !,
	interclasare(T1, [H2|T2], Rez).

interclasare([H1|T1], [H2|T2], [H2|Rez]):-
	H1 > H2, !,
	interclasare([H1|T1], T2, Rez).

interclasare([H1|T1], [H2|T2], Rez):-
	H1 = H2, !,
	interclasare(T1, T2, Rez).

interclasare_fara_dubluri(L1, L2, Rez):-
	elimina_dubluri(L1, L1_Nou),
	elimina_dubluri(L2, L2_Nou),
	interclasare(L1_Nou, L2_Nou, Rez).



















