%lab_p2

%Sa se sorteze o lista cu eliminarea dublurilor
% Se da o lista eterogena, formata din numere intregi si liste de
% numere. Sa se sorteze fiecare sublista fara pastrarea dublurilor

%a
%-----------------------------------------
%apare(El - element, L - lista)
%model de flux: (i,o), (o,i)

apare(El, [El|_]):- !. %daca gaseste El se opreste recursivitatea

apare(El, [_|T]):-
    apare(El, T). %daca nu il gaseste, continua cautarea cu restul listei
%-----------------------------------------
%multime(L - lista, Rez - lista)
%elimina dublurile dintr-o lista => o transforma in multime
%model de flux: (i,o)

multime([], []).  %daca lista e vida, rezultatul e vid

multime([H|T], Rez):-
    apare(H, T), !,
    multime(T, Rez). %daca mai apare elementul, il ignoram si continuam

multime([H|T], [H|Rez]):-
    multime(T, Rez).
%-----------------------------------------
%inserare(El - element, L - lista, Rez - lista)
%insereaza elementul pe pozitia corespunzatoare in lista SORTATA
%model de flux: (i,i,o)

inserare(X, [], [X]).  %daca lista e vida inseram elementul

inserare(X, [H|T], [X,H|T]):-
	X =< H, !.  %inseram elementul in fata primului element mai mare

inserare(X, [H|T], [H|Rez]):-
	X > H,
	inserare(X, T, Rez).  %X e mai mare, adaugam doar H si continuam
%-----------------------------------------
%sortare(L - lista, Rez - lista)
%sorteaza lista folosind Insertion Sort
%model de flux: (i,o)

sortare([], []).  %cand ajunge la lista vida, returnam o lista vida

sortare([H|T], Rez):-
	sortare(T, RezT),  %sorteaza "restul" listei
	inserare(H, RezT, Rez), !.  %insereaza H in lista rezultata sortata
%-----------------------------------------
%sortare_fara_dubluri(L - lista, Rez - lista)
%elimina dublurile si sorteaza lista rezultata
%model de flux: (i,o)

sortare_fara_dubluri(L, Rez):-
	multime(L, RezFaraDubluri),
	sortare(RezFaraDubluri, Rez).
%-----------------------------------------
%b
%sortare_fara_dubluri_eterogen(L - lista, Rez - lista)
%face sortare_fara_dubluri pe lista eterogena
%model de flux: (i,o)

sortare_fara_dubluri_eterogen([], []).

sortare_fara_dubluri_eterogen([L|T], [L_sortata|Rez]):-
	is_list(L), !,
	sortare_fara_dubluri(L, L_sortata),
	sortare_fara_dubluri_eterogen(T, Rez).

sortare_fara_dubluri_eterogen([X|T], [X|Rez]):-
	sortare_fara_dubluri_eterogen(T, Rez).
%-----------------------------------------








