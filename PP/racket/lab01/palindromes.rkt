#lang racket

; ignorați următoarele linii de cod.
(define show-defaults 2) ; câte exerciții la care s-au întors rezultate default să fie arătate detaliat
(define prepend #f) (define nopoints #t) (define name-ex '(testul testele trecut exercițiul)) ; variante: '(exercițiul exercițiile rezolvat exercițiul) sau '(testul testele trecut exercițiul) sau '(task taskurile rezolvat capitolul)
(define default-results `(#f 0 () your-code-here)) ; ce rezultate default sunt întoarse în exerciții
(define : 'separator) (define punct 'string) (define puncte 'string) (define BONUS 'string) (define total 0) (define exerciții 'string) (define all '()) (define n-ex 0) (define p-ex 0) (define n-exercs -1) (define defaults '())
(define (ex n sep p . s) (set! n-ex n) (set! p-ex p) (set! all (cons (list n p) all))) (define exercițiul ex) (define (p L) (map (λ (e) (display e) (display " ")) L) (newline)) (define (p-n-ex) (if nopoints (string-join (list (symbol->string (cadddr name-ex)) (number->string n-ex) "/" (number->string n-exercs))) n-ex)) (define (sunt n s) (set! n-exercs n))
(define (check-exp given expected) (check-exp-part "" 1 given expected)) (define (check-exp-part part per given expected) (check-test part per equal? given expected "diferă de cel așteptat"))
(define (check-in  given expected) (check-in-part  "" 1 given expected)) (define (check-in-part part per given expected) (check-test part per member given expected "nu se află printre variantele așteptate"))
(define (list>setR start end ch-len? L) (if (zero? end) L ((if (<= start 0) list->seteqv identity) (map (λ (e) (if (list? e) (list>setR (sub1 start) (sub1 end) e) e)) L))))
(define (check-set given expected) (check-set-part  "" 1 given expected)) (define (check-set-part part per given expected) (check-test part per (λ (x y) (apply equal? (map list->seteqv `(,given ,expected)))) given expected "nu este echivalent cu cel așteptat"))
(define (check-set-unique given expected) (check-set-unique-part  "" 1 given expected)) (define (check-set-unique-part part per given expected) (check-test part per (λ (x y) (and (apply = (map length `(,given ,expected))) (apply equal? (map list->seteqv `(,given ,expected))))) given expected "nu este echivalent cu cel așteptat"))
(define (check-test part percent tester given expected err-m) (if (not (tester given expected)) (and (when (member given default-results) (set! defaults (cons (if (< percent 1) (cons n-ex part) n-ex) defaults)))
  (when (or (not (member given default-results)) (<= (length defaults) show-defaults))
    (printf "[~a][--]~a rezultatul ~v ~a: ~v~n" (p-n-ex) (if (< percent 1) (format " la ~a ~v" (car name-ex) part) "") given err-m expected)))
 (let ((pts (* p-ex percent))) (printf (string-join (list "~a ~a ~a~a~a" (if nopoints "~a~a" ": +~v ~a") "~n") "") (if (and prepend (not nopoints)) (format "+~v:" pts) (format "[~a][OK]" (p-n-ex))) (car name-ex) (if (or prepend nopoints) n-ex "") (if (< percent 1) (format "~v " part) " ") (caddr name-ex) (if nopoints "" pts) (if nopoints "" (if (= pts 1) 'punct 'puncte))) (set! total (+ total pts)))))
(define (sumar) (when (and (not (null? defaults)) (< show-defaults (length defaults))) (p `(... rezultatul implicit dat la ,(cadr name-ex) ,(reverse defaults)))) (when (not nopoints) (printf "total: ~v puncte~n" total)))


;; Avem de implementat o mini-bibliotecă pentru numere palindromice.

;; Pentru aceasta, vom defini, pe rând, funcții pentru:
;; - reprezentarea (ca listă de "cifre") a unui număr natural într-o bază b
;; - testul că o listă este palindrom (adică este totuna cu lista inversată)
;; - diverse exerciții bazate pe numere palindromice într-una sau mai multe baze

(sunt 9 exerciții)

(exercițiul 1 : 1 punct)
;; Fie următoarele axiome pentru obținerea reprezentării unui număr natural
;; în baza b (cu [] = lista vidă și ++ = concatenare).
;; Convenim ca numărul 0 (în orice bază) să fie reprezentat prin lista vidă,
;; în rest reprezentarea corespunde reprezentării matematice.
;; num->base(0,b) = [ ]                                   ; pt n=0
;; num->base(n,b) = num->base(n div b, b) ++ [ n mod b ]  ; pt n>0
;; Implementați funcția corespunzătoare în Racket.

(define (num->base n b)
  (if (= n 0)
     '()
     (append (num->base (quotient n b) b) (list (modulo n b)))
  )
)
(check-exp-part 'a .5 (num->base 489 10) '(4 8 9))
(check-exp-part 'b .5 (num->base 489 2) '(1 1 1 1 0 1 0 0 1))


(exercițiul 2 : 1 punct)
;; Fie următoarele axiome pentru inversarea unei liste.
;; rev([ ]) = [ ]
;; rev(x:l) = rev(l) ++ [x]
;; Implementați funcția corespunzătoare în Racket.

(define (rev L)
  (if (null? L)
     '()
     (append (rev(cdr L)) (list (car L)))
  )
)

(check-exp (rev '(5 1 4 8 7)) '(7 8 4 1 5))


(exercițiul 3 : 1 punct)
;; Un reverse care acționează și asupra elementelor din eventualele liste interioare.
;; ex: Pt lista L = '(1 b (3 d (5 f)) (7 (h (9 10) 11)) 12):
;; (rev L) întoarce '(12 (7 (h (9 10) 11)) (3 d (5 f)) b 1)
;; (deep-rev L) ->  '(12 ((11 (10 9) h) 7) ((f 5) d 3) b 1)

; Cazul 1) - cazul de bază:
;; deep-rev([ ]) = [ ]

; Cazul 2) - când elementul curent NU este o listă, procedăm ca la funcția rev de mai sus:
;; deep-rev(x:l) = deep-rev(l) ++ [x]

; Cazul 3) - similar, dar când elementul curent este de asemenea o listă,
; această listă trebuie și ea inversată (cu tot cu eventualele liste interioare).
; În acest scop folosim tot deep-rev:
;; deep-rev(L:l) = deep-rev(l) ++ [deep-rev(L)]

;; Restricții:
;; - folosiți cond
;; - folosiți list? pentru a verifica dacă elementul procesat este o listă

(define (deep-rev L)
  (cond
      ((null? L) L)
      ((list? (car L)) (append (deep-rev (cdr L)) (list (deep-rev (car L)))))
      (else (append (deep-rev (cdr L)) (list (car L))))
  )
)

(check-exp (deep-rev '(1 b (3 d (5 f)) (7 (h (9 10) 11)) 12)) '(12 ((11 (10 9) h) 7) ((f 5) d 3) b 1))


(exercițiul 4 : 1 punct)
;; Implementați testul că o listă L este palindrom.
;; Abordarea recomandată este să descrieți CE este un palindrom,
;; mai degrabă decât CUM se verifică proprietatea de palindrom.
;; Genul acesta de abordare corespunde stilului declarativ de
;; a programa (în contrast cu stilul procedural).

(define (palindrome? L)
  (if (equal? L (rev L))
       #t
       #f
  )
)

(check-exp-part 'a .25 (palindrome? '(1 4 4 1)) #t)
(check-exp-part 'b .25 (palindrome? '(1 4 2 4 1)) #t)
(check-exp-part 'c .25 (palindrome? '(1 4 4 1 4 1)) #f)
(check-exp-part 'd .25 (palindrome? '()) #t)


(exercițiul 5 : 2 puncte)
;; Testați că n este palindrom în toate bazele din lista Bases.

;; a) După ce variabilă/variabile e util să faceți recursivitatea?
;;    - ar ajuta să știți dacă n-1 este palindrom în toate bazele din Bases?
;;    - ar ajuta să știți dacă n este palindrom în toate bazele din (cdr Bases)?
;;    (obs: nu întotdeauna facem apel recursiv pe -1 sau cdr, dar sunt cazurile cele mai frecvente)
;; b) Care sunt condițiile de oprire, în funcție de aceste variabile? (cazurile de bază)
;;    - ce trebuie să întoarcă funcția în aceste cazuri?
;;      (respectați mereu tipul întors de funcție: trebuie să fie număr, listă, bool, etc.?)
;;    - gândiți-vă cum valorile întoarse pe cazul de bază sunt preluate de funcție pentru a calcula
;;      rezultatul final
;; c) Care este apelul recursiv (e obligatoriu să aveți minim unul), și care este formula prin care
;;    din apelul recursiv se obține rezultatul final?

(define (all-palindromes? n Bases)
  (cond
      ((= n 0) #f)
      ((null? Bases) #t)
      (else (if (palindrome? (num->base n (car Bases)))
                 (all-palindromes? n (cdr Bases))
                 #f
            )
      )
  ) 
)

(check-exp-part 'a .5 (all-palindromes? 585 '(2 10)) #t)
(check-exp-part 'b .5 (all-palindromes? 594 '(2 10)) #f)


(exercițiul 6 : 0 puncte)
;; Dacă nu ați făcut-o deja, încercați să înlocuiți if sau cond de mai sus cu o combinație
;; de operatori logici (and, or, not).
;; Apoi testați-vă singuri funcția (fără check-expect, doar rulați-o pe o listă aleasă de voi).

(define (all-palindromes2? n Bases)
  (or (null? Bases)
      (and (palindrome? (num->base n (car Bases)))
           (all-palindromes2? n (cdr Bases))
      )
  )
)

(all-palindromes2? 585 '(2 10))



(exercițiul 7 : 2 puncte)
;; Găsiți toate numerele naturale, mai mici sau egale cu n, care sunt
;; palindroame în toate bazele din lista Bases.

;; Sugestii:
;; - folosiți funcția anterioară.
;; - efectuați pașii a, b, c descriși mai sus:
;;   a) Vrem să facem recursivitate după n sau după Bases?
;;   ... etc.

(define (palindromes-to-n n Bases)
  (cond
    ((< n 0) (list 0))
    ((all-palindromes? n Bases) (append (palindromes-to-n (- n 1) Bases) (list n)))
    (else (palindromes-to-n (- n 1) Bases))    
  )
)

(check-exp (palindromes-to-n 100 '(2 10)) '(0 1 3 5 7 9 33 99))


(exercițiul 8 : 2 puncte)
;; Să se găsească primul număr mai mare sau egal cu start care este 
;; palindrom în minim b baze dintre bazele 2, 3, 4, 5, 6, 7, 8, 9, 10.

;; Sugestii:
;; - definiți-vă una sau mai multe funcții ajutătoare
;; - puteți folosi tehnica "wishful thinking"
;;   - scrieți funcția finală apelând oricâte funcții ajutătoare încă inexistente
;;   - apoi implementați toate funcțiile de care ați descoperit că aveți nevoie
(define (verify-bases n Bases)
  (cond
    ((null? Bases) 0)
    ((palindrome? (num->base n (car Bases))) (+ (verify-bases n (cdr Bases)) 1))
    (else (verify-bases n (cdr Bases)))
  )
)

(define (first-b-pal start b)
  (if (>= (verify-bases start '(2 3 4 5 6 7 8 9 10)) b)
      start
      (first-b-pal (+ start 1) b)
  )
)

(check-exp-part 'a .5 (first-b-pal 10 4) 121)
(check-exp-part 'b .5 (first-b-pal 150 4) 373)


(exercițiul 9 : 3 puncte)
;; Să se găsească cea mai lungă porțiune continuă a unui număr care este palindrom.
;; Dacă există mai multe asemenea porțiuni, întoarceți una (oarecare) dintre ele.

;; Funcție ajutătoare care transformă o listă de cifre în număr
(define (list->num L) (foldl (lambda (dig num) (+ dig (* 10 num))) 0 L))

;; Sugestii:
;; - convertiți numerele în liste pentru a le prelucra cu funcțiile pe liste
;;   (pentru conversia inversă este dată funcția list->num de mai sus)
;; - folosiți take - (take L n) întoarce prefixul de lungime n al listei L

(define (longest-palindrome n)
   (define L (num->base n 10))
   (define len (length L))
   (define (iter L len crtlen)
      (and (<= len crtlen)
           (if (palindrome? (take L len))
               (list->num (take L len))
               (iter (cdr L) len (- crtlen 1))
           )
      )
  )
  (define (iter2 leng)
    (if (= leng 1)
        (car L)
        (or (iter L leng len) (iter2 (- leng 1)))
    )
  )
  (iter2 len)
)

(check-exp-part 'a 1/6 (longest-palindrome 121) 121)
(check-in-part  'b 1/6 (longest-palindrome 51) '(1 5))
(check-exp-part 'c 1/6 (longest-palindrome 1214) 121)
(check-exp-part 'd 1/6 (longest-palindrome 5121) 121)
(check-exp-part 'e 1/6 (longest-palindrome 5122145215) 1221)
(check-exp-part 'f 1/6 (longest-palindrome 5122145213125) 5213125)


(sumar)