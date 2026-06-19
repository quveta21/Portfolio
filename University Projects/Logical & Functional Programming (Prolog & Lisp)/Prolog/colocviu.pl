%candidat(L, Elem)
%alege un element candidat din lista L
%model de flux (i,o), (i,i)

candidat([H|_], H).
candidat([_|T], E):-
	candidat(T, E).

%generare(L, Col, Lg, P, K, V, Rez)
%model de flux (i,i,i,i,i,i,o)

generare(_, Col, K, _, K, _, Col):-!.
generare(L, Col, Lg, P, K, V, Rez):-
	candidat(L, E),
	\+ candidat(Col, E),
	V > P * E,    %verificam conditia pentru validarea generarii
	Lg1 is Lg + 1,
	P1 is P * E,
	generare(L, [E|Col], Lg1, P1, K, V, Rez).

main(L, K, V, Rez):-findall(R1, generare(L,[],0,1,K,V,R1), Rez).

%interval(A, B, Rez)
%construieste multimea de valori intregi din intervalul [A,B]
%model de flux (i,i,o), (i,i,i)

interval(A,A,[A]):-!.
interval(A,B,[A|Rez]):-
	A1 is A+1,
	interval(A1,B,Rez).

%candidat2(L, Elem, Rest)
%alege un candidat in Elem si returneaza in Rest valorile disponibile
%la stanga candidatului (vom construi submultimea de la dreapta
%la stanga

candidat2([H|_], H, []).
candidat2([H|T], E, [H|Rez]):-
	candidat2(T, E, Rez).

%generare2(Rest, Col, Lg, N, S, R)

generare2(_, Col, N, N, S, Col):-
	0 is S mod 2, !.
generare2(L, Col, Lg, N, S, R):-
	candidat2(L, E, Rest),
	Lg1 is Lg+1,
	S1 is S+E,
	generare2(Rest, [E|Col], Lg1, N, S1, R).

main2(A,B,N,R):-
	interval(A,B,L),
	findall(R1, generare2(L,[],0,N,0,R1),R).


%candidat3 acelasi cu candidat1

candidat3([H|_], H).
candidat3([_|T], E):-
	candidat3(T, E).

%generare3(L,Col,Lg,Pc,K,P,Rez)

generare3(_,Col,K,P,K,P,Col):-!.
generare3(L,Col,Lg,Pc,K,P,Rez):-
	candidat3(L, E),
	\+ candidat3(Col, E),
	P >= Pc * E,
	Lg1 is Lg+1,
	Pc1 is Pc * E,
	generare3(L,[E|Col],Lg1,Pc1,K,P,Rez).

main3(L,K,P,R):-
	findall(R1, generare3(L,[],0,1,K,P,R1), R).


%generare4(L,Col,S,NrImp,Rez)

generare4(_,Col,S,NrImp,Col):-
	1 is S mod 2,
	1 is NrImp mod 2.

generare4(L,Col,S,NrImp,Rez):-
	candidat2(L, E, Rest),
	S1 is S+E,
	Paritate is E mod 2,
	NrImp1 is NrImp+Paritate,
	generare4(Rest,[E|Col],S1,NrImp1,Rez).

main4(L, R):-
	findall(R1, generare4(L,[],0,0,R1), R).

submultime([],[]).
submultime([H|T], [H|R]):-
	submultime(T, R).
submultime([_|T], R):-
	submultime(T, R).

total_submultimi(L, R):- findall(R1, submultime(L, R1), R).





