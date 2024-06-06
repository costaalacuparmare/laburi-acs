#lang racket
(require "suffix-tree-stream.rkt")
(require "collection.rkt")

(provide (all-defined-out))

;; Vom prelua toate funcțiile din etapele 1-3 (exceptând
;; longest-common-substring, care nu beneficiază de 
;; reprezentarea ca flux întrucât parcurge tot arborele)
;; și le vom adapta la noua reprezentare a unui ST.
;;
;; Pentru că un ST este construit pornind de la o colecție
;; de sufixe și pentru că ne dorim să nu calculăm toate
;; sufixele decât dacă este nevoie, vom modifica toate
;; funcțiile care prelucrau liste de sufixe pentru a
;; prelucra fluxuri de sufixe.
;;
;; Obs: fără această modificare a listelor de sufixe în
;; fluxuri de sufixe, și presupunând că am manipulat
;; arborii de sufixe doar prin interfața definită în
;; fișierul suffix-tree (respectând astfel bariera de 
;; abstractizare), ar trebui să alterăm doar funcția 
;; suffixes->st care este practic un constructor pentru
;; tipul ST.
;; Din cauza transformării listelor de sufixe în fluxuri,
;; avem mult mai multe implementări de modificat.
;; Puteam evita acest lucru? Da, utilizând conceptul de
;; colecție de sufixe de la început (în loc să presupunem
;; că ele vor fi prelucrate ca liste). În loc de cons,
;; car, cdr, map, filter, etc. am fi folosit de fiecare
;; dată collection-cons, collection-first, ... etc. -
;; aceste funcții fiind definite într-o bibliotecă
;; inițială ca fiind echivalentele lor pe liste, și
;; redefinite ulterior în stream-cons, stream-first,
;; ... etc. Operatorii pe colecții de sufixe ar fi 
;; folosit, desigur, doar funcții de tip collection-.
;;
;; Am ales să nu procedăm astfel pentru că ar fi provocat
;; confuzie la momentul respectiv (când chiar operatorii
;; pe liste erau o noutate) și pentru a vă da ocazia să
;; faceți singuri acest "re-design".


; TODO
; Copiați din etapele anterioare implementările funcțiilor
; de mai jos și modificați-le astfel:
; - Toate funcțiile care lucrează cu liste de sufixe vor
;   lucra cu un nou tip de date Collection, ai cărui
;   constructori și operatori vor fi definiți de voi
;   în fișierul collection.rkt.
; - Pentru toate funcțiile, trebuie să vă asigurați că
;   este respectată bariera de abstractizare (atât în 
;   cazul tipului ST cât și în cazul tipului Collection).
; Obs: cu cât mai multe funcții rămân nemodificate, cu atât
; este mai bine (înseamnă că design-ul inițial a fost bun).

(define (longest-common-prefix w1 w2)
  (define (iter prefix w1 w2)
    (cond
      ((or (null? w1) (null? w2))
       (list prefix w1 w2))
      ((not (equal? (car w1) (car w2)))
       (list prefix w1 w2))
      (else
       (iter (append prefix (list (car w1)))
             (cdr w1) (cdr w2)))))
  (let* ((n (min (length w1) (length w2))))
    (iter '() w1 w2)
    )
  )


; am schimbat, în numele funcției, cuvântul list în
; cuvântul collection
(define (longest-common-prefix-of-collection words)
  (define (iter prefix words)
    (if (collection-empty? words)
        prefix
        (let* ((next-word (collection-car words)))
          (iter (car (longest-common-prefix prefix next-word))
                (collection-cdr words))
          )
        )
    )
  (iter (collection-car words) (collection-cdr words))
  )


(define (match-pattern-with-label st pattern)
  (let* ((ch-branch (get-ch-branch st (car pattern))))
    (if (not ch-branch)
        (list #f '())
        (let* ((prefix-result (longest-common-prefix (get-branch-label ch-branch) pattern)))
          (cond
            ((equal? (car prefix-result) pattern) #t)
            (else (if (equal? (car prefix-result) (caddr prefix-result))
                      (list #f (car prefix-result))
                      (list (car prefix-result) (caddr prefix-result) (get-branch-subtree ch-branch))))
            )
          )
        )
    )
  )


(define (st-has-pattern? st pattern)
  (let* ((match (match-pattern-with-label st pattern)))
    (cond
      ((equal? match #t) #t)
      ((equal? (car match) #f) #f)
      (else (st-has-pattern? (caddr match) (cadr match)))
      )
    )
  )


(define (get-suffixes text)
  (if (null? text)
      '()
      (collection-cons text (get-suffixes (cdr text)))
      )
  )


(define (get-ch-words words ch)
  (collection-filter (lambda (x) (and (not (null? x)) (equal? (car x) ch))) words)
  )


(define (ast-func suffixes)
  (let* ((new-suffixes (collection-map (lambda (x)
                                         (if (null? x)
                                             '()
                                             (cdr x)
                                             ))
                                       suffixes))
         (ast-pair (cons (list (car (collection-car suffixes))) new-suffixes))
         )
    (if (null? (cdr ast-pair))
        (list (car ast-pair))
        ast-pair
        )
    )
  )


(define (cst-func suffixes)
  (let* ((common-prefix (longest-common-prefix-of-collection suffixes))
         (cst-pair (cons common-prefix (collection-map (lambda (x)
                                                         (drop x (length common-prefix)))
                                                       suffixes))))
    (if (null? (cdr cst-pair))
        (list (car cst-pair))
        cst-pair
        )
    )
  )

; considerați că și parametrul alphabet este un flux
; (desigur, și suffixes este un flux, fiind o colecție
; de sufixe)
(define (suffixes->st labeling-func suffixes alphabet)
  (define (lose-nulls pairs)
    (collection-filter (lambda (element)
                         (not (collection-empty? element)))
                       pairs)
    )
  (if (null? suffixes)
      empty-st
      (let* ((first-letter-match-pairs (collection-map (lambda (ch)
                                                         (get-ch-words suffixes ch))
                                                       alphabet))
             (labeled-branches (collection-map labeling-func (lose-nulls first-letter-match-pairs))))
        (collection-map (lambda (branch)
                          (cons (car branch)
                                (suffixes->st labeling-func (cdr branch) alphabet)))
                        labeled-branches)
        )
      )
  )

; nu uitați să convertiți alfabetul într-un flux
(define text->st
  (lambda (text)
    (lambda (labeling-func)
      (let* ((suffixes (get-suffixes (append text '(#\$))))
             (sorted-alphabet (sort (remove-duplicates (append text '(#\$))) char<?)))
        (suffixes->st labeling-func suffixes (list->collection sorted-alphabet)))
      )
    )
  )


(define text->ast
  (lambda (text)
    ((text->st text) ast-func)
    )
  )


(define text->cst
  (lambda (text)
    ((text->st text) cst-func)
    )
  )


; dacă ați respectat bariera de abstractizare,
; această funcție va rămâne nemodificată.
(define (substring? text pattern)
  (st-has-pattern? (text->ast text) pattern)
  )


; dacă ați respectat bariera de abstractizare,
; această funcție va rămâne nemodificată.
(define (repeated-substring-of-given-length text len)
  (define (dfs stree path)
    (if (st-empty? stree)
        (if (and (>= (length path) len) (not (null? path)))
            (take path len)
            #f)
        (let ((subtree (first-branch stree))
              (substr (append path (get-branch-label (first-branch stree)))))
          (if (collection-empty? (get-branch-subtree subtree))
              (dfs (other-branches stree) path)
              (let ((result (dfs (get-branch-subtree subtree) substr)))
                (if result
                    result
                    (dfs (other-branches stree) path)
                    )
                )
              )
          )
        )
    )
  (dfs (text->cst text) '())
  )