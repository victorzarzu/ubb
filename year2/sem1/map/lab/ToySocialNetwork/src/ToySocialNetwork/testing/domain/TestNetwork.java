package ToySocialNetwork.testing.repository;

import ToySocialNetwork.domain.User;
import ToySocialNetwork.exceptions.repository.ExistentUserException;
import ToySocialNetwork.exceptions.repository.ExistentFriendshipException;
import ToySocialNetwork.exceptions.repository.InexistentFriendshipException;
import ToySocialNetwork.exceptions.repository.InexistentUserException;
import ToySocialNetwork.domain.Network;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class TestNetwork {

    @Test
    @DisplayName("Test add network user")
    public void testAddUser() throws ExistentUserException {
        Network network = new Network();
        User user = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        network.addUser(user);

        try {
            network.addUser(user);
            fail();
        } catch (ExistentUserException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu already exists!");
        }
    }

    @Test
    @DisplayName("Test remove network user")
    public void testRemoveUser() throws ExistentUserException, InexistentUserException {
        Network network = new Network();
        User user = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        network.addUser(user);
        network.removeUser(user);

        try {
            network.removeUser(user);
            fail();
        } catch (InexistentUserException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu does not exist!");
        }
    }


    @Test
    @DisplayName("Test add network friendship")
    public void testAddFriendship() throws ExistentUserException, InexistentUserException, ExistentFriendshipException {
        Network network = new Network();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        network.addUser(user1);

        try {
            network.addFriendship(user1, user2);
            fail();
        } catch (InexistentUserException exception) {
            assertEquals(exception.getMessage(), "andrei.ol does not exist!");
        }

        network.addUser(user2);
        network.addFriendship(user1, user2);

        try {
            network.addFriendship(user1, user2);
            fail();
        } catch(ExistentFriendshipException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu and andrei.ol are already friends!");
        }
    }

    @Test
    @DisplayName("Test remove network friendship")
    public void testRemoveFriendship() throws Exception {
        Network network = new Network();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        network.addUser(user1);

        try {
            network.removeFriendsShip(user1, user2);
            fail();
        } catch (InexistentUserException exception) {
            assertEquals(exception.getMessage(), "andrei.ol does not exist!");
        }

        network.addUser(user2);
        network.addFriendship(user1, user2);
        network.removeFriendsShip(user1, user2);

        try {
            network.removeFriendsShip(user1, user2);
            fail();
        } catch(InexistentFriendshipException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu and andrei.ol are not friends!");
        }
    }

    @Test
    @DisplayName("Test are friends network")
    public void testAreFriends() throws ExistentUserException, InexistentUserException, ExistentFriendshipException {
        Network network = new Network();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        User user3 = new User("andreea.ol", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        network.addUser(user1);

        try {
            network.areFriends(user1, user2);
            fail();
        } catch (InexistentUserException exception) {
            assertEquals(exception.getMessage(), "andrei.ol does not exist!");
        }
        network.addUser(user2);
        network.addUser(user3);
        network.addFriendship(user1, user2);

        assertTrue(network.areFriends(user1, user2));
        assertFalse(network.areFriends(user1, user3));

        try {
            network.addFriendship(user1, user2);
            fail();
        } catch(ExistentFriendshipException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu and andrei.ol are already friends!");
        }
    }

    @Test
    @DisplayName("Test clear network")
    public void testClear() throws ExistentUserException, InexistentUserException, ExistentFriendshipException {
        Network network = new Network();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        network.addUser(user1);
        network.addUser(user2);

        network.clear();

        try {
            network.removeUser(user1);
            fail();
        } catch (InexistentUserException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu does not exist!");
        }

        try {
            network.removeUser(user2);
            fail();
        } catch (InexistentUserException exception) {
            assertEquals(exception.getMessage(), "andrei.ol does not exist!");
        }
    }
}
