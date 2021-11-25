import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RegistryRemotoTagServer extends Remote, RegistryRemotoServer, RegistryRemotoTagClient {
    public boolean associaTag(String tag, String nomeLogico) throws RemoteException;
}
