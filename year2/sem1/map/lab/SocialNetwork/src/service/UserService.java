package service;

import domain.Network;
import domain.User;
import domain.exceptions.ExistentFriendshipException;
import domain.exceptions.ExistentUserException;
import domain.exceptions.InexistentFriendshipException;
import domain.exceptions.InexistentUserException;
import domain.validators.ValidationException;
import domain.validators.Validator;
import repository.Repository;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;
import repository.file.UserFileRepository;
import repository.memory.InMemoryAllNetwork;

/**
 * Class that models a service for users
 */
public class UserService implements Service {
    private InMemoryAllNetwork allNetwork;
    private Repository<String, User> userRepository;
    private Validator userValidator;

    /**
     * Constructor for creating a service for users
     * @param userRepository - a repository of users
     * @param userValidator - a validator for users
     * @param network - a network for the users
     */
    public UserService(Repository userRepository, Validator userValidator, InMemoryAllNetwork network) {
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
     * @throws ExistentEntityException if the user already exists
     * @throws ValidationException if the given data is not valid for a user to be created
     */
    public void addUser(String username, String password, String email,
                        String firstName, String lastName, String gender)
            throws ValidationException {
        User user = new User(username, password, email, firstName, lastName, gender);
        userValidator.validate(user);
        userRepository.add(user);
        allNetwork.addUser(user);
    }


    /**
     * Method that removes a user based on its username
     * @param username String
     * @throws InexistentEntityException if the user does not exist
     */
    public void removeUser(String username) {
        User user = userRepository.find(username);
        userRepository.remove(user.getId());
        allNetwork.removeUser(user);
    }

    /**
     * Method that creates the friendship between 2 users based on their usernames
     * @param username1 String
     * @param username2 String
     * @throws ExistentEntityException if the 2 users are already friends
     * @throws InexistentEntityException if at least one of the usernames does not correspond to a user
     */
    public void addFriendship(String username1, String username2) {
        User user1 = userRepository.find(username1);
        User user2 = userRepository.find(username2);
        allNetwork.addFriendship(user1, user2);
    }

    /**
     * Method that removes the friendship between 2 users based on their usernames
     * @param username1 String
     * @param username2 String
     * @throws InexistentEntityException if the 2 users are not friends
     * @throws InexistentEntityException if at least one of the usernames does not correspond to a user
     */
    public void removeFriendShip(String username1, String username2) {
        User user1 = userRepository.find(username1);
        User user2 = userRepository.find(username2);
        allNetwork.removeFriendsShip(user1, user2);
    }

    /**
     * Method that returns the user with the given username
     * @param username String
     * @return User
     * @throws InexistentEntityException if there is not user with the given username
     */
    public User findUser(String username) {
        return this.userRepository.find(username);
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
