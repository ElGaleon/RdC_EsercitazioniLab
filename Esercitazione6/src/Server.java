import java.io.*;
import java.rmi.Naming;
import java.rmi.RMISecurityManager;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

// TODO: sistemare lancio delle eccezioni - non funzionante
// TODO: sistemare algoritmo elimina_righe: non sempre scrive nel nuovo file
// TODO: cercare di implementare l'algoritmo con la lettura carattere per carattere perché più veloce e, se possibile, fare temporizzazioni a confronto
public class Server extends UnicastRemoteObject implements RemOp {

    // Costruttore
    public Server() throws RemoteException {
        super();
    }

    /* Conta righe che abbiano numero parole maggiore di $min */
    public int conta_righe(String nomeFile, int min) throws RemoteException {
        int res = 0, occ = 0;
        File f;
        System.out.println("Server RMI: richiesto conteggio righe");

        f = new File(nomeFile);   // Creazione file
        if (f.isDirectory()) {
            throw new RemoteException("Il file è una directory");
        }
        // Creating an object of BufferedReader class
        try {
            BufferedReader br = new BufferedReader(new FileReader(f));
            String st;
            int i;

            while (  (st= br.readLine()) != null) {
                if (st.split(" ").length > min) { // le parole della riga sono maggiori del min inserito dall'utente
                    res++;
                }
            }
            br.close();
        } catch (Exception e) {
            System.out.println("Lancio eccezione a Client");
           throw new RemoteException("Il file indicato non può essere aperto");
        }

        return res;
    }


    /* Elimina righe */
    public int elimina_righe(String nomeFile, int numLinea) throws RemoteException {
        int res = 0, riga = 1;
        File f, fOut;
        System.out.println("Server RMI: richiesta elimina righe");

        f = new File(nomeFile);   // Creazione file
        fOut = new File(nomeFile+"_eliminaRighe.txt");

        if (f.isDirectory()) {
            throw new RemoteException();
        }

        try {// Creating an object of BufferedReader class
            BufferedReader br = new BufferedReader(new FileReader(f));
            BufferedWriter brOut = new BufferedWriter(new FileWriter(fOut));
            String st;
            boolean eliminata = false;

            while ((st = br.readLine()) != null) {
                if (riga != numLinea) { // riga diversa da quella che si vuole eliminare
                    brOut.write(st);    // scrivo riga nel file modificato
                } else {
                    eliminata = true;
                }
                riga++;
            }
            br.close();
            brOut.close();
            if (eliminata == false) { // Restituisco eccezione se il numero di linea inserito è maggiore delle righe del file
                throw new RemoteException();
            }

        }catch (Exception e) {
               throw new RemoteException();
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