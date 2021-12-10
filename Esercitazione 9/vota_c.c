#include "vota.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <rpc/rpc.h>


int main (int argc , char argv[])
{   char *host ; CLIENT *cl;
    int *ris , *start_ok ; void * in;
    Tab *tab ; Input input;
    char str[5]; char c, ok[256];
    char candidato[50], op;
    int i , j, riga, col;
    if (argc != 2)
    {
    printf ("usage: %s server_host \n", argv[0]);
    exit(1);
    }
    host = argv[1];
    
    cl = clnt_create (host, VOTA, VOTAVERS, "udp");
    if (cl == NULL)
    {
        clnt_pcreateerror (host); exit (1);}
e 
    printf("Inserire: \nG) per vedere i giudici \tV) per esprimere il voto  \t^D per terminare:");
    
    while (gets (ok))
    {   if(strcmp (ok,"V")==0)
        {
            printf("\nInserisci nome candidato: ");
            scanf("%s", candidato); 
            
            printf("\nInserisci tipo operazione (A o S): ");
             scanf("%c", &op); //leggo e controllo
    while(op != 'A' && op!='S')
    {
        printf("Lettera sbagliata! Inserisci A (aggiunta) o S (sottrazione): \n");
        scanf("%c", &op);}
    input.op = op;
    strcpy(input.cand, candidato);
        
    gets(ok);//Consumo fine linea
    
    
    ris= esprimi_voto_1_svc(&input, c1);
    // Invocazione remota
    if(ris == NULL) {clnt_perror (cl, host); exit(1); }
    if(*ris <0) printf("Problemi... \n");
    else printf("Operazione effettuata con successo! \n");
    }   // if V


    else if(strcmp(ok,"G")==0
    {// Invocazione remota
        tab= classifica_giudici_1_svc(in,cl);
        if(tab == NULL) { clnt_perror(cl, host);
        exit(1);}
        printf("Stato di occupazione della tab \n");
        //TODO stampare tabella in base all'inizializzazione
        for(i =0; i <NUMFILE; i++)
        { 
            for(j=0; j<LUNGHFILA;j++)
            printf("%c\t", tab->fila[i].posto[j]);
            printf("\n");
        }
    } // if G
    else
    printf("Argomento di ingresso errato \n");
   printf("Inserire: \nG) per vedere i giudici \tV) per esprimere il voto  \t^D per terminare:");
    } // while
    // Libero le risorse , distruggendo il gestore di trasporto
    clnt_destroy(cl);
    exit (0);
    
}// main
