(defun e_putere_2 (p putere)
  (cond
    ((> putere p) nil)
    ((= putere p) t)
    (t (e_putere_2 p (* putere 2)))
  )
)

(defun aux_sterg (l index)
  (cond
    ((null l) nil)
    ((and (numberp (car l)) (e_putere_2 (+ 1 index) 1)) (aux_sterg (cdr l) (+ 1 index)))
    ((numberp (car l)) (cons (car l) (aux_sterg (cdr l) (+ 1 index))))
    (t (cons (car l) (aux_sterg (cdr l) index)))
  )
)

(defun sterg (l) (aux_sterg l 0))

;	model matematic:

;	e_putere_2(p, putere) = 1. false, daca putere > p
;			        2. true, daca putere = p
;			        3. e_putere_2(p, putere * 2), daca putere < p

;	aux_sterg(l1..ln, index) = 1. nil, daca n = 0
;				   2. aux_sterg(l2..ln, index + 1), daca l1 e numar si e pe
;				         pozitie putere a lui 2
;				   3. l1 U aux_sterg(l2..ln, index + 1), daca l1 e numar
;				   4. l1 U aux_sterg(l2..ln, index), altfel

;	sterg(l1..ln) = aux_sterg(l1..ln, 0)