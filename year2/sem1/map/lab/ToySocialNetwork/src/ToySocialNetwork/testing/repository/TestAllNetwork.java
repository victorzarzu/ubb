package ToySocialNetwork.testing.repository;

import ToySocialNetwork.domain.Network;
import ToySocialNetwork.domain.User;
import ToySocialNetwork.exceptions.repository.ExistentFriendshipException;
import ToySocialNetwork.exceptions.repository.ExistentUserException;
import ToySocialNetwork.exceptions.repository.InexistentFriendshipException;
import ToySocialNetwork.exceptions.repository.InexistentUserException;
import ToySocialNetwork.repository.AllNetwork;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestAllNetwork {

    @Test
    @DisplayName("Test add allNetwork user")
    public void testAddUser() throws ExistentUserException {
        AllNetwork network = new AllNetwork();
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
    @DisplayName("Test remove allNetwork user")
    public void testRemoveUser() throws ExistentUserException, InexistentUserException {
        AllNetwork network = new AllNetwork();
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
    @DisplayName("Test add allNetwork friendship")
    public void testAddFriendship() throws ExistentUserException, InexistentUserException, ExistentFriendshipException {
        AllNetwork network = new AllNetwork();
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
    @DisplayName("Test remove allNetwork friendship")
    public void testRemoveFriendship() throws Exception {
        AllNetwork network = new AllNetwork();
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
    @DisplayName("Test are friends allNetwork")
    public void testAreFriends() throws ExistentUserException, InexistentUserException, ExistentFriendshipException {
        AllNetwork network = new AllNetwork();
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
    @DisplayName("Test clear allNetwork")
    public void testClear() throws ExistentUserException, InexistentUserException, ExistentFriendshipException {
        AllNetwork network = new AllNetwork();
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

    @Test
    @DisplayName("Test number of communities allNetwork")
    public void testNumberOfCommunities() throws ExistentUserException, InexistentUserException, ExistentFriendshipException {
        AllNetwork network = new AllNetwork();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        User user3 = new User("andreea.ol", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        network.addUser(user1);
        network.addUser(user2);
        network.addUser(user3);
        network.addFriendship(user2, user3);

        assertEquals(2, network.numberOfCommunities());
    }

    @Test
    @DisplayName("Test most social community allNetwork")
    public void testMostSocialCommunity() throws ExistentUserException, InexistentUserException, ExistentFriendshipException {
        AllNetwork network = new AllNetwork();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        User user3 = new User("andreea.ol", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        User user4 = new User("patru", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        User user5 = new User("cinci", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        User user6 = new User("sase", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        network.addUser(user1);
        network.addUser(user2);
        network.addUser(user3);
        network.addUser(user4);
        network.addUser(user5);
        network.addUser(user6);
        network.addFriendship(user1, user2);
        network.addFriendship(user2, user3);
        network.addFriendship(user1, user3);
        network.addFriendship(user4, user5);
        network.addFriendship(user5, user6);

        Network resultNetwork = new Network();
        resultNetwork.addUser(user1);
        resultNetwork.addUser(user2);
        resultNetwork.addUser(user3);
        resultNetwork.addFriendship(user1, user2);
        resultNetwork.addFriendship(user2, user3);
        resultNetwork.addFriendship(user1, user3);

        assertEquals(resultNetwork, network.mostSocialCommunity());
    }
}
