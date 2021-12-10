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
static Tab tab;
static int inizializzato = 0// inizializzazione attuata

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
       tab.show[i].candidato = "L";
       tab.show[i].giudice = "L";
       tab.show[i].categoria= 'L';
       tab.show[i].nomeFile= "L";
       tab.show[i].fase='L';
       tab.show[i].voto= -1;
         
    }
   
    //Eventuale riempimento altri posti
    tab.show[2].candidato="Brasco";
    tab.show[2].giudice="Bowie";
    tab.show[2].categoria='U';
    tab.show[2].categoria="BrascoProfile.txt";
    tab.show[2].nomeFile='A';
    tab.show[2].voto=100;
    
    tab.show[3].candidato="Viga";
    tab.show[3].giudice="Winehouse";
    tab.show[3].categoria='D';
    tab.show[3].categoria="VigaProfile.txt";
    tab.show[3].nomeFile='S';
    tab.show[3].voto=50;
    
    inizializzato = 1;
    printf("Terminata init struttura dati !\n");
}

/*Procedure*/
int * esprimi_voto_1_svc(Input *input struct svc_req *rqstp)
{
   /* int voto = 0;
    printf("\nInserire voto: ");
    scanf("%d", &voto);*///prodecura remota, non ha senso chiedere ulteriori dati
    static int result =-1;
    result=-1;
    inizializza();//Invoco l’inizializzazione
    
     for( i= 0; i< N; i++){
        if(strcmp(tab.show[i].candidato, input->cand)==0){
            if(strcmp(input->op, "A")==0){
                tab.show[i].voto += 1;//variabile voto?
                result=0 ;
            }
            if(strcmp(input->op, "S")==0){
                tab.show[i].voto -= 1;
                result=0;
            }
        }
     }
    return(&result);
}//esprimi_voto

//TODO
Tab* classifica_giudici_1_svc(void *in, struct svc_req *rqstp)
{
    inizializza(); //Invoco l’inizializzazione
    
    
     /*for( i= 0; i< N; i++){
        tab.show[i].candidato = "L";
       tab.show[i].giudice = "L";
       tab.show[i].categoria= 'L';
       tab.show[i].nomeFile= "L";
       tab.show[i].fase='L';
       tab.show[i].voto= -1;
    }*/
     
     
    return (&tab);
} //classifica_giudici



