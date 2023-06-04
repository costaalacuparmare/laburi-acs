/*-- testLG.c -- prelucrare lista generica de pointeri la puncte din plan */
#include "thash.h"
#include <string.h>

/* persoana are un nume si un nr de telefon
telefonul are forma 0701234567 (10 caractere intre 0-9)+ \0.
primul caracter este '0' */
typedef struct {char*nume, telMobil[11];}TPers;


/*generez un cod  unic pe baza primei litere din nume */
int codHashNume(void*a)
{
	char *p=((TPers*)a)->nume;
	return *p - 'a';
}

void AfiElPers(void * ae)
{
  TPers *p = (TPers*)ae;
  printf("[%s %s]\n ", p->nume, p->telMobil);
}

TLG GenerareListaPers(size_t nrPers)
{
	/*citesc in ordine pentru nr pers
		numele - o linie de max 100 caractere
		nr telefon - o linie max 10 caractere+\0
	 */
	int i, succes;
	char buf[100];
	TLG r=NULL;
	TPers p;
	for(i=0;i<nrPers;i++)
	{
		fgets(buf,99, stdin);
		p.nume=strdup(buf);
		p.nume[strlen(p.nume)-1]='\0';
		if(!p.nume)
			return r;
		fgets(buf,99,stdin);
		strncpy(p.telMobil, buf,10);
		p.telMobil[10]='\0';
		succes=InsLG(&r,&p,sizeof(TPers));
		if(!succes)
			return r;
	}
	return r;
}

//functii care compara 2 persoane dupa nume respectiv dupa telefon
int cmpPersNume(void *p1,void*p2)
{
	return strcmp( ((TPers*)p1)->nume,((TPers*)p2)->nume );
}

int cmpPersTel(void *p1,void*p2)
{
	return strcmp( ((TPers*)p1)->telMobil,((TPers*)p2)->telMobil );
}

/* functie care elibereaza spatiul alocat pentru o persoana
este folosita de DistrTH */
void elibPers(void * p)
{
	free( ((TPers*)p)->nume);
}


TH* GenerareHash(TLG listaPers)
{
	TH *h1 = IniTH(26, codHashNume);
	if (!h1) {
		printf("oroare");
		return NULL;
	}
	for (TLG p = listaPers; p != NULL; p = p->urm) {
		int codificare = h1->fh(p->info);
		TLG *lista = h1->v + codificare;
		InsLG(lista, p->info, sizeof(TPers));
	}
	return h1;
}

int NumaraPersoane(TH *h, char * prefixTel) {
	int k = 0;
	for (int i = 0; i < h->M; i++) {
		TLG *lista = h->v + i;
	}
}

int main()
{ 
 	TLG x = NULL;
 	TH *h1=NULL;
  	/* recomand sa aveti un fisier text cu linii
	nume pers
	nr telefon */

	x = GenerareListaPers(3);
    if(!x)
    {
        printf("Lista nu a putut fi generata\n");
        return 0;
    }
    
  	Afisare(&x, AfiElPers);
    
	// se decomenteaza dupa ce se genereaza tabela hash
	h1=GenerareHash(x);
    printf("tabela hash nume \n");
	AfiTH(h1, AfiElPers);
  	
    /* secvente de test */

  
  	Distruge(&x, elibPers);
	/*  se decomenteaza dupa ce se genereaza tabela hash 
	DistrTH(&h1, elibPers); */
  	return 0;
}
