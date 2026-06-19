%lab1_p1

%a
%apare(El - element, L - lista)
%model de flux: (i,o), (o,i)
apare(El, [El|_]):- !. %daca gaseste El se opreste recursivitatea

apare(El, [_|T]):-
    apare(El, T). %daca nu il gaseste, continua cautarea cu restul listei

%multime(L - lista, Rez - lista)
%transforma o lista intr-o multime, in ordinea ultimei aparitii
%model de flux: (i,o)

multime([], []).  %daca lista e vida, rezultatul e vid

multime([H|T], Rez):-
    apare(H, T), !,
    multime(T, Rez). %daca mai apare elementul, il ignoram si continuam

multime([H|T], [H|Rez]):-
    multime(T, Rez).

%b
%gcd(A - int, B - int, D - int)
%model de flux: (i,i,o)
gcd(A, 0, A):- !. %cand restul e 0 am gasit gcd (atribuim lui D valoarea din A)

gcd(A, B, D):-
    B \= 0,
    R is A mod B,
    gcd(B, R, D).

%gcd_list(L - lista, D - int)
%sa se calculeze cmmdc al unei liste
%model de flux: (i,o)

gcd_list([H], H):- !.  %cand lista are un element, D = L1

gcd_list([H|T], D):-
    gcd_list(T, DT), %aflam intai gcd al restului listei
    gcd(H, DT, D). %gasim gcd al intregii liste









