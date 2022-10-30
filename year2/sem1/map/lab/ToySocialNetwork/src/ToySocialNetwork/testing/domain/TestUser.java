package ToySocialNetwork.testing.domain;

import ToySocialNetwork.domain.User;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestUser {

    @Test
    @DisplayName("Testing user's getters")
    public void testGetters() {
        User user = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        assertEquals(user.getUsername(), "victor.zarzu");
        assertEquals(user.getPassword(), "ceva");
        assertEquals(user.getEmail(), "victorzarzu@gmail.com");
        assertEquals(user.getFirstName(), "Victor");
        assertEquals(user.getLastName(), "Zarzu");
        assertEquals(user.getGender(), "Man");
    }

    @Test
    @DisplayName("Testing user's equality")
    public void testEquality() {
        User user1 = new User("victor.zarzu", "eusunt", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("victor.zarzu", "eusunt1", "victorzarzu@yahoo.com", "Eugen", "Zarzu", "Man");
        assertEquals(user1, user2);
    }

    @Test
    @DisplayName("Testing user's setters")
    public void testSetters() {
        User user = new User("user_254", "eusunt", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        user.setPassword("eusunt1");
        user.setEmail("andreeilinca@yahoo.com");
        user.setFirstName("Andreea");
        user.setLastName("Ilinca");
        user.setGender("Woman");

        assertEquals(user.getUsername(), "user_254");
        assertEquals(user.getPassword(), "eusunt1");
        assertEquals(user.getEmail(), "andreeilinca@yahoo.com");
        assertEquals(user.getFirstName(), "Andreea");
        assertEquals(user.getLastName(), "Ilinca");
        assertEquals(user.getGender(), "Woman");
    }

    @Test
    @DisplayName("Testing user's string format")
    public void testToString() {
        User user = new User("victor.zarzu", "eusunt", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        assertEquals(user.toString(), "Username: victor.zarzu | Email : victorzarzu@gmail.com | First name: Victor | " +
                "Last name: Zarzu | Gender: Man\n");
    }
}
