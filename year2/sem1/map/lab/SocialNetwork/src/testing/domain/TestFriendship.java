package testing.domain;

import domain.Friendship;
import domain.User;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestFriendship {

    @Test
    @DisplayName("Testing friendship's getters")
    public void testGetters() {
        Friendship friendship = new Friendship("eu", "tu");
        assertEquals(LocalDateTime.now().getMinute(), friendship.getFriendshipDate().getMinute());
        assertEquals(LocalDateTime.now().getHour(), friendship.getFriendshipDate().getHour());
        assertEquals(LocalDateTime.now().getDayOfMonth(), friendship.getFriendshipDate().getDayOfMonth());
        assertEquals(LocalDateTime.now().getMonth(), friendship.getFriendshipDate().getMonth());
        assertEquals(LocalDateTime.now().getYear(), friendship.getFriendshipDate().getYear());
        assertEquals(friendship.getFirstUsername(), "eu");
        assertEquals(friendship.getSecondUsername(), "tu");

        Friendship friendshipNew = new Friendship("eu", "tu", LocalDateTime.now().plusYears(10));
        assertEquals(friendshipNew.getFriendshipDate().getYear(), LocalDateTime.now().plusYears(10).getYear());
    }

    @Test
    @DisplayName("Testing friendship's equality")
    public void testEquality() {
        Friendship friendship1 = new Friendship("eu", "tu");
        Friendship friendship2 = new Friendship("tu", "eu");
        assertEquals(friendship1, friendship2);
    }

    @Test
    @DisplayName("Testing user's setters")
    public void testSetters() {
        Friendship friendship = new Friendship("eu", "tu");
        friendship.setFriendshipDate(LocalDateTime.now().plusDays(5));
        assertEquals(friendship.getFriendshipDate(), LocalDateTime.now().plusDays(5));
    }
}
