package testing.repository;

import domain.Network;
import domain.User;
import domain.exceptions.ExistentFriendshipException;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;
import repository.memory.InMemoryAllNetwork;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestInMemoryAllNetwork {

    @Test
    @DisplayName("Test add InMemoryAllNetwork user")
    public void testAddUser() throws ExistentEntityException {
        InMemoryAllNetwork network = new InMemoryAllNetwork();
        User user = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        network.addUser(user);

        try {
            network.addUser(user);
            fail();
        } catch (ExistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu already exists!");
        }
    }

    @Test
    @DisplayName("Test remove InMemoryAllNetwork user")
    public void testRemoveUser() {
        InMemoryAllNetwork network = new InMemoryAllNetwork();
        User user = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        network.addUser(user);
        network.removeUser(user);

        try {
            network.removeUser(user);
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu does not exist!");
        }
    }


    @Test
    @DisplayName("Test add InMemoryAllNetwork friendship")
    public void testAddFriendship() {
        InMemoryAllNetwork network = new InMemoryAllNetwork();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        network.addUser(user1);

        try {
            network.addFriendship(user1, user2);
            fail();
        } catch (InexistentEntityException exception) {
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
    @DisplayName("Test remove InMemoryAllNetwork friendship")
    public void testRemoveFriendship() {
        InMemoryAllNetwork network = new InMemoryAllNetwork();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        network.addUser(user1);

        try {
            network.removeFriendsShip(user1, user2);
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "andrei.ol does not exist!");
        }

        network.addUser(user2);
        network.addFriendship(user1, user2);
        network.removeFriendsShip(user1, user2);

        try {
            network.removeFriendsShip(user1, user2);
            fail();
        } catch(InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu and andrei.ol are not friends!");
        }
    }

    @Test
    @DisplayName("Test are friends InMemoryAllNetwork")
    public void testAreFriends() {
        InMemoryAllNetwork network = new InMemoryAllNetwork();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        User user3 = new User("andreea.ol", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        network.addUser(user1);

        try {
            network.areFriends(user1, user2);
            fail();
        } catch (InexistentEntityException exception) {
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
    @DisplayName("Test clear InMemoryAllNetwork")
    public void testClear() {
        InMemoryAllNetwork network = new InMemoryAllNetwork();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        network.addUser(user1);
        network.addUser(user2);

        network.clear();

        try {
            network.removeUser(user1);
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu does not exist!");
        }

        try {
            network.removeUser(user2);
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "andrei.ol does not exist!");
        }
    }

    @Test
    @DisplayName("Test number of communities InMemoryAllNetwork")
    public void testNumberOfCommunities() {
        InMemoryAllNetwork network = new InMemoryAllNetwork();
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
    @DisplayName("Test most social community InMemoryAllNetwork")
    public void testMostSocialCommunity() {
        InMemoryAllNetwork network = new InMemoryAllNetwork();
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
