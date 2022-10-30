package ToySocialNetwork.repository;

import ToySocialNetwork.domain.User;
import ToySocialNetwork.exceptions.repository.ExistentUserException;
import ToySocialNetwork.exceptions.repository.ExistentFriendshipException;
import ToySocialNetwork.exceptions.repository.InexistentFriendshipException;
import ToySocialNetwork.exceptions.repository.InexistentUserException;

import java.util.*;

/**
 * Class that models a network
 */
public class Network {
    private Map<User, List<User>> network;

    /**
     * Constructor for the network class
     */
    public Network() {
        network = new HashMap<>();
    }

    /**
     * Method that adds a user to the network
     * @param user User
     * @throws ExistentUserException if the user is already in the network
     */
    public void addUser(User user) throws ExistentUserException {
        if(!network.containsKey(user)) {
            network.put(user, new ArrayList<>());
            return;
        }
        throw new ExistentUserException(user.getUsername() + " already exists!");
    }

    /**
     * Method that removes a user from the network
     * @param user User
     * @throws InexistentUserException if the user does not exist in the network
     */
    public void removeUser(User user) throws InexistentUserException {
        if(!network.containsKey(user)) {
            throw new InexistentUserException(user.getUsername() + " does not exist!");
        }
        network.remove(user);
        for(Map.Entry<User, List<User>> entries : network.entrySet()) {
            entries.getValue().remove(user);
        }
    }

    /**
     * Method that adds a friendship in the network
     * @param user1 User
     * @param user2 User
     * @throws InexistentUserException if at least one of the user does not exist in the network
     * @throws ExistentFriendshipException if there is already a friendship between the users
     */
    public void addFriendship(User user1, User user2) throws InexistentUserException, ExistentFriendshipException {
        String errorMessage = "";
        if(!network.containsKey(user1)) {
            errorMessage += user1.getUsername() + " does not exist!";
        }
        if(!network.containsKey(user2)) {
            errorMessage += (errorMessage.length() > 0 ? "\n" : "") + user2.getUsername() + " does not exist!";
        }
        if(errorMessage.length() > 0) {
            throw new InexistentUserException(errorMessage);
        }
        if(network.get(user1).contains(user2)) {
            throw new ExistentFriendshipException(user1.getUsername() +
                    " and " + user2.getUsername() + " are already friends!");
        }

        network.get(user1).add(user2);
        network.get(user2).add(user1);
    }

    /**
     * Method that removes a friendship in the network
     * @param user1 User
     * @param user2 User
     * @throws InexistentUserException if at least one of the user does not exist in the network
     * @throws InexistentFriendshipException if there is not friendship between the users with the given usernames
     */
    public void removeFriendsShip(User user1, User user2) throws InexistentUserException, InexistentFriendshipException {
        String errorMessage = "";
        if(!network.containsKey(user1)) {
            errorMessage += user1.getUsername() + " does not exist!";
        }
        if(!network.containsKey(user2)) {
            errorMessage += (errorMessage.length() > 0 ? "\n" : "") + user2.getUsername() + " does not exist!";
        }
        if(errorMessage.length() > 0) {
            throw new InexistentUserException(errorMessage);
        }
        if(!network.get(user1).contains(user2)) {
            throw new InexistentFriendshipException(user1.getUsername() +
                    " and " + user2.getUsername() + " are not friends!");
        }

        network.get(user1).remove(user2);
        network.get(user2).remove(user1);
    }

    public boolean areFriends(User user1, User user2) throws InexistentUserException {
        String errorMessage = "";
        if(!network.containsKey(user1)) {
            errorMessage += user1.getUsername() + " does not exist!";
        }
        if(!network.containsKey(user2)) {
            errorMessage += (errorMessage.length() > 0 ? "\n" : "") + user2.getUsername() + " does not exist!";
        }
        if(errorMessage.length() > 0) {
            throw new InexistentUserException(errorMessage);
        }
        return network.get(user1).contains(user2);
    }

    public void clear() {
        network.clear();
    }
}
