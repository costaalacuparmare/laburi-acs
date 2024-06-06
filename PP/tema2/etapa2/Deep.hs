module Deep where

import Shallow (Point, Region, Transformation)
import qualified Shallow as S

{-
    Deep embeddings pentru regiuni și transformări. Fiecare regiune
    și transformare este reprezentată sub forma unui arbore sintactic
    (abstract syntax tree, AST) ce descrie secvența de operații care contribuie
    la construcția acelei regiuni sau transformări. De exemplu, expresia
    (circles 2), unde circles a fost definită în etapa 1, ar produce acum
    un rezultat similar cu

    Union (Circle 2.0) (Transform (Translation 6.0 0.0) (Circle 2.0)).

    Pentru a obține acest efect, toate funcțiile din etapa 1 sunt reimplementate
    astfel încât să utilizeze direct constructorul de date potrivit al unui
    tip de date. De exemplu, funcția fromPoints *este* acum constructorul
    FromPoints.

    Primul avantaj major al reprezentării bazate pe AST-uri este posibilitatea
    interpretării acesteia în diverse moduri pentru a reconstitui semnificații
    concrete variate ale regiunilor și transformărilor, e.g. regiuni ca funcții
    caracteristice, și transformări ca funcții pe puncte, ca în etapa 1.
    Vom vedea și alte semnificații concrete în etapa 3.

    Al doilea mare avantaj îl constituie posibilitatea simplificării AST-ului
    înaintea interpretării lui într-o manieră specifică. Observați deja cum
    funcțiile combineTransformations și applyTransformation de mai jos, văzute
    ca smart constructors, recunosc anumite cazuri particulare și simplifică
    AST-ul încă de la construcție.
-}
data RegionAST
    = FromPoints [Point]
    | Rectangle Float Float
    | Circle Float
    | Complement RegionAST
    | Union RegionAST RegionAST
    | Intersection RegionAST RegionAST
    | Transform TransformationAST RegionAST
    deriving (Show, Eq)

data TransformationAST
    = Translation Float Float
    | Scaling Float
    | Combine [TransformationAST]
    deriving (Show, Eq)

fromPoints :: [Point] -> RegionAST
fromPoints = FromPoints

rectangle :: Float -> Float -> RegionAST
rectangle = Rectangle

circle :: Float -> RegionAST
circle = Circle

complement :: RegionAST -> RegionAST
complement = Complement

union :: RegionAST -> RegionAST -> RegionAST
union = Union

intersection :: RegionAST -> RegionAST -> RegionAST
intersection = Intersection

translation :: Float -> Float -> TransformationAST
translation = Translation

scaling :: Float -> TransformationAST
scaling = Scaling

{-
    Smart constructor: dacă lista de transformări este singleton, înlocuiește
    lista cu unica transformare din listă; altfel, utilizează constructorul
    de date Combine.
-}
combineTransformations :: [TransformationAST] -> TransformationAST
combineTransformations [transformation] = transformation
combineTransformations transformations = Combine transformations

{-
    Smart constructor: dacă se dorește aplicarea unei liste vide de transformări
    asupra unei regiuni, întoarce regiunea ca atare; altfel, utilizează
    constructorul de date Transform.
-}
applyTransformation :: TransformationAST -> RegionAST -> RegionAST
applyTransformation (Combine []) region = region
applyTransformation transformation region = Transform transformation region

{-
    Implementați funcția toTransformation, care constituie o interpretare
    a AST-ului unei transformări (TransformationAST), în vederea recuperării
    reprezentării concrete din etapa 1, sub forma unei funcții cu tipul
    Transformation = (Point -> Point).

    Nu este necesar să implementați de la zero, ci puteți invoca direct
    funcțiile din etapa 1, prefixându-le cu "S." (observați la începutul acestui
    fișier linia "import qualified Shallow as S"). Mai precis, funcțiile
    neprefixate, e.g. translation, sunt cele din acest fișier, iar funcțiile
    prefixate, e.g. S.translation, sunt cele din modulul Shallow.
-}
toTransformation :: TransformationAST -> Transformation
toTransformation (Translation x y) = S.translation x y
toTransformation (Scaling x) = S.scaling x
toTransformation (Combine transformations) = S.combineTransformations $ map
                                             toTransformation transformations

{-
    Implementați funcția toRegion, care constituie o interpretare a AST-ului
    unei regiuni (RegionAST), în vederea recuperării reprezentării concrete
    din etapa 1, sub forma unei funcții caracteristice cu tipul
    Region = (Point -> Bool).
-}
toRegion :: RegionAST -> Region
toRegion (FromPoints points) = S.fromPoints points
toRegion (Rectangle x y) = S.rectangle x y
toRegion (Circle r) = S.circle r
toRegion (Complement region) = S.complement $ toRegion region
toRegion (Union region1 region2) = S.union (toRegion region1)
                                  (toRegion region2)
toRegion (Intersection region1 region2) = S.intersection (toRegion region1)
                                          (toRegion region2)
toRegion (Transform transformation region) = S.applyTransformation
                                             (toTransformation transformation)
                                             (toRegion region)

{-
    Varianta actualizată a a funcției inside.
-}
inside :: Point -> RegionAST -> Bool
inside = flip toRegion

{-
    Implementați funcția decomposeTransformation, care descompune o transformare
    oricât de complexă într-o listă de transformări elementare (translații
    și scalări), conservând bineînțeles ordinea acestora.

    Constrângeri: evitați recursivitatea explicită.

    Hint: valorificați ordinea de sus în jos de realizare a pattern matching-ului,
    pentru a scurta descrierea cazurilor.

    Exemple:

    > decomposeTransformation $ Translation 1 2
    [Translation 1.0 2.0]

    > decomposeTransformation $ Scaling 2
    [Scaling 2.0]

    > decomposeTransformation $
        Combine [ Translation 1 2
                , Combine [ Translation 3 4
                          , Scaling 2
                          ]
                , Scaling 3
                ]
    [Translation 1.0 2.0,Translation 3.0 4.0,Scaling 2.0,Scaling 3.0]
-}
decomposeTransformation :: TransformationAST -> [TransformationAST]
decomposeTransformation (Combine transformations) = concatMap
                                                    decomposeTransformation
                                                    transformations
decomposeTransformation (Translation x y) = [Translation x y]
decomposeTransformation (Scaling x) = [Scaling x]

{-
    Implementați funcția fuseTransformations, care alipește transformările
    adiacente de același fel (translații cu translații și scalări cu scalări)
    dintr-o listă de transformări elementare (translații și scalări),
    și întoarce lista transformărilor rezultante.

    Constrângeri: evitați recursivitatea explicită.

    > fuseTransformations [Translation 1 2]
    [Translation 1.0 2.0]

    > fuseTransformations [Scaling 2, Scaling 3]             
    [Scaling 6.0]

    > fuseTransformations [ Translation 1 2, Translation 3 4
                          , Scaling 2, Scaling 3
                          , Translation 5 6
                          ]
    [Translation 4.0 6.0,Scaling 6.0,Translation 5.0 6.0]
-}
fuseTransformations :: [TransformationAST] -> [TransformationAST]
fuseTransformations transformations = foldr f [] transformations
    where f (Translation x y) (Translation x' y' : rest) =
            Translation (x + x') (y + y') : rest
          f (Scaling x) (Scaling x' : rest) = Scaling (x * x') : rest
          f transformation acc = transformation : acc


{-
    Implementați funcția optimizeTransformations, care simplifică toate
    transformările din AST-ul unei regiuni. Principiile sunt următoarele:

    * Transformările succesive trebuie descompuse și alipite.
    * Pentru a evidenția lanțuri cât mai lungi de transformări succesive,
      se urmărește deplasarea în sus a transformărilor din AST, astfel:
      * Complementul unei transformări este transformarea complementului.
      * O ramificare (reuniune sau intersecție) de transformări de regiuni
        presupune determinarea celui mai lung prefix de transformări comune
        de pe cele două ramuri și deplasarea acestuia deasupra ramificării,
        păstrând sub ea sufixele de transformări necomune.
    * O regiune elementară (din puncte, dreptunghi sau cerc) se consideră
      optimizată.
    * Toate cosmetizările de mai sus se realizează după optimizarea recursivă
      a subregiunilor.
    
    Constrângeri: evitați duplicarea codului.

    Hints:

    * case pentru pattern matching în interiorul altor expresii
    * smart constructors: combineTransformation, applyTransformation

    Exemple:

    > optimizeTransformations $
        Transform (Combine [ Translation 1 2
                           , Combine [ Translation 3 4
                                     , Scaling 2
                                     ]  
                           , Scaling 3
                           ])
                  (Circle 5)
    Transform (Combine [Translation 4.0 6.0,Scaling 6.0]) (Circle 5.0)

    > optimizeTransformations $
        Transform (Combine [ Translation 1 2
                           , Combine [ Translation 3 4
                                     , Scaling 2
                                     ]  
                           , Scaling 3
                           ])
                  (Transform (Scaling 4)
                             (Transform (Scaling 2) (Circle 5)))
    Transform (Combine [Translation 4.0 6.0,Scaling 48.0]) (Circle 5.0)

    > optimizeTransformations $
        Complement (Transform (Scaling 4)
                              (Transform (Scaling 2) (Circle 5)))
    Transform (Scaling 8.0) (Complement (Circle 5.0))

    > optimizeTransformations $
        Transform (Combine [ Translation 1 2
                           , Combine [ Translation 3 4
                                     , Scaling 2
                                     ]  
                           , Scaling 3
                           ])
                  (Complement (Transform (Scaling 4)
                                         (Transform (Scaling 2) (Circle 5))))
    Transform (Combine [Translation 4.0 6.0,Scaling 48.0]) (Complement (Circle 5.0))

    > optimizeTransformations $
        Union (Complement (Transform (Scaling 4)
                                     (Transform (Scaling 2) (Circle 5))))
              (Rectangle 6 7)
    Union (Transform (Scaling 8.0) (Complement (Circle 5.0))) (Rectangle 6.0 7.0)

    > optimizeTransformations $
        Union (Transform (Combine [ Translation 1 2
                                  , Combine [ Translation 3 4
                                            , Scaling 2
                                            ]  
                                  , Scaling 3
                                  ])
                         (Complement (Transform (Scaling 4)
                                                (Transform (Scaling 2) (Circle 5)))))
              (Transform (Translation 4 6) (Rectangle 6 7))
    Transform (Translation 4.0 6.0)
              (Union (Transform (Scaling 48.0) (Complement (Circle 5.0)))
                     (Rectangle 6.0 7.0))
-}
--optimizeTransformations :: RegionAST -> RegionAST
optimizeTransformations fromPoints@(FromPoints _) = fromPoints
optimizeTransformations rectangle@(Rectangle _ _) = rectangle
optimizeTransformations circle@(Circle _) = circle

optimizeTransformations (Transform transformation (Transform transformation' regAst)) =
    let res = optimizeTransformations (Transform combTrans regAst)
        combTrans = (Combine (fuseTransformations lstTrans))
        lstTrans1 = decomposeTransformation transformation
        lstTrans2 = decomposeTransformation transformation'
        lstTrans = lstTrans1 ++ lstTrans2
    in res
optimizeTransformations (Transform transformation regAst) =
    let lstTrans = (fuseTransformations . decomposeTransformation) transformation
        newTrans = createNewTransform lstTrans
        createNewTransform (el:[]) = el
        createNewTransform lst = (Combine lst)
        optimizedRegAst = (optimizeTransformations regAst)
        createNewRegAst regAstVal@(Transform _ _) = optimizeTransformations (Transform newTrans (optimizeTransformations regAstVal))
        createNewRegAst regAstVal = (Transform newTrans (optimizeTransformations regAstVal))
    in createNewRegAst optimizedRegAst

optimizeTransformations (Complement (Transform transformation regAst)) =
    let nextRegAst = optimizeTransformations $ Complement regAst
    in optimizeTransformations (Transform transformation nextRegAst)

optimizeTransformations (Complement nextRegAst) = Complement $ optimizeTransformations nextRegAst

optimizeTransformations (Union regAst regAst1) =
    let optimizedReg = optimizeTransformations regAst
        optimizedReg1 = optimizeTransformations regAst1
        createNextReg (FromPoints fromPoints) (FromPoints fromPoints1) = case fromPoints == fromPoints1 of
            True -> regAst
            _ -> (Union optimizedReg optimizedReg1)
        createNextReg (Rectangle f1 f2) (Rectangle f3 f4) = case f1 == f3 && f2 == f4 of
            True -> regAst
            _ -> (Union optimizedReg optimizedReg1)
        createNextReg (Circle f) (Circle f1) = case f == f1 of
            True -> regAst
            _ -> (Union optimizedReg optimizedReg1)
        createNextReg (Transform (Combine (x:lst)) nextReg) (Transform (Combine (x1:lst1)) nextReg1) = case x == x1 of
            True -> (Transform x (optimizeTransformations (Union (Transform (Combine lst) nextReg) (Transform (Combine lst1) nextReg1))))
            _ -> (Union optimizedReg optimizedReg1)
        createNextReg (Transform (Combine (x:lst)) nextReg) (Transform x1 nextReg1) = case x == x1 of
            True -> (Transform x (optimizeTransformations (Union (Transform (Combine lst) nextReg) nextReg1)))
            _ -> (Union optimizedReg optimizedReg1)
        createNextReg (Transform x nextReg) (Transform (Combine (x1:lst1)) nextReg1) = case x == x1 of
            True -> (Transform x (optimizeTransformations (Union nextReg (Transform (Combine lst1) nextReg1))))
            _ -> (Union optimizedReg optimizedReg1)
        createNextReg (Transform x nextReg) (Transform x1 nextReg1) = case x == x1 of
            True -> (Transform x (optimizeTransformations (Union nextReg nextReg1)))
            _ -> (Union optimizedReg optimizedReg1)
        createNextReg reg1 reg2 = Union (optimizeTransformations reg1) $ optimizeTransformations reg2
    in createNextReg optimizedReg optimizedReg1

optimizeTransformations (Intersection regAst regAst1) =
    let optimizedReg = optimizeTransformations regAst
        optimizedReg1 = optimizeTransformations regAst1
        createNextReg (FromPoints fromPoints) (FromPoints fromPoints1) = case fromPoints == fromPoints1 of
            True -> regAst
            _ -> (Intersection optimizedReg optimizedReg1)
        createNextReg (Rectangle f1 f2) (Rectangle f3 f4) = case f1 == f3 && f2 == f4 of
            True -> regAst
            _ -> (Intersection optimizedReg optimizedReg1)
        createNextReg (Circle f) (Circle f1) = case f == f1 of
            True -> regAst
            _ -> (Intersection optimizedReg optimizedReg1)
        createNextReg (Transform (Combine (x:lst)) nextReg) (Transform (Combine (x1:lst1)) nextReg1) = case x == x1 of
            True -> (Transform x (optimizeTransformations (Intersection (Transform (Combine lst) nextReg) (Transform (Combine lst1) nextReg1))))
            _ -> (Intersection optimizedReg optimizedReg1)
        createNextReg (Transform (Combine (x:lst)) nextReg) (Transform x1 nextReg1) = case x == x1 of
            True -> (Transform x (optimizeTransformations (Intersection (Transform (Combine lst) nextReg) nextReg1)))
            _ -> (Intersection optimizedReg optimizedReg1)
        createNextReg (Transform x nextReg) (Transform (Combine (x1:lst1)) nextReg1) = case x == x1 of
            True -> (Transform x (optimizeTransformations (Intersection nextReg (Transform (Combine lst1) nextReg1))))
            _ -> (Intersection optimizedReg optimizedReg1)
        createNextReg (Transform x nextReg) (Transform x1 nextReg1) = case x == x1 of
            True -> (Transform x (optimizeTransformations (Intersection nextReg nextReg1)))
            _ -> (Intersection optimizedReg optimizedReg1)
        createNextReg reg1 reg2 = Intersection (optimizeTransformations reg1) $ optimizeTransformations reg2
    in createNextReg optimizedReg optimizedReg1