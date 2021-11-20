import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RemOp extends Remote {
    int conta_righe(String nomeFile, int min) throws RemoteException;
    int elimina_righe(String nomeFile, int numLinea) throws RemoteException;
}