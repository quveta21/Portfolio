(defun succesor_pare(l)
  (cond
	((and (numberp l) (evenp l)) (+ l 1))
	((atom l) l)
	(t (mapcar #'succesor_pare l))
  )
)

(defun nivel_k(arb k)
  (cond 
	((and (= k 0) (atom arb)) (list arb))	;cand gasim un nod pe nivelul k
	(t (mapcan #'(lambda (l) (nivel_k l (- k 1))) arb))
  )
)

(defun main_k(arb k) (nivel_k arb (+ k 1)))

(defun nivel_imp(arb nivel e)
  (cond
	((and (oddp nivel) (atom arb)) e)
	((and (evenp nivel) (atom arb)) arb)
	(t (mapcar #'(lambda (l) (nivel_imp l (+ nivel 1) e)) arb))
  )
)

(defun main_imp(arb e) (nivel_imp arb -1 e))

(defun adancime(l)
  (cond
	((null (cdr l)) 0)
	(t (+ 1 (apply #'max (mapcar #'adancime (cdr l)))))
  )
)

(defun adancime2(l)
  (cond
	((atom l) 0)
	(t (+ 1 (apply #'max (mapcar #'adancime2 l))))
  )
)

(defun elimina(e l)
  (cond
	((and (atom l) (equal l e)) nil)
	((atom l) (list l))
	(t (mapcan #'(lambda (lst) (elimina e lst)) l))
  )
)

(defun inloc_zero(l k)
  (cond
	((and (= k 0) (atom l)) 0)
	((atom l) l)
	(t (mapcar #'(lambda (lst) (inloc_zero lst (- k 1))) l))
  )
)

(defun main_inloc_zero(l k) (inloc_zero l (+ k 1)))