%apare(El - element, L - lista)
%verifica daca apare elementul in lista
%model de flux: (i,i), (i,o), (o,i)

apare(El, [El|_]):- !.

apare(El, [_|T]):-
	apare(El, T).

%abs_val(N - numar intreg, Rez - valoare N absoluta)
%intoarce valoarea absoluta a lui N
%model de flux: (i,i), (i,o)

abs_val(N, A):-
	N < 0, !,
	A is -N.

abs_val(N, N).

%oglindire(L - lista, R - lista oglindita)
%ogl_acc(L - lista, Acc - acumulator, R - rezultatul oglindirii)
%inverseaza o lista
%model de flux: (i,i), (i,o)

ogl_acc([], Acc, Acc).  %rezultatul e acumularea inversa a numerelor

ogl_acc([H|T], Acc, R) :- ogl_acc(T,[H|Acc],R).  %adaugam elem. invers

oglindire(L,R) :- ogl_acc(L,[],R).

%proprietate(X - elementul, L - lista)
% verifica daca X respecta proprietatea cerintei, adica daca exista
% vreun Y in lista astfel incat |v(X)-v(Y)| = 1
%model de flux: (i,i)

proprietate(X, [Y|_]):-
	abs_val(X-Y, A),  %putem pune direct X-Y pt ca apare is
	A =:= 1, !.

proprietate(X, [_|T]):-
	proprietate(X, T).  %daca nu gasim vecin, cautam mai departe

%lungime(L - lista, N - lungimea listei)
%afla lungimea listei
%model de flux: (i,i), (i,o)

lungime([],0).

lungime([_|T],N) :- lungime(T,N1), N is N1+1.

%in_interval(X - numar intreg, Lo - interval low, Hi - interval high)
%genereaza valorile intregi dintre Lo si Hi
%model de flux: (i,i,i), (i,i,o)

in_interval(X,Lo,Hi) :-
    Lo =< Hi,                          %conditia de oprire a generarii
    ( X = Lo                            %X e primul numar din interval
    ; Lo1 is Lo+1, in_interval(X,Lo1,Hi) ).  %limita inferioara creste

% generate_perm(N - numar intreg, Acc - acumulator, Rez - rezultatul
% final)
% genereaza o permutare INVERSATA(de la coada la cap) cu proprietatea
% din cerinta
% model de flux: (i,i,i), (i,i,o), (i,o,o), (i,o,i)

generate_perm(N, Acc, Acc):-
	lungime(Acc, N), !.  %daca am acumulat N numere, am gasit rezultatul

generate_perm(N, [], Rez):-         %primul element: orice X din 1..N
    in_interval(X,1,N),
    generate_perm(N,[X],Rez).

generate_perm(N, Acc, Rez):-
	in_interval(X, 1, N),  %genereaza un nr din permutare
	\+ apare(X, Acc),  %verificam sa NU apara deja in permutare
	proprietate(X, Acc),  %verificam proprietatea)
	generate_perm(N, [X|Acc], Rez).

%permutare(N - numar intreg, Rez - permutare)
%genereaza permutarile cu proprietatea ceruta
%model de flux: (i,i), (i,o)

permutare(N,Rez) :-
    generate_perm(N,[],Rinv),
    oglindire(Rinv,Rez).



