#include "operazioni.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <rpc/rpc.h>

FS_Out *file_scan_1_svc(char **nomeFile, struct svc_req *rp){
    static FS_Out result;
    
    
    
    printf("Nome file ricevuto: %s\n", *nomeFile);

    int f;
    if((f = open(*nomeFile, O_RDONLY)) < 0){
        printf("Impossibile aprire file: %s\n", *nomeFile);
        result.numChar = -1;
        return &result;
    }
    char c;
    int n, chars = 0, words = 0, lines = 0;
    while((n = read(f, &c, 1) > 0)){
        if(c == ' '){
            words++;
        }else if(c == '\n'){
            lines++;
        }else{
            chars++;
        }
    }
    close(f);
    if(chars == 0){
        printf("Nessun carattere nel file\n");
        result.numChar = -1;
        return &result;
    }
    printf("File: %s\tChars: %d\tWords: %d\tLines: %d\n", *nomeFile, chars, words, lines);
    result.numChar= chars;
    result.numWords = words;
    result.numLines = lines;
    return &result;

}

int *dir_scan_1_svc(DirScan_In *d, struct svc_req *rp){
    static int result;
    DIR *dir;
    struct dirent * dd;
    int count = 0;
    int fd;
    char path[MAXNAMLEN];
    
    if((dir = opendir(d->direttorio)) == NULL){
		result = -420;
		return (&result);
	}
    while ((dd = readdir(dir)) != NULL){
        if(dd->d_type == DT_REG){
            sprintf(path,"%s/%s", d->direttorio, dd->d_name);
            if((fd = open(path, O_RDONLY)) != -1){
                if((lseek(fd,0,SEEK_END)) > d->soglia){
                    close(fd);
                    count++;
                }
            }else{
                count = 69;
            }
        }
    }
    printf("Numero totale di file %d\n", count);
    closedir(dir);
    
    result = count;
    return &result;
}
