import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

public class Client {
    // Avvio del Client RMI
    public static void main(String[] args) {
        final int REGISTRYPORT = 1099;
        String registryHost = null;                    //host remoto con registry
        //String serviceName = "Server";		//lookup name...Hardcoded
        String serviceName = "";
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));

        // Controllo dei parametri della riga di comando
        if (args.length != 2) {
            System.out.println("Sintassi: RMI_Registry_IP ServiceName");
            System.exit(1);
        }
        registryHost = args[0];
        serviceName = args[1];

        System.out.println("Invio richieste a " + registryHost + " per il servizio di nome " + serviceName);

        // Connessione al servizio RMI remoto
        try {
            String completeName = "//" + registryHost + ":" + REGISTRYPORT + "/"
                    + serviceName;
            RemOp serverRMI = (RemOp) Naming.lookup(completeName);
            System.out.println("ClientRMI: Servizio \"" + serviceName + "\" connesso");

            System.out.println("\nRichieste di servizio fino a fine file");

            String service;
            System.out.print("Servizio (C=Conta Righe, E=Elimina Riga): ");


            String fileName;
            int occ, numLinea;

            /*ciclo accettazione richieste utente*/
            while ((service = stdIn.readLine()) != null) {

                if (service.equals("C")) {
                    int res;
                    System.out.print("Inserisci nome file: ");
                    fileName = stdIn.readLine();

                    System.out.print("Inserisci numero minimo occorrenze: ");
                    occ = Integer.parseInt(stdIn.readLine());

                    try {
                        res = serverRMI.conta_righe(fileName, occ);

                    } catch (RemoteException e) {
                        e.getMessage();
                        continue;
                    }
                    System.out.println("Numero righe con numero parole maggiore del min indicato: " + res);
                } // C = Conta Righe

                else if (service.equals("E")) {
                    int res;
                    System.out.print("Inserisci nome file: ");
                    fileName = stdIn.readLine();

                    System.out.print("Inserisci numero linea da eliminare: ");
                    numLinea = Integer.parseInt(stdIn.readLine());

                    try {
                        res = serverRMI.elimina_righe(fileName, numLinea);

                    } catch (Exception e) {
                        e.getMessage();
                        continue;
                    }
                    System.out.println("Numero righe del nuovo file: " + res);
                } // E = Elimina Righe

                else System.out.println("Servizio non disponibile");

                System.out.print("Servizio (C=Conta Righe, E=Elimina Righe): ");
            } // while (!EOF), fine richieste utente

        } catch (NotBoundException nbe) {
            System.err.println("ClientRMI: il nome fornito non risulta registrato; " + nbe.getMessage());
            //nbe.printStackTrace();
            System.exit(1);
        } catch (Exception e) {
            System.err.println("ClientRMI: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }
}

