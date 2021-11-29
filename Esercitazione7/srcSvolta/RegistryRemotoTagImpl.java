/**
 * 	Implementazione del Registry Remoto.
 *	Metodi descritti nelle interfacce.  
 */

import java.rmi.Naming;
import java.rmi.RMISecurityManager;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class RegistryRemotoTagImpl extends UnicastRemoteObject implements
	RegistryRemotoTagServer {
		private static final String[] tags= {"Tag1","Tag2","Tag3","Tag4","Parmenide"};
	// num. entry [nomelogico][ref]
	final int tableSize = 100;

	// Tabella: la prima colonna contiene i nomi, la seconda i riferimenti remoti, la terza l'eventuale tag
	Object[][] table = new Object[tableSize][3];

	public RegistryRemotoTagImpl() throws RemoteException {
		super();
		for (int i = 0; i < tableSize; i++) {
			table[i][0] = null;			// nome logico
			table[i][1] = null;			// riferimento remoto
			table[i][2] = null;			// eventuale tag
		}
	}

	/** Aggiunge la coppia nella prima posizione disponibile */
	public synchronized boolean aggiungi(String nomeLogico, Remote riferimento)
			throws RemoteException {
		// Cerco la prima posizione libera e la riempio
		boolean risultato = false;
		if( (nomeLogico == null) || (riferimento == null) )
			return risultato;
		for (int i = 0; i < tableSize; i++)
			if (table[i][0] == null) {
				table[i][0] = nomeLogico;
				table[i][1] = riferimento;
				risultato = true;
				break;
			}
		return risultato;
	}

  /** Restituisce il riferimento remoto cercato, oppure null */
	public synchronized Remote cerca(String nomeLogico) throws RemoteException {
		Remote risultato = null;
		if( nomeLogico == null ) return null;
		for (int i = 0; i < tableSize; i++)
			if ( nomeLogico.equals((String) table[i][0]) ) {
				risultato = (Remote) table[i][1];
				break;	
			}
		return risultato;
	}

	/** Restituisce tutti i riferimenti corrispondenti ad un nome logico */
	public synchronized Remote[] cercaTutti(String nomeLogico)
			throws RemoteException {
		int cont = 0;
		if( nomeLogico == null ) return new Remote[0];
		for (int i = 0; i < tableSize; i++)
			if ( nomeLogico.equals((String) table[i][0]) )
				cont++;
		Remote[] risultato = new Remote[cont];
		// Ora lo uso come indice per il riempimento
		cont = 0;
		for (int i = 0; i < tableSize; i++)
			if ( nomeLogico.equals((String) table[i][0]) )
				risultato[cont++] = (Remote) table[i][1];
		return risultato;
	}

	/** Restituisce tutti i riferimenti corrispondenti ad un nome logico */
	public synchronized Object[][] restituisciTutti() throws RemoteException {
		int cont = 0;
		for (int i = 0; i < tableSize; i++)
			if (table[i][0] != null) cont++;
		Object[][] risultato = new Object[cont][2];
		// Ora lo uso come indice per il riempimento
		cont = 0;
		for (int i = 0; i < tableSize; i++)
			if (table[i][0] != null) {
				risultato[cont][0] = table[i][0];
				risultato[cont][1] = table[i][1];
			}
		return risultato;
	}

	/** Elimina la prima entry corrispondente al nome logico indicato */
	public synchronized boolean eliminaPrimo(String nomeLogico)
			throws RemoteException {
			boolean risultato = false;
			if( nomeLogico == null ) return risultato;    
			for (int i = 0; i < tableSize; i++)
				if ( nomeLogico.equals((String) table[i][0]) ) {
					table[i][0] = null;
					table[i][1] = null;
					risultato = true;
					break;
				}
			return risultato;
	}

	public synchronized boolean eliminaTutti(String nomeLogico)
			throws RemoteException {
		boolean risultato = false;
		if( nomeLogico == null ) return risultato;    
		for (int i = 0; i < tableSize; i++)
			if ( nomeLogico.equals((String) table[i][0]) ) {
				if (risultato == false)
        	risultato = true;
				table[i][0] = null;
				table[i][1] = null;
			}
		return risultato;
	}

	@Override
	public synchronized boolean associaTag(String tag, String nomeLogico) throws RemoteException {
		boolean risultato = false;
		if (nomeLogico == null || tag == null)
			return risultato;
		for (int i = 0; i < tableSize; i++)
			if ( nomeLogico.equals((String) table[i][0]) ) {
				if (table[i][2] == null) {
					table[i][2] = tag;
					if (!risultato)
						risultato = true;
				}
			}
		return risultato;
	}


	/* Codice  copiato da cercaTutti*/
	@Override
	public Remote[] cercaTag(String tag) throws RemoteException {
		int cont = 0;
		if( tag == null ) return new Remote[0];
		for (int i = 0; i < tableSize; i++)
			if ( tag.equals((String) table[i][2]) )
				cont++;
		Remote[] risultato = new Remote[cont];
		// Ora lo uso come indice per il riempimento
		cont = 0;
		for (int i = 0; i < tableSize; i++)
			if ( tag.equals((String) table[i][2]) )
				risultato[cont++] = (Remote) table[i][2];
		return risultato;
	}

	// Avvio del Server RMI
	public static void main(String[] args) {

		int registryRemotoPort = 1099;
		String registryRemotoHost = "localhost";
		String registryRemotoName = "RegistryRemoto";
		String tag = "";

		// Controllo dei parametri della riga di comando
		if (args.length != 0 && args.length != 1 && args.length != 2) {
			System.out.println("Sintassi: ServerImpl [registryPort] [tag]");
			System.exit(1);
		}
		if (args.length == 1) {
			try {
				registryRemotoPort = Integer.parseInt(args[0]);
			} catch (Exception e) {
				System.out
				.println("Sintassi: ServerImpl [registryPort] [tag], registryPort intero");
				System.exit(2);
			}
		}
		if (args.length == 2) {
			registryRemotoPort = Integer.parseInt(args[0]);
			tag = args[1];
		}


		// Impostazione del SecurityManager
		if (System.getSecurityManager() == null)
			System.setSecurityManager(new RMISecurityManager());

		// Registrazione del servizio RMI
		String completeName = "//" + registryRemotoHost + ":" + registryRemotoPort
				+ "/" + registryRemotoName;
		try {
			RegistryRemotoTagImpl serverRMI = new RegistryRemotoTagImpl();
			Naming.rebind(completeName, serverRMI);

			if (tag != " ") {
				serverRMI.associaTag(tag, completeName); // completeName è il nomeLogico ????
				System.out.println("Server RMI: Servizio \"" + registryRemotoName
						+ " [Tag: " + tag + "]" +"\" registrato");
			}

			System.out.println("Server RMI: Servizio \"" + registryRemotoName
					+ "\" registrato");
		} catch (Exception e) {
			System.err.println("Server RMI \"" + registryRemotoName + "\": "
					+ e.getMessage());
			e.printStackTrace();
			System.exit(1);
		}
	}

	public void stampa() {
		System.out.println("Ecco il contenuto aggiornato del registry:\n");
		for(int i=0;i<this.tableSize;i++) {
			if(this.table[i][0]!=null) {
				System.out.println("Nome logico n."+(i+1)+": "+(String)this.table[i][0]);
				if(this.table[i][2]!=null){
					System.out.println("e con il tag;"+(String)this.table[i][2]);
				}
			}
		}
	}
}