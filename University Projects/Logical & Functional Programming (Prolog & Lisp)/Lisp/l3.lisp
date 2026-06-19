(defun all_atoms(l)
  (cond
	((atom l) (list l))
	(t (mapcan #'all_atoms l))
  )
)

;	model matematic:
;	all_atoms(l) = 1. {l}, daca l e atom
;		       2. U all_atoms(li), daca l = (l1..ln)