package ToySocialNetwork.domain;

import ToySocialNetwork.exceptions.repository.ExistentUserException;
import ToySocialNetwork.exceptions.repository.ExistentFriendshipException;
import ToySocialNetwork.exceptions.repository.InexistentFriendshipException;
import ToySocialNetwork.exceptions.repository.InexistentUserException;

import java.util.*;

/**
 * Class that models a network
 */
public class Network {
    private Map<User, Set<User>> network;

    /**
     * Constructor for the network class
     */
    public Network() {
        network = new HashMap<>();
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == this) {
            return true;
        }
        if(!(obj instanceof Network)) {
            return false;
        }

        return Objects.equals(this.network, ((Network) obj).network);
    }

    @Override
    public String toString() {
        if(network.size() == 0) {
            return "Empty network!";
        }

        String result = "";
        for(Map.Entry<User, Set<User>> entry : network.entrySet()) {
            result += entry.getKey().getUsername() + " ";
            if(entry.getValue().size() > 0) {
                result += "is friend with ";
                for (User friend : entry.getValue()) {
                    result += friend.getUsername() + " ";
                }
            }
            else {
                result += "does not have friends ";
            }
            result += "\n";
        }

        return result;
    }

    /**
     * Method that adds a user to the network
     * @param user User
     * @throws ExistentUserException if the user is already in the network
     */
    public void addUser(User user) throws ExistentUserException {
        if(!network.containsKey(user)) {
            network.put(user, new HashSet<>());
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
        for(Map.Entry<User, Set<User>> entries : network.entrySet()) {
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

    /**
     * Method used for traversing the network using dfs
     * @param user User
     * @param componentUsers Set<User>
     */
    private void dfsNumberOfCommunities(User user, Set<User> componentUsers) {
        for(User friend : network.get(user)) {
            if(!componentUsers.contains(friend)) {
                componentUsers.add(friend);
                dfsNumberOfCommunities(friend, componentUsers);
            }
        }
    }

    /**
     * Method that returns the number of communities inside the network
     * @return Integer
     */
    public Integer numberOfCommunities() {
        Integer result = 0;

        HashSet<User> visitedUsers = new HashSet<>();
        for(User user : network.keySet()) {
            if(!visitedUsers.contains(user)) {
                HashSet<User> componentUsers = new HashSet<>();
                result++;
                dfsNumberOfCommunities(user, componentUsers);
                visitedUsers.addAll(componentUsers);
            }
        }

        return result;
    }

    /**
     * Method that generated the subwork consisting of the users that are in the users Set
     * @param users Set<User>
     * @return Network
     */
    private Network generateSubNetwork(Set<User> users) {
        Network generatedNetwork = new Network();
        for(User user : users) {
            try{
                generatedNetwork.addUser(user);
                for(User friend : network.get(user)) {
                    if(!generatedNetwork.areFriends(user, friend)) {
                        generatedNetwork.addFriendship(user, friend);
                    }
                }
            }catch (Exception exception){};
        }

        return generatedNetwork;
    }

    /**
     * Method that returns the number of friendships in a given network
     * @param network Network
     * @return Integer
     */
    private static Integer numberOfFriendships(Network network) {
        Integer friendships = 0;
        for(User user : network.network.keySet()) {
            friendships += network.network.get(user).size();
        }
        return friendships / 2;
    }

    /**
     * Method that returns the most social community
     * @return Network
     */
    public Network mostSocialCommunity() {
        Set<User> visitedUsers = new HashSet<>();
        Network mostSocialCommunity = new Network();
        for(User user : network.keySet()) {
            if(!visitedUsers.contains(user)) {
                Set<User> componentUsers = new HashSet<>();
                dfsNumberOfCommunities(user, componentUsers);
                visitedUsers.addAll(componentUsers);

                Network componentNetwork = generateSubNetwork(componentUsers);
                if(numberOfFriendships(componentNetwork) > numberOfFriendships(mostSocialCommunity)) {
                    mostSocialCommunity = componentNetwork;
                }
            }
        }

        return mostSocialCommunity;
    }

    /**
     * Method that clears the network
     */
    public void clear() {
        network.clear();
    }
}
