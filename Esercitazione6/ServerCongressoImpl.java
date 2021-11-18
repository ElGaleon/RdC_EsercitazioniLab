/**
 * ServerImpl.java
 * 		Implementazione del server
 * */

import java.rmi.Naming;
import java.rmi.RMISecurityManager;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class ServerCongressoImpl extends UnicastRemoteObject implements
    ServerCongresso {
  static Programma prog[];

  // Costruttore
  public ServerCongressoImpl() throws RemoteException {
    super();
  }

  /* Conta righe che abbiano numero parole maggiore di $min */
  public int conta_righe(String nomeFile, int min) throws RemoteException {
      int res = 0, int occ = 0;
      File f;
      System.out.println("Server RMI: richiesto conteggio righe");

      f = new File(nomeFile);   // Creazione file
    // Creating an object of BufferedReader class
    BufferedReader br = new BufferedReader(new FileReader(f));
    String st;

    while ((st = br.readLine()) != null)
        if (st.split(' ').length > min)
          res++;
  }
      return res;
  }

  /* Elimina righe */
  public int conta_righe(String nomeFile, int numLinea) throws RemoteException {
    int res = 0;
    System.out.println("Server RMI: richiesta elimina righe");
    return result;
  }


  // Avvio del Server RMI
  public static void main(String[] args) {

    // creazione programma
    prog = new Programma[3];
    for (int i = 0; i < 3; i++)
      prog[i] = new Programma();
    int registryRemotoPort = 1099;
    String registryRemotoName = "RegistryRemoto";
    String serviceName = "ServerCongresso";

    // Controllo dei parametri della riga di comando
    if (args.length != 1 && args.length != 2) {
      System.out
          .println("Sintassi: ServerCongressoImpl NomeHostRegistryRemoto [registryPort], registryPort intero");
      System.exit(1);
    }
    String registryRemotoHost = args[0];
    if (args.length == 2) {
      try {
        registryRemotoPort = Integer.parseInt(args[1]);
      } catch (Exception e) {
        System.out
            .println("Sintassi: ServerCongressoImpl NomeHostRegistryRemoto [registryPort], registryPort intero");
        System.exit(2);
      }
    }

    // Impostazione del SecurityManager
    if (System.getSecurityManager() == null) {
      System.setSecurityManager(new RMISecurityManager());
    }

    // Registrazione del servizio RMI
    String completeRemoteRegistryName = "//" + registryRemotoHost + ":"
        + registryRemotoPort + "/" + registryRemotoName;

    try {
      RegistryRemotoServer registryRemoto = (RegistryRemotoServer) Naming
          .lookup(completeRemoteRegistryName);
      ServerCongressoImpl serverRMI = new ServerCongressoImpl();
      registryRemoto.aggiungi(serviceName, serverRMI);
      System.out.println("Server RMI: Servizio \"" + serviceName
          + "\" registrato");
    } catch (Exception e) {
      System.err.println("Server RMI \"" + serviceName + "\": "
          + e.getMessage());
      e.printStackTrace();
      System.exit(1);
    }
  }
}