(in-package :om)

(om::defmethod! group-identical ((liste list))
  :initvals (list (list 1 2)) 
  :indoc '("liste")
  :icon 128
  :doc "constructs a list of list of elements 
by grouping successive identical elements in <liste>.
example:
(group-identical '(1 2 3 4 toto toto 5 5 5 1 2 1 1 2 3 1 1 3 3))
OM->((1) (2) (3) (4) (toto toto) (5 5 5) (1) (2) (1 1) (2) (3) (1 1) (3 3))

 "
  (if (null liste)
    liste
    (let* ((first (car liste))
           (rest (rest liste))
           )
      (if (atom first)
       (cons (cons first (loop while (equal first (first rest))
        collect (pop rest)))
             (group-identical rest))
        (cons (group-identical first) (group-identical rest))))))