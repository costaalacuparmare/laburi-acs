/*--- auxarb.c --- functii de afisare si constructie arbore */
#include "tarb.h"
#include <stdarg.h>
#include <time.h>


TArb ConstrNod(int x, TArb s, TArb d)/* -> adresa nod (cu informatia x, 
				fiu stanga s, fiu dreapta d) sau NULL in caz de eroare */
{
	TArb aux = (TArb)malloc (sizeof(TNod));  /* incearca alocare spatiu */
	if (!aux) return NULL;                   /* spatiu insuficient */
	aux->info = x; aux->st = s; aux->dr = d; /* actualizeaza campurile nodului */

	return aux;                              /* intoarce adresa nodului */
}

TArb ConstrFr(int x)     /* -> adresa frunza cu informatia x, sau
					NULL daca nu exista spatiu */
{
	TArb aux = (TArb)malloc (sizeof(TNod));
	if (!aux) return NULL;
	aux->info = x; aux->st = aux->dr = NULL;

	return aux;
}

TArb ConstrAA (int lim, int nn, int v1, int v2)
/*- construieste un arbore de inaltime < lim, cu cel mult
	nn noduri cu chei in intervalul [vi,vs] -*/
{
	int niv;                /* nivel; inserarea se poate face pe nivel 0..lim-1 */
	TArb a = NULL, *aa;     /* a - arbore, aa - adresa arbore */

	srand(time(NULL));

	while (nn > 0) {          /* mai trebuie inserate noduri */
		for (niv = 0, aa = &a; niv < lim ; niv++) /* parcurgere in adancime */
			if (!(*aa)) {                               /* la adresa aa se poate insera */
				*aa = ConstrFr(rand() % (v2-v1+1) + v1);     /* incearca legare nod nou */
				if (!*aa)
					return a;                     /* nu mai exista spatiu */
				nn--;                                   /* scade numar noduri de inserat */
				break;
			} else
				aa = random(2) ? &(*aa)->dr : &(*aa)->st; /* avans dreapta sau stanga, aleator */
	}
	return a;
}

void distruge(TArb r) 	/* functie auxiliara - distruge toate nodurile */
{
	if (!r) return;
	distruge (r->st);     /* distruge subarborele stang */
	distruge (r->dr);     /* distruge subarborele drept */
	free (r);             /* distruge nodul radacina */
}

void DistrArb(TArb *a) /* distruge toate nodurile arborelui de la adresa a */
{
	if (!(*a)) return;       /* arbore deja vid */
	distruge (*a);           /* distruge toate nodurile */
	*a = NULL;               /* arborele este vid */
}

int NrNoduri(TArb r)        /* numarul de noduri din arborele r -*/
{
	if (!r) return 0;          /* arbore vid => 0 noduri */
	return 1 + NrNoduri(r->st) + NrNoduri(r->dr);
}

int NrNiv(TArb r)           /* numar niveluri (0 pentru arbore vid) */
{
	int ns, nd;
	if (!r) return 0;
	ns = NrNiv(r->st); nd = NrNiv(r->dr);
	return 1 + (ns >= nd ? ns : nd);
}


void Repr(TArb r, int centru, int linie, int dif, char desen[18][81], char cri[], int limita)
/*- functie auxiliara - pregateste desen arbore, cu radacina in centru linie+1
	 dif - distanta pe orizontala intre r si fiecare dintre cei doi descendenti
	 Exemple:  dif = 5    |        dif = 2    |
					 xxx                 xxx
				___/ \___              / \
			 |         |            |   |                               -*/
{
	int k;

	if (linie > limita) return;
	if (dif <= 1) {      /* spatiu de afisare insuficient -> ... */
		memset(desen[linie]+centru, '.', 3);
		return;
	}
	desen[linie][centru] = '|';      /* legatura spre nod */
	desen[linie][0] = ':';
	if (linie+1 > limita) return;
	sprintf(cri, "%3i", r->info);   /* converteste valoare info la 3 caractere */
	k = (cri[0] == ' ') ? 2 : 1;    /* decalaj fata de centru */
	memcpy(desen[linie+1] + centru - k, cri, 3); /* copiaza cele 3 caractere in desen */
	desen[linie+1][0] = ':';
	if (linie+2 > limita) return;
	if (r->st) {
		desen[linie+2][centru-1] = '/';                     /* reprezinta ramura  ____/  */
		desen[linie+2][0] = ':'; desen[linie+3][0] = ':';
		memset(desen[linie+2] + centru - dif + 1, '_', dif-2);
		Repr(r->st, centru - dif, linie + 3, (dif+1)/2, desen, cri, limita);   /* si subarborele stang */
	}
	if (r->dr) {
		desen[linie + 2][centru+1] = '\\';                  /* reprezinta ramura  \____  */
		desen[linie+2][0] = ':'; desen[linie+3][0] = ':';
		memset (desen[linie+2] + centru + 2, '_', dif-2);
		Repr(r->dr, centru + dif, linie + 3, (dif+1)/2, desen, cri, limita );   /* si subarborele drept */
	}
}

void AfiArb(TArb r) /*- afiseaza arborele r -*/
{
	int j;
	char desen[18][81], cri[] = "xxx";  /* zona reprezentare arbore, info */
	int limita = 17; 

	for (j = 0; j <= limita; j++)
		memset (desen[j], ' ', 79);
	if (!r)
		printf ("%49s", "-=- Arbore VID -=-");
	else {
		Repr(r,40,0,19, desen, cri, limita); /* preg reprezentare cu centrul in coloana 39 a primei linii */
		for (j = 0; j <= limita && desen[j][0] == ':'; j++) {
			desen[j][79] = '\0'; printf("%s\n", desen[j]+1);
		}
	}
	printf ("\n");
}

//Ex1 Lab4 - numara cate noduri sunt recursiv

int Numara (TArb r) {
    if (!r)
        return 0;
    if (r->dr != NULL && r->st != NULL) {
        if (r->info > (r->dr->info + r->st->info) / 2)
            return 1 + Numara(r->st) + Numara(r->dr);
        return Numara(r->st) + Numara(r->dr);
    }
}

//Ex2 Lab 4 - parcurgere sdr si nr cate noduri au doar un fiu pe dr

void Parcurgere (TArb r, int *nr_info) {
    if (!r)
        return;
    Parcurgere(r->st, nr_info);
    Parcurgere(r->dr, nr_info);
    if (r->st == NULL && r->dr != NULL) {
        printf("nod: %d\n", r->info);
        (*nr_info)++;
    }
}

//Ex3 Lab 4 - afiseaza daca toate nodurile non-frunze au 2 fii

int Verifica (TArb r) {
    if (!r)
        return 0;
    if ( !r->st && !r->dr)
        return 1;
    if(r->st && r->dr)
        return 1 && Verifica(r->st) && Verifica(r->dr);
    return 0;
}

//Ex2 Lab 6 - niv minim cu o frunza

int Check_Fr (TArb r, int niv) {
    if (r->st == NULL && r->dr == NULL)
        return niv;
    if (r->st == NULL)
        return Check_Fr(r->dr,niv+1);

    if (r->dr == NULL)
        return Check_Fr(r->st, niv+1);
    return MIN(Check_Fr(r->st, niv+1),Check_Fr(r->dr, niv+1));
}

//Ex3 Lab 6 - procent de numere deasupra unui niv care sunt pare

int nr_procent(TArb r, int niv, int nivCrt, int *val) {
    if (!r) return 0;
    if (nivCrt < niv) {
		if (r->info % 2 == 0)
			(*val)++;
		return 1 + nr_procent(r->st, niv, nivCrt + 1, val) + nr_procent(r->dr, niv, nivCrt + 1, val);
	}
		return 0;
}

float procent(TArb r, int n) {
	int val = 0;
	int nr = nr_procent(r,n,0,&val);
	if (nr == 0)
		return 0;
	return ((float) val/nr) * 100;
}

int NivSum(TArb r, int niv, int nivCrt) {
	if (!r) return 0;
	if (niv > NrNiv(r))
		return 0;
	if (nivCrt == niv)
		return r->info;
	else
		return NivSum(r->st, niv, nivCrt+1) + NivSum(r->dr, niv, nivCrt+1);
}

int NivSumMax (TArb r, int *sum) {
	if (!r) return 0;
	int niv = 0;
	for ( int i = 0; i < NrNiv(r); i++)
		if ( sum < NivSum(r,i,0)) {
			sum = NivSum(r, i, 0);
			niv = i;
		}
	return niv;
}