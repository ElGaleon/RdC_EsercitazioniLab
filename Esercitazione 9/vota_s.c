#include "vota.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <rpc/rpc.h>


/*const N=7;//LUNGHFILA
const NUMCOL=6;//NUMFILE*/

/*STATO SERVER*/
static Elenco elenco;
static Tab tab;
static int inizializzato = 0;// inizializzazione attuata



void inizializza() //Possibilità 1
{
    printf("Inizializzo struttura dati !\n");
    int i, j;
    if(inizializzato== 1) return;
    //inizializzazione struttura dati
    for( i= 0; i< N; i++){
       tab.show[i].candidato="L";
       tab.show[i].giudice="L";
       tab.show[i].categoria= 'L';
       tab.show[i].nomeFile="L";
       tab.show[i].fase='L';
       tab.show[i].voto= -1;
         
    }
   
    //Eventuale riempimento altri posti
    tab.show[2].candidato="Brasco";
    tab.show[2].giudice="Bowie";
    tab.show[2].categoria='U';
    tab.show[2].nomeFile="BrascoProfile.txt";
    tab.show[2].fase='A';
    tab.show[2].voto=100;
    
    tab.show[3].candidato="Viga";
    tab.show[3].giudice="Winehouse";
    tab.show[3].categoria='D';
    tab.show[3].nomeFile="VigaProfile.txt";
    tab.show[3].fase='S';
    tab.show[3].voto=150;
    
    tab.show[4].candidato="Io";
    tab.show[4].giudice="Mika";
    tab.show[4].categoria='D';
    tab.show[4].nomeFile="MioProfile.txt";
    tab.show[4].fase='S';
    tab.show[4].voto=110;
    
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
    
    for( i= 0; i< N; i++){
        if(strcmp(tab.show[i].candidato, input->cand)==0){
            if(input->op == '+'){
                tab.show[i].voto += 1;}
            if(input->op == '-'){
                if((tab.show[i].voto-1)>=0)
                    tab.show[i].voto -= 1;
                
            }
            result=0;
        }
        
     }
     
     if(result == -1){
            perror("il candidato non esiste!\n");
            exit(1);
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


Elenco *classifica_giudici_1_svc(void *in, struct svc_req *rqstp)
{
    inizializza(); //Invoco l’inizializzazione
    
    G g[N];
    int j=0, k, l;
    int isIn = 0;
    static Elenco result;
    
    printf("inizializzo array G\n");
    //inizializzo array G
     for(k=0; k<N; k++){
               strcpy(g[k].nome,"L");
                g[k].votoTot = 0;  
            }
             printf("costruisco array G\n");
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
                 printf(" nome: %s\n",g[j].nome);
                 g[j].votoTot += tab.show[i].voto;
                j++; //tengo il conto del riempimento di G
            }//altrimenti le operazioni che servivano sono già state fatte
            isIn =0;
        }
    }
    
     printf("ordino array G\n");
    //ordino G
     quickSortE(g, j);
    
      printf("assegno a result\n");
     //result
    for(int i=0, k=0; i<j; i++, k++){
        elenco.nome[i].c= g[k].nome;
         printf(" elenco.nome: %s\n",elenco.nome[i].c);
    }
    if(j==0) {
         printf(" result null\n");
        return NULL;
    }
    
    return (&elenco);
    
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
			while (i < j && compareE(a[i],pivot) > 0) i++; //compare
			while (j > i && compareE(a[j], pivot) <= 0) j--;
			if (i < j) scambiaE(i, j, a);
		} while (i < j);
		// determinati i due sottoinsiemi 
	// posiziona il pivot 
		if (i != iPivot && compareE(a[i],a[iPivot]) != 0)
		{
			scambiaE(i, iPivot, a);
			iPivot = i;
		}
		// ricorsione sulle sottoparti, se necessario 
		if (iniz < iPivot - 1)
			quickSortRE(a, iniz, iPivot - 1);
		if (iPivot + 1 < fine)
			quickSortRE(a, iPivot + 1, fine);
	} //(iniz < fine) 
}
