;1

(defun produs (v1 v2)
  (if (null v1)				;conditia de oprire: daca nu mai avem membri ai vectorului de verificat
      0					;returnam 0 in acest caz
      (+ (* (car v1) (car v2))		;inmultim coordonatele curente
         (produs (cdr v1) (cdr v2)))))	;si le adunam la restul sumei pentru celelalte coordonate

;2

(defun adancime(lst)
  (cond
      ((null lst) 1)			;lista vida va avea adancime 1
      ((atom lst) 0)			;daca l1 e atom, nu crestem adancimea
      (t (max (+ 1 (adancime(car lst)))	;altfel luam maximul dintre adancimea lui l1 + 1
          (adancime(cdr lst))))		;si adancimea restului listei
  )
)

;3

(defun inserare(e lst rez)
  (cond
    ((null lst)
       (append (reverse rez) (list e)))			;daca lista e vida inseram elementul
    ((= e (car lst))
       (append (reverse rez) lst))			;eliminam dublurile
    ((< e (car lst))
       (append (reverse rez) (cons e lst)))		;inseram elementul pe pozitia potrivita
    (t
       (inserare e (cdr lst) (cons (car lst) rez))))	;adaugam elementul curent si continuam cautarea pozitiei (in ordine inversa)
)

(defun sortare (lst rez)
  (if (null lst)
      rez						;returnam rezultatul cand nu mai avem ce sorta
      (sortare (cdr lst) (inserare (car lst) rez nil))	;inseram fiecare element in pozitia potrivita
  )
)

(defun sortare_main(lst)
  (sortare lst nil)
)

;4

(defun apare(e m)
  (if (null m)
      NIL			;nil daca multimea e vida
      (if (equal e (car m))
          T			;true daca e egal cu elementul curent
          (apare e (cdr m))	;altfel, continuam cautarea in restul listei
      )
  )
)

(defun intersectie(m1 m2 rez)
  (if (null m1)
      rez								;intoarcem rezultatul cand nu mai avem elemente
      (if (apare (car m1) m2)
          (intersectie (cdr m1) m2 (append rez (list (car m1))))	;daca apare elementul in m2, il adaugam in intersectie
          (intersectie (cdr m1) m2 rez)					;altfel, continuam cu restul elementelor
      )
  )
)

(defun intersectie_main(m1 m2)
  (intersectie m1 m2 ())
)