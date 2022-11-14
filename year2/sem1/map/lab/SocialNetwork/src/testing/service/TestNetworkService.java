package testing.service;

import config.Config;
import domain.Friendship;
import domain.Network;
import domain.User;
import domain.exceptions.InexistentFriendshipException;
import domain.validators.FriendshipValidator;
import domain.validators.UserValidator;
import domain.validators.ValidationException;
import domain.validators.Validator;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import repository.Repository;
import repository.database.FriendshipDbRepository;
import repository.database.UserDbRepository;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;
import service.NetworkService;

import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;

public class TestNetworkService {
    private static FriendshipDbRepository friendshipRepository = new FriendshipDbRepository(Config.getProperties().getProperty("databaseTestUrl"),
            Config.getProperties().getProperty("username"), Config.getProperties().getProperty("password"));
    private static Repository<String, User> userRepository = new UserDbRepository(Config.getProperties().getProperty("databaseTestUrl"),
            Config.getProperties().getProperty("username"), Config.getProperties().getProperty("password"));
    private static final Validator<User> userValidator = new UserValidator();
    private static final Validator<Friendship> friendshipValidator = new FriendshipValidator();
    private static NetworkService service = new NetworkService(userRepository, userValidator, friendshipRepository, friendshipValidator);


    @BeforeEach
    public void initData() {
        service.clear();
    }

    @Test
    @DisplayName("Test user adding service")
    public void testAddUser() throws Exception {
        try {
            service.addUser("victor.zarzu", "dada", "dafafdasf.com", "Victor", "Zarzu", "Man");
            fail();
        } catch (ValidationException exception) {
            assertEquals(exception.getMessage(), "Invalid email!\n");
        }

        service.addUser("victor.zarzu", "dada", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        try {
            service.addUser("victor.zarzu", "dada", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
            fail();
        } catch (ExistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu already exists!");
        }
    }

    @Test
    @DisplayName("Test user removing service")
    public void testRemoveUser() throws Exception {
        service.addUser("victor.zarzu", "dada", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        service.removeUser("victor.zarzu");

        try {
            service.removeUser("victor.zarzu");
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu does not exist!");
        }
    }

    @Test
    @DisplayName("Test user modifying service")
    public void testModifyUser() throws Exception {
        service.addUser("victor.zarzu", "dada", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        service.modifyUser("victor.zarzu", "nunu", "victorzarzu@gmail.com", "Eugen", "Zarzu", "Man");

        User userFound = service.findUser("victor.zarzu");
        assertEquals(userFound.getPassword(), "nunu");
        assertEquals(userFound.getFirstName(), "Eugen");

        try {
            service.modifyUser("victor", "nunu", "victorzarzu@gmail.com", "Eugen", "Zarzu", "Man");

            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor does not exist!");
        }

        try {
            service.modifyUser("victor.zarzu", "dada", "dafafdasf.com", "Victor", "Zarzu", "Man");
            fail();
        } catch (ValidationException exception) {
            assertEquals(exception.getMessage(), "Invalid email!\n");
        }
    }

    @Test
    @DisplayName("Test friendship adding service")
    public void testAddFriendship() throws Exception {
        service.addUser("victor.zarzu", "dada", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        service.addUser("andrei.ol", "ceva", "andrei.ol@gmail.com", "Andrei", "Ol", "Man");

        service.addFriendship("victor.zarzu", "andrei.ol");

        try {
            service.addFriendship("victor.zarzu", "andrei.ol");
            fail();
        } catch (ExistentEntityException exception) {
            assertEquals(exception.getMessage(), "Friendship between andrei.ol and victor.zarzu already exists!");
        }

        try {
            service.addFriendship("victor.zarzu", "andre.ol");
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "andre.ol does not exist!");
        }

        try {
            service.addFriendship("victor.zarzu", "victor.zarzu");
            fail();
        } catch (ValidationException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu cannot be friend to itself!");
        }
    }

    @Test
    @DisplayName("Test removing friendship service")
    public void testRemoveFriendship() throws Exception {
        service.addUser("victor.zarzu", "dada", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        service.addUser("andrei.ol", "ceva", "andrei.ol@gmail.com", "Andrei", "Ol", "Man");

        service.addFriendship("victor.zarzu", "andrei.ol");
        service.removeFriendship("victor.zarzu", "andrei.ol");

        try {
            service.removeFriendship("victor.zarzu", "andrei.ol");
            fail();
        } catch (InexistentFriendshipException exception) {
            assertEquals(exception.getMessage(), "Friendship between andrei.ol and victor.zarzu does not exist!");
        }

        try {
            service.removeFriendship("victor.zarzu", "andre.ol");
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "andre.ol does not exist!");
        }
    }

    @Test
    @DisplayName("Test finding friendship service")
    public void testFindFriendship() throws Exception {
        service.addUser("victor.zarzu", "dada", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        service.addUser("andrei.ol", "ceva", "andrei.ol@gmail.com", "Andrei", "Ol", "Man");

        service.addFriendship("victor.zarzu", "andrei.ol");
        Friendship friendshipFound = service.findFriendship("victor.zarzu", "andrei.ol");
        assertEquals(friendshipFound.getFirstUsername(), "andrei.ol");
        assertEquals(friendshipFound.getSecondUsername(), "victor.zarzu");

        try {
            service.removeFriendship("victor", "andrei.ol");
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor does not exist!");
        }
    }

    @Test
    @DisplayName("Test modifying friendship service")
    public void testModifyFriendship() throws Exception {
        service.addUser("victor.zarzu", "dada", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        service.addUser("andrei.ol", "ceva", "andrei.ol@gmail.com", "Andrei", "Ol", "Man");

        service.addFriendship("victor.zarzu", "andrei.ol");
        service.modifyFriendshipDate("victor.zarzu", "andrei.ol", LocalDateTime.now().minusYears(10));

        Friendship friendshipFound = service.findFriendship("victor.zarzu", "andrei.ol");
        assertEquals(friendshipFound.getFriendshipDate().getYear(), LocalDateTime.now().minusYears(10).getYear());

        try {
            service.modifyFriendshipDate("victor", "andrei.ol", LocalDateTime.now().minusYears(10));
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor does not exist!");
        }

        try {
            service.modifyFriendshipDate("victor.zarzu", "andrei.ol", LocalDateTime.now().plusYears(10));
            fail();
        } catch (ValidationException exception) {
            assertEquals(exception.getMessage(), "Friendship date cannot be in the future!");
        }
    }

    @Test
    @DisplayName("Test find user by username service")
    public void testFindUser() throws Exception {
        service.addUser("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");

        User foundUser = service.findUser("victor.zarzu");
        assertEquals(foundUser.getId(), "victor.zarzu");
        assertEquals(foundUser.getPassword(), "ceva");
        assertEquals(foundUser.getEmail(), "victorzarzu@gmail.com");
        assertEquals(foundUser.getFirstName(), "Victor");
        assertEquals(foundUser.getLastName(), "Zarzu");
        assertEquals(foundUser.getGender(), "Man");

        try{
            service.findUser("andrei.ol");
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "andrei.ol does not exist!");
        }
    }

    @Test
    @DisplayName("Test number of communities service")
    public void testNumberOfCommunities() throws Exception {
        service.addUser("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        service.addUser("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        service.addUser("andreea.ol", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        service.addFriendship("andreea.ol", "andrei.ol");

        assertEquals(2, service.numberOfCommunities());
    }

    @Test
    @DisplayName("Test most social community service")
    public void testMostSocialCommunity() throws Exception {
        service.addUser("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        service.addUser("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        service.addUser("andreea.ol", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        service.addUser("patru", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        service.addUser("cinci", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        service.addUser("sase", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        service.addFriendship("victor.zarzu", "andrei.ol");
        service.addFriendship("andrei.ol", "andreea.ol");
        service.addFriendship("victor.zarzu", "andreea.ol");
        service.addFriendship("patru", "cinci");
        service.addFriendship("cinci", "sase");

        Network resultNetwork = new Network();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        User user3 = new User("andreea.ol", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");

        resultNetwork.addUser(user1);
        resultNetwork.addUser(user2);
        resultNetwork.addUser(user3);
        resultNetwork.addFriendship(user1, user2);
        resultNetwork.addFriendship(user2, user3);
        resultNetwork.addFriendship(user1, user3);

        assertEquals(resultNetwork, service.mostSocialCommunity());
    }
}
