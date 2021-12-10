#include "sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <rpc/rpc.h>

/*STATO SERVER*/
static Sala sala; // variabile per la sala
static int inizializzato = 0// inizializzazione attuata
void inizializza() //Possibilità 1
{
    int i, j;
    if(inizializzato== 1) return;
    //inizializzazione struttura dati
    for( i= 0; i< NUMFILE; i++){
    for(j= 0; j <LUNGHFILA; j++)
    sala.fila[i].posto[j]='L';
    //Eventuale riempimento altri posti
    sala.fila[1].posto[0]='D';
    sala.fila[2].posto[1]='P'
    sala.fila[5].posto[2]='P';
    //...
    inizializzato = 1;
    printf("Terminata init struttura dati !\n");
}

/*Procedure*/
int prenota_postazione_1_svc(Input *input struct svc_req *rqstp)
{
    static int result =-1;
    result=-1;
    inizializza();//Invoco l’inizializzazione
    if(sala.fila[input->fila].posto[input->colonna] !='L')
    return(&result);
    else
    {
    sala.fila[input->fila].posto[input->colonna] = input->tipo;
    result=0; return(&result);
    }
}//prenota_postazione

Sala* visualizza_stato_1_svc(void *in, struct svc_req *rqstp)
{
    inizializza(); //Invoco l’inizializzazione
    return (&sala);
} //visualizza_stato



