package testing.service;

import domain.Network;
import domain.User;
import domain.validators.UserValidator;
import domain.validators.ValidationException;
import domain.validators.Validator;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import repository.Repository;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;
import repository.memory.InMemoryAllNetwork;
import repository.memory.InMemoryRepository;
import service.UserService;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;

public class TestUserService {
    private static final Repository<String, User> userRepository = new InMemoryRepository<>();
    private static final Validator<User> userValidator = new UserValidator();
    private static final InMemoryAllNetwork allNetwork = new InMemoryAllNetwork();
    private static UserService service = new UserService(userRepository, userValidator, allNetwork);


    @BeforeEach
    public void initData() {
        service.clear();
    }

    @Test
    @DisplayName("Test user adding service")
    public void testAdd() throws Exception {
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
    public void testRemove() throws Exception {
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
    @DisplayName("Test friendship adding service")
    public void testAddFriendship() throws Exception {
        service.addUser("victor.zarzu", "dada", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        service.addUser("andrei.ol", "ceva", "andrei.ol@gmail.com", "Andrei", "Ol", "Man");

        service.addFriendship("victor.zarzu", "andrei.ol");

        try {
            service.addFriendship("victor.zarzu", "andrei.ol");
            fail();
        } catch (ExistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu and andrei.ol are already friends!");
        }

        try {
            service.addFriendship("victor.zarzu", "andre.ol");
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "andre.ol does not exist!");
        }
    }

    @Test
    @DisplayName("Test removing friendship adding service")
    public void testRemoveFriendship() throws Exception {
        service.addUser("victor.zarzu", "dada", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        service.addUser("andrei.ol", "ceva", "andrei.ol@gmail.com", "Andrei", "Ol", "Man");

        service.addFriendship("victor.zarzu", "andrei.ol");
        service.removeFriendShip("victor.zarzu", "andrei.ol");

        try {
            service.removeFriendShip("victor.zarzu", "andrei.ol");
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu and andrei.ol are not friends!");
        }

        try {
            service.removeFriendShip("victor.zarzu", "andre.ol");
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "andre.ol does not exist!");
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
        User user4 = new User("patru", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        User user5 = new User("cinci", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        User user6 = new User("sase", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        resultNetwork.addUser(user1);
        resultNetwork.addUser(user2);
        resultNetwork.addUser(user3);
        resultNetwork.addFriendship(user1, user2);
        resultNetwork.addFriendship(user2, user3);
        resultNetwork.addFriendship(user1, user3);

        assertEquals(resultNetwork, service.mostSocialCommunity());
    }
}
