package ToySocialNetwork.service;

import ToySocialNetwork.domain.Network;
import ToySocialNetwork.domain.User;
import ToySocialNetwork.exceptions.domain.UserValidationException;
import ToySocialNetwork.exceptions.repository.*;
import ToySocialNetwork.exceptions.validation.ValidationException;
import ToySocialNetwork.repository.AllNetwork;
import ToySocialNetwork.repository.UserRepository;
import ToySocialNetwork.validation.Validator;
import ToySocialNetwork.validation.domain.UserValidator;

/**
 * Class that models a service for users
 */
public class UserService implements Service {
    private AllNetwork allNetwork;
    private UserRepository userRepository;
    private Validator userValidator;

    public UserService(UserRepository userRepository, Validator userValidator, AllNetwork network) {
        this.userRepository = userRepository;
        this.allNetwork = network;
        this.userValidator = userValidator;
    }

    /**
     * Method that adds a user
     * @param username String
     * @param password String
     * @param email String
     * @param firstName String
     * @param lastName String
     * @param gender String
     * @throws ExistentUserException if the user already exists
     * @throws UserValidationException if the given data is not valid for a user to be created
     */
    public void addUser(String username, String password, String email,
                        String firstName, String lastName, String gender)
            throws ExistentUserException, ValidationException {
        User user = new User(username, password, email, firstName, lastName, gender);
        userValidator.validate(user);
        userRepository.add(user);
        allNetwork.addUser(user);
    }


    /**
     * Method that removes a user based on its username
     * @param username String
     * @throws InexistentUserException if the user does not exist
     */
    public void removeUser(String username) throws InexistentUserException {
        User user = userRepository.findUser(username);
        userRepository.remove(user);
        allNetwork.removeUser(user);
    }

    /**
     * Method that creates the friendship between 2 users based on their usernames
     * @param username1 String
     * @param username2 String
     * @throws ExistentFriendshipException if the 2 users are already friends
     * @throws InexistentUserException if at least one of the usernames does not correspond to a user
     */
    public void addFriendship(String username1, String username2) throws ExistentFriendshipException, InexistentUserException {
        User user1 = userRepository.findUser(username1);
        User user2 = userRepository.findUser(username2);
        allNetwork.addFriendship(user1, user2);
    }

    /**
     * Method that removes the friendship between 2 users based on their usernames
      * @param username1 String
     * @param username2 String
     * @throws InexistentFriendshipException if the 2 users are not friends
     * @throws InexistentUserException if at least one of the usernames does not correspond to a user
     */
    public void removeFriendShip(String username1, String username2)throws InexistentFriendshipException, InexistentUserException {
        User user1 = userRepository.findUser(username1);
        User user2 = userRepository.findUser(username2);
        allNetwork.removeFriendsShip(user1, user2);
    }

    /**
     * Method that returns the user with the given username
     * @param username String
     * @return User
     * @throws InexistentUserException if there is not user with the given username
     */
    public User findUser(String username) throws InexistentUserException {
        return this.userRepository.findUser(username);
    }

    /**
     * Method that returns the number of communities inside the network
     * @return Integer
     */
    public Integer numberOfCommunities() {
        return allNetwork.numberOfCommunities();
    }

    /**
     * Method that returns the most social community
     * @return Network
     */
    public Network mostSocialCommunity() {
        return allNetwork.mostSocialCommunity();
    }

    /**
     * Method that clears the data
     */
    public void clear() {
        userRepository.clear();
        allNetwork.clear();
    }
}
