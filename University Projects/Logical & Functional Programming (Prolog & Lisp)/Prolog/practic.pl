%se da o lista formata din nr intregi. sa se genereze lista
% submultimilor listei

%pick_number(X - numar, L - lista)

pick_number(_, []).

pick_number(X, [H|T]):-
	X = H, !,
	pick_number(X, T).

apare(El, [El|_]).

apare(El, [_|T]):-
	apare(El, T).

%elemente(L - lista, Rez - lista cu elementele)
%returneaza o lista de liste cu elementele multimii

elemente([], [[]]).

elemente([H|T], [[H]|Rez]):-
	elemente(T, Rez).

% generare_submultimi(L - lista, Rez - lista finala de submultimi
% imbina toate multimile din L pentru a crea multimi noi

submultimi([], []).

submultimi([H1,H2|T], [HRez|Rez]):-
	submultimi(T, Rez),
	append(H1, H2, HRez),
	\+ apare(HRez, Rez).

