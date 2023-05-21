/*MICLIUS Razvan-Gabriel - 314CB*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t_graf_lista.h"
#include "task1.h"

#define INT_MAX ~(1 << 31)
#define STRSIZE 16

/*
 * Constante:
 *         INT_MAX   - Nu stiam daca pot importa limits.h
 *         STRSIZE   - Marimea maxima aleasa arbitrar pentru un sir
 *
 * citeste_graf_task1:
 *         in        - fisierul de input
 * Returneaza:
 *         graf      - un graf neorientat (succes)
 *         NULL      - esec
 * Variabile:
 *         intrare   - fisierul de input
 *         n_noduri  - numar noduri
 *         n_arce    - numar arce
 *         i         - iterator clasic
 *         cost      - variabila auxiliara in care se citeste costul
 *         asocieri  - gigavectorul de caractere ce face corespondenta
 *                     nod - sir
 *         buffer    - variabila auxiliara (buffer) in care citesc stringul
 *                     pentru a evalua
 *         index_st  - indexul nodului de la care pleaca legatura
 *         index_dr  - indexul nodului la care ajunge legatura
 *         aux       - variabila auxiliara prin care fac legatura in lista de
 *                     arce
 *        parcurgere - la fel ca aux
 *         graf      - graful
 *   contor_asocieri - numarul de cuvinte deja introduse in asocieri
 * Functia creeaza graful neorientat ce respecta tiparul fisierelor de input
 * de la cerinta 1.
 * Mai intai, se citesc numarul de noduri si numarul de arce, si graful se
 * initializeaza. Apoi, pentru fiecare arc citim in fisier perechea de noduri
 * si costul.
 * Indexarea nodurilor se face prin vectorul de cuvinte asocieri, in care se
 * incearca gasirea sirului echivalent cu cel citit in buffer. Daca nu s-a
 * gasit, se adauga in lista. Altfel, index_st va contine nodul de la care
 * pleaca legatura, iar index_dr nodul la care se duce. Apoi, se introduc
 * ordonat in listele corespunzatoare arcele.
 */

graf_lista_adiacenta *
citeste_graf_task1(char *in)
{
    FILE *intrare = NULL;
    unsigned int n_noduri = 0, n_arce = 0;
    unsigned int i = 0;
    int cost = 0;
    char *asocieri = NULL;
    char *buffer = NULL;
    unsigned int contor_asocieri = 0;
    unsigned int index_st = 0;
    unsigned int index_dr = 0;
    graf_lista_adiacenta *graf = NULL;
    lista_adiacenta aux = NULL;
    lista_adiacenta *parcurgere = NULL;
/******************************************************************************
 *                              STOP INITIALIZARI                             *
 * ***************************************************************************/
    intrare = fopen(in, "rt");
    if (!intrare)
        return NULL;
    fscanf(intrare, "%u %u", &n_noduri, &n_arce);
    asocieri = calloc(STRSIZE, n_noduri);
    if (!asocieri)
        goto eroare_aloc_asocieri;
    buffer = calloc(sizeof(char), STRSIZE);
    if (!buffer)
        goto eroare_aloc_buffer;
    graf = graf_init(n_noduri);
    if (!graf)
        goto eroare_aloc_graf;
    for (; i < n_arce; i++) {
        index_st = 0;
        index_dr = 0;
        fscanf(intrare, "%s ", buffer);
        for (; index_st < contor_asocieri; index_st++) {
            if (strcmp(buffer, asocieri + STRSIZE * index_st) == 0)
                break;
        }
        if (index_st == contor_asocieri) {
            memcpy(asocieri + contor_asocieri * STRSIZE, buffer, STRSIZE);
            contor_asocieri++;
        }
        fscanf(intrare, "%s ", buffer);
        for (; index_dr < contor_asocieri; index_dr++) {
            if (strcmp(buffer, asocieri + STRSIZE * index_dr) == 0)
                break;
        }
        if (index_dr == contor_asocieri) {
            memcpy(asocieri + contor_asocieri * STRSIZE, buffer, STRSIZE);
            contor_asocieri++;
        }
        fscanf(intrare, "%d ", &cost);
        parcurgere = &graf->lista_arce[index_st];
        while (*parcurgere && (*parcurgere)->destinatie < index_dr)
            parcurgere = &((*parcurgere)->urm);
        aux = calloc(sizeof(celula_adiacenta), 1);
        if (!aux)
            goto eroare_aloc_aux;
        aux->urm = *parcurgere;
        aux->destinatie = index_dr;
        aux->cost = cost;
        *parcurgere = aux;
        parcurgere = &graf->lista_arce[index_dr];
        while (*parcurgere && (*parcurgere)->destinatie < index_st)
            parcurgere = &((*parcurgere)->urm);
        aux = calloc(sizeof(celula_adiacenta), 1);
        if (!aux)
            goto eroare_aloc_aux;
        aux->urm = *parcurgere;
        aux->destinatie = index_st;
        aux->cost = cost;
        *parcurgere = aux;
    }
    fclose(intrare);
    free(asocieri);
    free(buffer);
    return graf;

    //  Erori
eroare_aloc_aux:
    graf_distr(&graf);
eroare_aloc_graf:
    free(buffer);
eroare_aloc_buffer:
    free(asocieri);
eroare_aloc_asocieri:
    fclose(intrare);
    return NULL;
}

/******************************************************************************
 *                           NUMAR ELEMENTE CONEXE                            *
 * ***************************************************************************/

/*
 * aux_parcurgere_adancime:
 *         graf      - graful pentru care se realizeaza parcurgerea
 *         vizier    - vectorul ce contine 0 pentru elemente nevizitate, sau
 *                     indexul componentei conexe din care face parte nodul
 *         index     - nodul pentru care se face parcurgerea
 *       index_conex - indexul componentei conexe (pentru a actualiza vizier)
 * Returneaza:
 *         1         - nodul a fost vizitat deja
 *         0         - nodul nu a fost vizitat si s-a realizat parcurgerea pe
 *                     copii sai
 * Variabile:
 *         aux       - variabila cu care se realizeaza parcurgerea listei
 * Parcurgere in adancime cinstita, singurul element aparte este modificare
 * vectorului de vizitati, astfel incat acesta sa contina indexul elementei
 * conexe in loc de 1.
 */

static unsigned short
aux_parcurgere_adancime(graf_lista_adiacenta *graf, unsigned int *vizier,
                        unsigned int index, unsigned int index_conex)
{
    lista_adiacenta aux = NULL;
    if (vizier[index])
        return 1;
    aux = graf->lista_arce[index];
    vizier[index] = index_conex;
    while (aux) {
        aux_parcurgere_adancime(graf, vizier, aux->destinatie, index_conex);
        aux = aux->urm;
    }
    return 0;
}

/*
 * numar_comp_conexe:
 *         graf      - graful pentru care se realizeaza parcurgerea
 *         vizier    - vectorul ce va contine indicele componentei conexe
 *                     din care face parte fiecare nod
 * Returneaza:
 *       comp_conexe - numarul de componente conexe
 * Variabile:
 *       comp_conexe - numarul de componente conexe
 *         i         - iterator clasic
 * Daca se iese din parcurgerea in adancime, insa un nod a ramas nevizitat,
 * rezulta ca acel nod face parte dintr-o alta componenta conexa. Astfel, se
 * incrementeaza comp_conexe si se incepe parcurgerea de la noul nod.
 */

unsigned int
numar_comp_conexe(graf_lista_adiacenta *graf, unsigned int *vizier)
{
    unsigned int comp_conexe = 0;
    unsigned int i = 0;
    for (; i < graf->nr_noduri; i++) {
        if (vizier[i] == 0) {
            comp_conexe++;
            aux_parcurgere_adancime(graf, vizier, i, comp_conexe);
        }
    }
    return comp_conexe;
}

/******************************************************************************
 *                            ALGORITMUL LUI PRIM                             *
 * ***************************************************************************/

/*
 * Lista folosita pentru a alege muchia optima in fiecare iteratie. Elementele
 * ei vor fi inserate ordonat.
 */

typedef struct celula_lista_prim {
    lista_adiacenta muchie;
    struct celula_lista_prim *urm;
} celula_prim, *lista_prim;

/*
 * lista_prim_adauga:
 *         lista     - lista in care se va insera noua muchie
 *         muchie    - muchia ce trebuie inserata
 * Returneaza:
 *         0         - nu a reusit alocarea
 *         1         - s-a schimbat inceputul listei
 *         2         - s-a introdus in alta pozitie
 * Variabile:
 *         aux       - celula care va fi legata in lista
 *         p         - variabila cu care se parcurge lista pentru a gasi
 *                     pozitia lui aux
 *         ant       - celula anterioara, care trebuie legata la aux
 * Functia insereaza in mod ordonat in lista un nou element ce contine muchia
 * cu prioritatea cea mai mare pentru algoritmul lui Prim.
 */

static unsigned short
lista_prim_adauga(lista_prim *lista, lista_adiacenta muchie)
{
    lista_prim aux = calloc(sizeof(celula_prim), 1);
    lista_prim p = NULL, ant = NULL;
    if (!aux)
        return 0;
    aux->muchie = muchie;
    if ((!(*lista)) || muchie->cost < (*lista)->muchie->cost) {
        aux->urm = *lista;
        *lista = aux;
        return 1;
    }
    p = (*lista)->urm;
    ant = *lista;
    while (p) {
        if (muchie->cost < p->muchie->cost)
            break;
        ant = p;
        p = p->urm;
    }
    ant->urm = aux;
    aux->urm = p;
    aux->muchie = muchie;
    return 2;
}

/*
 * lista_purifica:
 *         lista     - lista din care se vor elimina celule
 *        destinatie - nodul pentru care se elimina celulele
 * Variabile:
 *         aux       - celula care va fi eliminata din lista
 *         p         - variabila cu care se parcurge lista pentru a gasi
 *                     pozitia elementelor de eliminat
 *         ant       - celula anterioara, care trebuie legata la aux -> urm
 * Functia elimina din lista toate celulele ce au o muchie care se indreapta
 * catre destinatie.
 */

static void
lista_purifica(lista_prim *lista, unsigned int destinatie)
{
    lista_prim p = NULL, ant = NULL, aux = NULL;
    while ((*lista) && (*lista)->muchie->destinatie == destinatie) {
        ant = *lista;
        *lista = (*lista)->urm;
        free(ant);
    }
    if (!(*lista))
        return;
    ant = *lista;
    p = (*lista)->urm;
    while (p) {
        if (p->muchie->destinatie == destinatie) {
            ant->urm = p->urm;
            free(p);
            p = ant;
        }
        ant = p;
        p = p->urm;
    }
}

/*
 * lista_extrage_min:
 *         lista     - lista din care se extrage elementul cu prioritate cea
 *                     mai mare, in sensul algoritmului lui Prim
 * Returneaza:
 *         muchie    - muchia cu cea mai mare prioritate in sensul lui Prim
 *         NULL      - lista este goala
 * Variabile:
 *         min       - celula care va fi extrasa din lista
 *         muchie    - muchia cu cea mai mare prioritate in sensul lui Prim
 * Functia extrage muchia cu cea mai mare prioritate. Dat fiind ca lista este
 * ordonata, aceasta va fi intotdeauna prima.
 */

static lista_adiacenta
lista_extrage_min(lista_prim *lista)
{
    lista_prim min = *lista;
    lista_adiacenta muchie = NULL;
    if (!min)
        return NULL;
    muchie = min->muchie;
    *lista = (*lista)->urm;
    free(min);
    return muchie;
}

/*
 * fcomp:
 *         a         - parametrul unu pentru functia de comparare qsort
 *         b         - parametrul doi pentru functia de comparare qsort
 * Returneaza:
 *         relatia de ordine dintre cele doua elemente
 * Functie de sortare pentru qsort. Nimic aparte.
 */

static int
fcomp(const void *a, const void *b)
{
    return (*(int *)a) - (*(int *)b);
}

/*
 * algoritm_prim:
 *         graf      - graful pe care aplicam algoritmul lui prim
 *         nr_conexe - numarul de elemente conexe din graf
 *         masca     - vector ce contine pentru fiecare nod indexul componentei
 *                     conexe din care face parte
 *         componente_conexe - vector ce contine pentru fiecare componenta
 *                             conexa primul nod din aceasta
 * Returneaza:
 *         sume      - vectorul sortat ce contine suma costurilor drumurilor
 *                     pentru fiecare componenta conexa in parte
 *         NULL      - nu s-a reusit alocarea
 * Variabile:
 *         lista     - lista de prioritati pentru muchii
 *         vizitati  - vector ce tine cont de ce noduri au fost vizitate
 *         sume      - vectorul sortat ce contine suma costurilor drumurilor
 *                     pentru fiecare componenta conexa in parte
 *         min       - valoarea cu care se va gasi muchia cu cel mai mic cost
 *         start     - nodul de la care se porneste
 *         i         - iterator clasic
 *         p         - variabila auxiliar cu care se parcurge lista muchiilor
 * 1. start devine nod din fiecare componenta conexa.
 * 2. vizitati[start] devine 1
 * 3. adaugam in lista de muchii toate muchiile ce pornesc de la start si
 *    nu au ca destinatie un nod deja vizitat
 * 4. alegem din lista de muchii cea mai buna muchie
 * 5. start devine nodul catre care se duce aceasta muchie
 * 6. eliminam din lista de muchii toate muchiile ce duc la start
 * 7. adaugam in componenta conexa corespunzatoare acelui nod costul muchiei
 * 8. daca muchia extrasa este catre un nod deja vizitat, implicit am terminat
 *    pentru componenta conexa actuala. daca nu, ne intoarcem la pasul 2.
 */

unsigned int *
algoritm_prim(graf_lista_adiacenta *graf, unsigned int nr_conexe,
              unsigned int *masca, unsigned int *componente_conexe)
{
    lista_prim lista = NULL;
    int *vizitati = NULL;
    unsigned int *sume = NULL;
    int min = INT_MAX;
    unsigned int start = 0;
    unsigned int i = 0;
    lista_adiacenta p = NULL;
/******************************************************************************
 *                              STOP INITIALIZARI                             *
 * ***************************************************************************/
    vizitati = calloc(graf->nr_noduri, sizeof(int));
    if (!vizitati)
        return NULL;
    sume = calloc(nr_conexe, sizeof(int));
    if (!sume) {
        free(vizitati);
        return NULL;
    }
    for (; i < nr_conexe; i++) {
        start = componente_conexe[i];                           //  1.
        do {                                                    //
            vizitati[start] = 1;                                //  2.
            p = graf->lista_arce[start];                        //  3.
            while (p) {                                         //  3.
                if (vizitati[p->destinatie] == 0)               //  3.
                    lista_prim_adauga(&lista, p);               //  3.
                p = p->urm;                                     //  3.
            }                                                   //  3.
            p = lista_extrage_min(&lista);                      //  4.
            if (!p)                                             //
                break;                                          //
            start = p->destinatie;                              //  5.
            lista_purifica(&lista, start);                      //  6.
            sume[masca[start] - 1] += p->cost;                  //  7.
            if (vizitati[start] == 1)                           //  8.
                p = NULL;                                       //  8.
        } while (lista || p);                                   //  8.
    }
    free(vizitati);
    qsort(sume, nr_conexe, sizeof(int), fcomp);
    return sume;
}
