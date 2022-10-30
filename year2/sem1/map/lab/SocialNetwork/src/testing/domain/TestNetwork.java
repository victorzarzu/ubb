package testing.domain;


import domain.Network;
import domain.User;
import domain.exceptions.ExistentFriendshipException;
import domain.exceptions.ExistentUserException;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;

import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;


public class TestNetwork {

    @Test
    @DisplayName("Test add network user")
    public void testAddUser() {
        Network network = new Network();
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
    @DisplayName("Test remove network user")
    public void testRemoveUser()  {
        Network network = new Network();
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
    @DisplayName("Test add network friendship")
    public void testAddFriendship() {
        Network network = new Network();
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
    @DisplayName("Test remove network friendship")
    public void testRemoveFriendship() {
        Network network = new Network();
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
    @DisplayName("Test are friends network")
    public void testAreFriends() {
        Network network = new Network();
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
    @DisplayName("Test equals network")
    public void testEquals() {
        Network network1 = new Network();
        Network network2 = new Network();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        network1.addUser(user1);
        network1.addUser(user2);
        network1.addFriendship(user1, user2);
        network2.addUser(user1);
        network2.addUser(user2);
        network2.addFriendship(user1, user2);

        assertEquals(network1, network2);

        network2.removeFriendsShip(user1, user2);
        assertNotEquals(network1, network2);
    }

    @Test
    @DisplayName("Test toString network")
    public void testToString() {
        Network network = new Network();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andrei.ol@gmail.com", "Andre", "Ol", "Man");
        User user3 = new User("andreea.on", "ceva", "andreea.on@gmail.com", "Andreea", "On", "Woman");
        network.addUser(user1);
        network.addUser(user2);
        network.addUser(user3);
        network.addFriendship(user1, user2);

        assertEquals(3, network.toString().split("\n").length);
    }

    @Test
    @DisplayName("Test clear network")
    public void testClear() {
        Network network = new Network();
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
    @DisplayName("Test number of communities network")
    public void testNumberOfCommunities() {
        Network network = new Network();
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andreiol@gmail.com", "Andrei", "Ol", "Man");
        User user3 = new User("andreea.ol", "ceva", "andreeaol@gmail.com", "Andreea", "Ol", "Woman");
        network.addUser(user1);
        network.addUser(user2);
        network.addUser(user3);
        network.addFriendship(user2, user3);

        assertEquals(Optional.of(2), Optional.of(network.numberOfCommunities()));
    }

    @Test
    @DisplayName("Test most social community network")
    public void testMostSocialCommunity() {
        Network network = new Network();
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
