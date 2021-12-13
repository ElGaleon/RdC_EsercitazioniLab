#include "vota.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <rpc/rpc.h>
/*
 col 0 = candidato
 col 1 = giudice
 col 2 = categoria
 col 3 = nome file
 col 4 = fase
 col 5 = voto
 */
/*const N=7;//LUNGHFILA
const NUMCOL=6;//NUMFILE*/

/*STATO SERVER*/
static Elenco e;
static Tab tab;
static int inizializzato = 0;// inizializzazione attuata

/*void inizializza() //Possibilità 1
{
    int i, j;
    if(inizializzato== 1) return;
    //inizializzazione struttura dati
    for( i= 0; i< N; i++){
    for(j= 0; j <NUMCOL; j++){
        if(j==NUMCOL-1) tab.riga[i].col[j]=-1;
         else tab.riga[i].col[j]='L';
         
    }
   
    //Eventuale riempimento altri posti
    tab.riga[1].col[0]="Brasco";
    tab.riga[1].col[1]="Bowie";
    tab.riga[1].col[2]='U';
    tab.riga[1].col[3]="BrascoProfile.txt";
    tab.riga[1].col[4]='A';
    tab.riga[1].col[5]=100;
    
    tab.riga[2].col[0]="Viga";
    tab.riga[2].col[1]="Winehouse";
    tab.riga[2].col[2]='D';
    tab.riga[2].col[3]="VigaProfile.txt";
    tab.riga[2].col[4]='S';
    tab.riga[2].col[5]=50;
    inizializzato = 1;
    printf("Terminata init struttura dati !\n");
}*/

void inizializza() //Possibilità 1
{
    int i, j;
    if(inizializzato== 1) return;
    //inizializzazione struttura dati
    for( i= 0; i< N; i++){
       strcpy(tab.show[i].candidato , "L");
       strcpy(tab.show[i].giudice , "L");
       tab.show[i].categoria= 'L';
       strcpy(tab.show[i].nomeFile,"L");
       tab.show[i].fase='L';
       tab.show[i].voto= -1;
         
    }
   
    //Eventuale riempimento altri posti
    strcpy(tab.show[2].candidato,"Brasco");
    strcpy(tab.show[2].giudice,"Bowie");
    tab.show[2].categoria='U';
    strcpy(tab.show[2].nomeFile,"BrascoProfile.txt");
    tab.show[2].fase='A';
    tab.show[2].voto=100;
    
    strcpy(tab.show[3].candidato,"Viga");
    strcpy(tab.show[3].giudice,"Winehouse");
    tab.show[3].categoria='D';
    strcpy( tab.show[3].nomeFile,"VigaProfile.txt");
    tab.show[3].fase='S';
    tab.show[3].voto=50;
    
    inizializzato = 1;
    printf("Terminata init struttura dati !\n");
}

/*Procedure*/

int * esprimi_voto_1_svc(Input *input, struct svc_req *rqstp)
{
   /* int voto = 0;
    printf("\nInserire voto: ");
    scanf("%d", &voto);*///prodecura remota, non ha senso chiedere ulteriori dati
    static int result =-1;
    result=-1;
    inizializza();//Invoco l’inizializzazione
    int i;
    
    /* for( i= 0; i< N; i++){
        if(strcmp(tab.show[i].candidato, input->cand)==0){
            if(strcmp(input->op, "A")==0){
                tab.show[i].voto += 1;
                result=0 ;
            }
            if(strcmp(input->op, "S")==0){
                tab.show[i].voto -= 1;
                result=0;
            }
        }
     }*/
    
    for( i= 0; i< N; i++){
        if(strcmp(tab.show[i].candidato, input->cand)==0){
                tab.show[i].voto += atoi(input->op);
        }
     }
     
    return(&result);
}//esprimi_voto




typedef struct {
    char nome[MAXS];
    int votoTot;
}G;

int compareE(G v1, G v2);
void scambiaE(int a, int b, G* v);
void quickSortE(G* a, int dim);
void quickSortRE(G* a, int iniz, int fine);

//TODO
Elenco *classifica_giudici_1_svc(void *in, struct svc_req *rqstp)
{
    inizializza(); //Invoco l’inizializzazione
    
    G g[N];
    int j=0, k, l;
    int isIn = 0;
    static Elenco result;
    
    //inizializzo array G
     for(k=0; k<N; k++){
               strcpy(g[k].nome, "L");
                g[k].votoTot = 0;  
            }
    //costruisco G
     for(int i= 0; i< N; i++){
         if(strcmp(tab.show[i].giudice, "L") != 0){//se il giudice nella main tab non è vuoto
             for( k=0; k<N; k++){
                 if(strcmp(g[k].nome, tab.show[i].giudice)==0){//controllo che il nome non sia già stato inserito in G
                     isIn=1;
                     g[k].votoTot += tab.show[i].voto;//se già inserito, sommo il voto totale
                }
            }
            if(!isIn){//inizializzazioni nome giudice e voto in G
                strcpy(g[j].nome, tab.show[i].giudice);
                 g[j].votoTot += tab.show[i].voto;
                j++; //tengo il conto del riempimento di G
            }//altrimenti le operazioni che servivano sono già state fatte
        }
    }
    
    //ordino G
     quickSortE(g, j);
    
     
     //result
    for(int i=0, k=0; i<j; i++, k++){
        strcpy(result.nome[i].c, g[k].nome);
    }
    if(j==0) return NULL;
    
    return (&result);
    
} //classifica_giudici

//funzioni varie per l'ordinamento
void scambiaE(int a, int b, G* v)
{
	G tmp = v[a];
	v[a] = v[b];
	v[b] = tmp;
}

int compareE(G v1, G v2) {//v[posMax] < v[i]
	int result;

	float tot1 = 0, tot2 = 0;

	result = v1.votoTot - v2.votoTot;

	return result;
}

void quickSortE(G* a, int dim)
{
	quickSortRE(a, 0, dim - 1);
}
void quickSortRE(G* a, int iniz, int fine)
{
	int i, j, iPivot;
	G pivot;
	if (iniz < fine)
	{
		i = iniz;
		j = fine;
		iPivot = fine;
		pivot = a[iPivot];
		do  //trova la posizione del pivot 
		{
			while (i < j && compareE(a[i],pivot) < 0) i++; //compare
			while (j > i&& compareE(a[j], pivot) >= 0) j--;
			if (i < j) scambiaE(i, j, a);
		} while (i < j);
		// determinati i due sottoinsiemi 
	// posiziona il pivot 
		if (i != iPivot && compareE(a[i],a[iPivot]) != 0)
		{
			scambiaE(i, iPivot, a); //occhio a scambia
			iPivot = i;
		}
		// ricorsione sulle sottoparti, se necessario 
		if (iniz < iPivot - 1)
			quickSortRE(a, iniz, iPivot - 1);
		if (iPivot + 1 < fine)
			quickSortRE(a, iPivot + 1, fine);
	} //(iniz < fine) 
}
