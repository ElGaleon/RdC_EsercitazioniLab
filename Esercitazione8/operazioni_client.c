#include "operazioni.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <rpc/rpc.h>

#define MAX_NAME_LENGHT 256
#define MAX_SOGLIA 50   // Massimo 50 cifre

int main(int argc, char **argv){
    char *server; 
    CLIENT *cl;

    DirScan_In d_Input;
    char nomeFile[MAX_NAME_LENGHT];

    int *risDir;
    FS_Out *f_Result;
    
    if(argc != 2){
        fprintf(stderr, "Usage: %s host\n", argv[0]); 
        exit(1);
    }

    server = argv[1];

    cl = clnt_create(server, OPERAZIONIPROG, OPERAZIONIVERS, "udp");
    if (cl == NULL) { clnt_pcreateerror(server);exit(1);}

    char service[2];
    printf("Quale servizio vuoi utilizzare?\nPer FileScan: FS\tPer DirScan: DS\n");
    while(gets(service)){
        if(strcmp("FS", service) == 0){
            printf("Servizio FileScan: inserisci il nome del file\n");

            //char nomeFile[MAX_NAME_LENGHT];
            gets(nomeFile);

            f_Result = file_scan_1(&nomeFile, cl);

            if(f_Result == NULL){
                printf("Servizio FileScan: Errore RPC\n");
                clnt_perror(cl, server); 
                exit(1);
            }
            if (f_Result->numChar == -1){
                printf("Servizio FileScan: Errore nel risultato"); 
                printf("Quale servizio vuoi utilizzare?\nPer FileScan: FS\tPer DirScan: DS\n");
                continue;
            }

            printf("Servizio FileScan: Risultato da %s\nChars: %d\tWords: %d\tLines: %d\n", server, f_Result->numChar, f_Result->numWords, f_Result->numLines);

            free(nomeFile);

        }else if(strcmp("DS", service) == 0){
            printf("Servizio DirScan: inserisci il nome del direttorio\n");

            char dirName[MAX_NAME_LENGHT];
            gets(dirName);

            printf("Servizio DirScan: inserisci la soglia\n");
            char sogliaString[MAX_SOGLIA];
            gets(sogliaString);
            int soglia = atoi(sogliaString);
            if(soglia <= 0){
                printf("Servizio DirScan: soglia non valida\n");
                printf("Quale servizio vuoi utilizzare?\nPer FileScan: FS\tPer DirScan: DS\n");
                continue;
            }

            
            d_Input.direttorio = dirName;
            d_Input.soglia = soglia;
            printf("dirName: %s\tsoglia: %d\n", d_Input.direttorio, d_Input.soglia);
            risDir = dir_scan_1(&d_Input, cl);
            if(risDir == NULL){
                printf("Servizio DirScan: Errore RPC\n");
                clnt_perror(cl, server); 
                exit(1);
            }
            if (risDir < 0){
                printf("Servizio DirScan: Errore nel risultato"); 
                printf("Quale servizio vuoi utilizzare?\nPer FileScan: FS\tPer DirScan: DS\n");
                continue;
            }

            printf("Servizio DirScan: Risultato da %s %d\n", server, *risDir);
            
            
        }else{
            printf("Servizio invalido\n");
        }
        printf("Quale servizio vuoi utilizzare?\nPer FileScan: FS\tPer DirScan: DS\n");
    }
    

    clnt_destroy(cl);
}