/**
 *  Interfaccia remota Registry per il Cliente.
 *  	Cerca = ottiene il primo riferimento al server registrato con 'nomeLogico'.
 *  	CercaTutti = ottiene tutti i riferimenti ai server registrati con 'nomeLogico'.
 */

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RemOp extends Remote {
	public int conta_righe(String nomeFile, int num) throws RemoteException;
	public int elimina_righe(String nomeFile, int numLinea) throws RemoteExceptions;
}
