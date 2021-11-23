import java.io.*;

/**
 * ServerImpl.java
 * 		Implementazione del server
 * */

import java.rmi.Naming;
import java.rmi.RMISecurityManager;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

import java.io.*;
import java.rmi.Naming;
import java.rmi.RMISecurityManager;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

// TODO: cercare di implementare l'algoritmo con la lettura carattere per carattere perch pi veloce e, se possibile, fare temporizzazioni a confronto
//aggiornamento: lettura a carattere non testata (implementata e commentata sotto)
public class Server extends UnicastRemoteObject implements RemOp {

    // Costruttore
    public Server() throws RemoteException {
        super();
    }

    /* Conta righe che abbiano numero parole maggiore di $min */
    public int conta_righe(String nomeFile, int min) throws RemoteException {
        int res = 0;
        File f;
        System.out.println("Server RMI: richiesto conteggio righe");

        f = new File(nomeFile);   // Creazione file
        if (f.isDirectory()) {
            throw new RemoteException("Il file ? una directory");
        }
        // Creating an object of BufferedReader class
        try {
            BufferedReader br = new BufferedReader(new FileReader(f));
            String st;
            int i;
            long start, end;
            char c;
            start=System.currentTimeMillis();
            while (  (st= br.readLine()) != null) {
                if (st.split(" ").length > min) { // le parole della riga sono maggiori del min inserito dall'utente
                    res++;
                }
            }
//lettura char incompleta
           /* StringBuilder stb = new StringBuilder();
                 while ((i=br.read()) != -1) {
            	c = (char)i;
            	stb.append(c);
            	 if(c=='\n'){
            		 st=stb.toString();
            	if(st.split(" ").length > min) // le parole della riga sono maggiori del min inserito dall'utente
                   res++;
                }
                }*/
            
            /*int contap=0;
	    char prevC='0';
             while ((i=br.read()) != -1) {
        	c = (char)i;
		if((c>='a' && c<='z') || (c>='A' && c<='Z') && contap==0)contap++; //controllo prima parola (nel caso in cui non ci siano spazi)
        	if(c==' ' && (prevC != ' ' && prevC!='0')) contap++;
        	 if(c=='\n'){
            if (contap > min) { // le parole della riga sono maggiori del min inserito dall'utente
               res++;
            }
            contap=0;
            }
           
        }*/
            end=System.currentTimeMillis();
            br.close();
            System.out.println("Tempo ContaRighe"+ Long.toString(end-start) + " millisecondi");
        } catch (Exception e) {
            System.out.println("Lancio eccezione a Client");
            throw new RemoteException("Il file indicato non pu? essere aperto");
        }

        return res;
    }


    /* Elimina righe */
    public int elimina_righe(String nomeFile, int numLinea) throws RemoteException {
        int riga = 1;
        File f, fOut;
        System.out.println("Server RMI: richiesta elimina righe");

        f = new File(nomeFile);   // Apertura file
        if(!f.exists()){
            throw new RemoteException("Il file non esiste\n");
        }
        if (f.isDirectory()) {
            throw new RemoteException("Il file e' un direttorio\n");
        }
        
        fOut = new File(nomeFile+"_eliminaRighe.txt");  //Creazione file
        try {
            if (fOut.createNewFile()){
                System.out.println("File " + fOut + " is created!");
            } else {
                System.out.println("File " + fOut + " already exists.");
            }
        } catch (IOException i)  {
            throw new RemoteException("Impossibile creare file output\n");
        }

        try {// Creating an object of BufferedReader class
            //BufferedReader br = new BufferedReader(new FileReader(f));
            BufferedReader br = new BufferedReader(new FileReader(nomeFile));
            BufferedWriter brOut = new BufferedWriter(new FileWriter(fOut));
            String st;
            char c;
            int i;
            long start, end;
            boolean eliminata = false;
            start=System.currentTimeMillis();
            while ((st = br.readLine()) != null) {
                if (riga != numLinea) { // riga diversa da quella che si vuole eliminare
                    brOut.write(st+"\n");    // scrivo riga nel file modificato
                } else {
                    eliminata = true;
                }
                riga++;
            }
            if(numLinea > riga){
                br.close();
                brOut.close();
                fOut.delete();
                throw new RemoteException("Numero di linea eccessivo\n");
            }
           /* while ((i=br.read()) != -1) {
            	c = (char)i;
                if (riga != numLinea) { // riga diversa da quella che si vuole eliminare
                    brOut.write(c);    // scrivo char riga nel file modificato
                } else {
                    eliminata = true;
                }
                if(c=='\n')riga++; //se incontro fine riga, incremento la variabile
            }*/
            end=System.currentTimeMillis();
            br.close();
            brOut.close();
            if (eliminata == false) { // Restituisco eccezione se il numero di linea inserito e' maggiore delle righe del file
                throw new RemoteException("Nessuna riga eliminata\n");
            }

            System.out.println("Tempo EliminaRighe "+ Long.toString(end-start) + " millisecondi");
        }catch (Exception e) {
            System.out.println("Eccezione:\n" + e.getMessage());
            throw new RemoteException(e.getMessage());
        }

        return riga-2;
    }


    // Avvio del Server RMI
    public static void main(String[] args) {
        final int REGISTRYPORT = 1099;
        String registryHost = "localhost";
        String serviceName = "RemOp";		//lookup name...

        // Registrazione del servizio RMI
        String completeName = "//" + registryHost + ":" + REGISTRYPORT + "/"
                + serviceName;
        try{
        	Server serverRMI = new Server();
            Naming.rebind(completeName, serverRMI);
            System.out.println("Server RMI: Servizio \"" + serviceName
                    + "\" registrato");
        }
        catch(Exception e){
            System.err.println("Server RMI \"" + serviceName + "\": "
                    + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }

    }
}