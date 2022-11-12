package service;

import domain.Friendship;
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

import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

/**
 * Class that models a service for users
 */
public class UserService implements Service {
    private Repository<String, User> userRepository;
    private Repository<Set<String>, Friendship> friendshipRepository;
    private Validator userValidator;
    private Validator friendshipValidator;

    /**
     * Constructor for creating a service for users
     * @param userRepository - a repository of users
     * @param userValidator - a validator for users
     * @param  friendshipRepository - a repository of friendships
     * @param friendshipValidator - a validator for users
     */
    public UserService(Repository userRepository, Validator userValidator,
                       Repository friendshipRepository, Validator friendshipValidator) {
        this.userRepository = userRepository;
        this.userValidator = userValidator;
        this.friendshipRepository = friendshipRepository;
        this.friendshipValidator = friendshipValidator;
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
    }

    /**
     * Method that modifies a user
     * @param username String
     * @param password String
     * @param email String
     * @param firstName String
     * @param lastName String
     * @param gender String
     * @throws InexistentEntityException if the user does not exist
     * @throws ValidationException if the given data is not valid for a user to be created
     */
    public void modifyUser(String username, String password, String email,
                        String firstName, String lastName, String gender) {
        User user = new User(username, password, email, firstName, lastName, gender);
        userValidator.validate(user);
        userRepository.modify(user);
    }


    /**
     * Method that removes a user based on its username
     * @param username String
     * @throws InexistentEntityException if the user does not exist
     */
    public void removeUser(String username) {
        User user = userRepository.find(username);
        userRepository.remove(user.getId());
    }

    /**
     * Method that creates the friendship between 2 users based on their usernames
     * @param username1 String
     * @param username2 String
     * @throws ExistentEntityException if the 2 users are already friends
     * @throws ValidationException if the both usernames are the same
     * @throws InexistentEntityException if at least one of the usernames does not correspond to a user
     */
    public void addFriendship(String username1, String username2) {
        userRepository.find(username1);
        userRepository.find(username2);
        Friendship friendship = new Friendship(username1, username2);
        friendshipValidator.validate(friendship);
        friendshipRepository.add(friendship);
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
        friendshipRepository.remove(new HashSet<>(Arrays.asList(username1, username2)));
    }

    /**
     * Method that modifies the friendship date of a friendship
     * @param username1 username of the first user
     * @param username2 username of the second user
     * @param friendshipDate the new date of the friendship
     * @throws ValidationException if the given date is in the future
     * @throws InexistentEntityException if at least one of the usernames does not correspond to a user
     */
    public void modifyFriendshipDate(String username1, String username2, LocalDateTime friendshipDate) {
        User user1 = userRepository.find(username1);
        User user2 = userRepository.find(username2);

        Friendship friendship = new Friendship(username1, username2, friendshipDate);
        friendshipValidator.validate(friendship);
        friendshipRepository.modify(friendship);
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
     * Method that returns the friendship between the given usernames
     * @param username1 username of the first user
     * @param username2 username of the first user
     * @return Friendship
     * @throws InexistentEntityException if there is no friendship between the given users
     */
    public Friendship findFriendship(String username1, String username2) {
        return this.friendshipRepository.find(new HashSet<>(Arrays.asList(username1, username2)));
    }

    /**
     * Method that returns the number of communities inside the network
     * @return Integer
     */
    public Integer numberOfCommunities() {
        Network network = new Network(this.userRepository.getMap(), this.friendshipRepository.getAll());
        return network.numberOfCommunities();
    }

    /**
     * Method that returns the most social community
     * @return Network
     */
    public Network mostSocialCommunity() {
        Network network = new Network(this.userRepository.getMap(), this.friendshipRepository.getAll());
        return network.mostSocialCommunity();
    }

    public Iterable<User> getAllUsers() {
        return userRepository.getAll();
    }

    public Iterable<Friendship> getAllFriendships() {
        return friendshipRepository.getAll();
    }

    /**
     * Method that clears the data
     */
    public void clear() {
        userRepository.clear();
        friendshipRepository.clear();
    }
}
