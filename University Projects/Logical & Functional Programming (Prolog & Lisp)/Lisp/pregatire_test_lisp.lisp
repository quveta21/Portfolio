(defun count_atoms(l)
  (cond
	((null l) 0)
	((atom l) 1)
	(t (apply #'+ (mapcar #'count_atoms l)))
  )
)

(defun e_membru(l e)
  (cond
	((equal l e) t)
	((atom  l) nil)
	(t (or (e_membru (car l) e) (e_membru (cdr l) e)))
  )
)

(defun inordine (arb)
  (cond
    ((null arb) nil)	; daca arborele e vid, returnam NIL
    (t 
     (append 
       (inordine (cadr arb))   ; parcurge subarb st
       (list (car arb))        ; pune radacina
       (inordine (caddr arb))  ; parcurge subarb dr
     ))
  )
)

(defun postordine (arb)
  (cond
    ((null arb) nil)
    (t 
     (append 
       (postordine (cadr arb))   
       (postordine (caddr arb))  
       (list (car arb))          
     ))
  )
)

(defun preordine (arb)
  (cond
    ((null arb) nil) ; Dacă arborele e vid, returnăm NIL
    (t 
     (append 
       (list (car arb))         ; 1. Vizitează Rădăcina (PRIMUL lucru)
       (preordine (cadr arb))   ; 2. Parcurge Stânga recursiv
       (preordine (caddr arb))  ; 3. Parcurge Dreapta recursiv
     ))
  )
)

(defun nivel (arb x n)
  (cond
    ((null arb) nil)
    ((equal (car arb) x) n)
    (t (or (nivel (cadr arb) x (+ 1 n)) (nivel (caddr arb) x (+ 1 n))))
  )
)

(defun main_nivel (arb x) (nivel arb x 0))