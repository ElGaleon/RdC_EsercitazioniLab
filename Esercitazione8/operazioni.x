struct FS_Out{ 
                int numChar;
                int numWords;
                int numLines;
                };
struct DirScan_In{  
                string direttorio <50>;
                int soglia;
                };

program OPERAZIONIPROG {
   version OPERAZIONIVERS {
        FS_Out FILE_SCAN(string nomeFile) = 1;
        int DIR_SCAN(DirScan_In d) = 2;
    } = 1;
} = 0x20000013;