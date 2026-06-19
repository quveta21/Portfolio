(defun nivel-k (lista k)
  (car (proc-nod lista 0 k)))

;; proceseaza un nod
(defun proc-nod (lista nivel k)
  ;; consuma subarborii nodului
  ;; (cadr lista) = nr fii
  ;; (cddr lista) = restul listei
  (let ((rez-fii (proc-fii (cadr lista) (cddr lista) (1+ nivel) k)))
    (list 
      (if (= nivel k) 
          (cons (car lista) (car rez-fii)) ; daca suntem pe nivelul k, adaugam nodul la lista rezultat
          (car rez-fii))                   ; altfel,
      
      ;; restul listei ramase
      (cadr rez-fii))))

;; proceseaza n fii
(defun proc-fii (n lista nivel k)
  (if (= n 0)
      (list nil lista) ; stop: 0 fii -> lista de noduri e goala, restul listei e neschimbat
      
      ;; parcurg recursiv cei n fii
      (let* ((r1 (proc-nod lista nivel k))               ; rez fiu 1
             (rn (proc-fii (1- n) (cadr r1) nivel k)))   ; rez restul fiilor
        
        ;; lipesc rezultatele
        (list (append (car r1) (car rn))  ; lista de noduri gasite in r1 si rn
              (cadr rn)))))               ; returnez restul ramas de la ultimul fiu