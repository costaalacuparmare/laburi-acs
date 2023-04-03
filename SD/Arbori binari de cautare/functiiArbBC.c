#include "arbBC.h"

/* Aloca un element de tip Arb si returneaza pointerul aferent */
TArb Constr_Frunza(int elem) {
    TArb aux = (TArb) malloc(sizeof(TNod));
    if (!aux) 
        return NULL;

    aux->info = elem;
    aux->st = aux->dr = NULL;

    return aux;
}


int InserareABC(TArb *arbore, int elem) {
    TArb p, n, aux;
    
    if(*arbore == NULL) {
        *arbore = Constr_Frunza(elem);
        if(!*arbore) return 0;
        return 1;
    }

    n = *arbore;
    while (n) {
        if (elem == n->info) 
            return 0;

        p = n;
        if (elem > n->info) 
            n = n->dr;
        else 
            n = n->st;
    }

    aux = Constr_Frunza(elem);
    if(!aux)
        return 0;
    if(p->info > elem)
        p->st = aux;
    else    
        p->dr = aux;
    return 1;
}

/* Parcurgere Radacina - Stanga - Dreapta */
void RSD(TArb a) {
	if (!a) {
        printf("-"); 
        return;
    }
	
    if (!a->st && !a->dr) {          /* conditie frunza */
        printf(" %d ", a->info);      
        return;
    }
	
    printf(" %d ", a->info);
	printf("(");
	
    RSD(a->st);                      /* apelare recursiva */
	printf(",");
	
    RSD(a->dr);                      /* apelare recursiva */
	printf(")");
}

void DRS(TArb a) {
    if (!a) {
        printf("-");
        return;
    }

    if (!a->st && !a->dr) {          /* conditie frunza */
        printf(" %d ", a->info);
        return;
    }

    DRS(a->dr);                      /* apelare recursiva */
    printf(",");


    printf(" %d ", a->info);
    printf("(");

    DRS(a->st);                      /* apelare recursiva */
    printf(")");
}

/* Dezalocare memorie arbore */
void DistrugeArb(TArb* adrArbore) {
    if (!(*adrArbore)) {
        return;
    }

    DistrugeArb(&(*adrArbore)->st);
    DistrugeArb(&(*adrArbore)->dr);

    free(*adrArbore);
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

/*- afiseaza arborele r -*/
void AfiArb(TArb r) 
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

/* Ex1 Lab 5 afiseaza info mai mici decat x, nr de valori prin drs */

void DRS_Num(TArb a, int x, int *nr) {
    if (!a)
        return;

    DRS_Num(a->dr,x,nr);

        if (a->info < x) {
            printf("%d ", a->info);
            (*nr)++;
        }

    DRS_Num(a->st,x,nr);
}

int Numara(TArb r, int x) {
    int nr = 0;
    if(!r) return 0;
    printf("Elemente mai mari decat %d: ", x);
    DRS_Num(r,x,&nr);
    printf("\n");
    return nr;
}

/* Ex1 Lab 5 afiseaza nivelul daca info mai mici decat x sunt pe acelasi sau -1 */

int NrNiv (TArb r) {
    int ns = 0, nd = 0;
    if (!r) return 0;
    ns = NrNiv(r->st);
    nd = NrNiv(r->dr);
    return 1 + (ns >= nd ? ns : nd);
}

int Check_Niv (TArb r, int x, int nivCrt, int niv) {
    if(!r) return 0;
    if (nivCrt == niv)
        if (r->info < x)
            return 1;
        else
            return 0;
    return Check_Niv(r->st,x,nivCrt+1,niv) && Check_Niv(r->dr,x,nivCrt+1,niv);
}

int Verif(TArb r, int x) {
    int niv = NrNiv(r);
    int i = 0;
    for(; i < niv; i++) {
        int Check = Check_Niv(r,x,0,i);
        if (Check == 1)
            return 1;
    }
    return -1;

}