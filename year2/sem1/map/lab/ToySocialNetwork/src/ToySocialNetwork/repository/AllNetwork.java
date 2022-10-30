package ToySocialNetwork.repository;

import ToySocialNetwork.domain.Network;

public class InMemoryNetwork {
    private Network network;

    public InMemoryNetwork() {
        network = new Network();
    }
}
