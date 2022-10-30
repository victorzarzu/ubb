package ToySocialNetwork.repository;

import ToySocialNetwork.domain.Network;
import ToySocialNetwork.domain.User;
import ToySocialNetwork.exceptions.repository.ExistentFriendshipException;
import ToySocialNetwork.exceptions.repository.ExistentUserException;
import ToySocialNetwork.exceptions.repository.InexistentFriendshipException;
import ToySocialNetwork.exceptions.repository.InexistentUserException;

import java.util.*;

/**
 * Class for modelling the whole network
 */
public class AllNetwork {
    private Network network;

    /**
     * Constructor for the AllNetwork class
     */
    public AllNetwork() {
        network = new Network();
    }

    /**
     * Method that adds a user to the network
     * @param user User
     * @throws ExistentUserException if the user is already in the network
     */
    public void addUser(User user) throws ExistentUserException {
        this.network.addUser(user);
    }

    /**
     * Method that removes a user from the network
     * @param user User
     * @throws InexistentUserException if the user does not exist in the network
     */
    public void removeUser(User user) throws InexistentUserException {
        this.network.removeUser(user);
    }

    /**
     * Method that adds a friendship in the network
     * @param user1 User
     * @param user2 User
     * @throws InexistentUserException if at least one of the user does not exist in the network
     * @throws ExistentFriendshipException if there is already a friendship between the users
     */
    public void addFriendship(User user1, User user2) throws InexistentUserException, ExistentFriendshipException {
        this.network.addFriendship(user1, user2);
    }

    /**
     * Method that removes a friendship in the network
     * @param user1 User
     * @param user2 User
     * @throws InexistentUserException if at least one of the user does not exist in the network
     * @throws InexistentFriendshipException if there is not friendship between the users with the given usernames
     */
    public void removeFriendsShip(User user1, User user2) throws InexistentUserException, InexistentFriendshipException {
        network.removeFriendsShip(user1, user2);
    }

    /**
     * Method that tests if 2 users are friends
     * @param user1 User
     * @param user2 User
     * @return true if they are friends and false otherwise
     * @throws InexistentUserException if at least one of the users does not exist
     */
    public boolean areFriends(User user1, User user2) throws InexistentUserException {
        return network.areFriends(user1, user2);
    }

    /**
     * Method that returns the number of communities inside the network
     * @return Integer
     */
    public Integer numberOfCommunities() {
        return network.numberOfCommunities();
    }

    /**
     * Method that returns the most social community
     * @return Network
     */
    public Network mostSocialCommunity() {
        return network.mostSocialCommunity();
    }

    /**
     * Method that clears the network
     */
    public void clear() {
        network.clear();
    }
}
