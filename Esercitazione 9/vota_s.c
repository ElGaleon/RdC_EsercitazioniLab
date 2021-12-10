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
static Giudici giudici; // variabile per i giudici
static int inizializzato = 0// inizializzazione attuata

void inizializza() //Possibilità 1
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
}

/*Procedure*/
int * esprimi_voto_1_svc(Input *input struct svc_req *rqstp)
{
    static int result =-1;
    result=-1;
    inizializza();//Invoco l’inizializzazione
    
     for( i= 0; i< N; i++){
        if(strcmp(tab.riga[i].col[0], input->cand)==0){
            if(strcmp(input->op, "A")==0){
                tab.riga[i].col[NUMCOL-1] += voto;//variabile voto?
                result=0 ;
            }
            if(strcmp(input->op, "S")==0){
                tab.riga[i].col[NUMCOL-1] -= voto;
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
    
    
     for( i= 0; i< N; i++){
    for(j= 0; j <NUMCOL; j++){
        if(j==NUMCOL-1) tab.riga[i].col[j]=-1;
         else tab.riga[i].col[j]='L';
         
    }
    return (&tab);
} //classifica_giudici



