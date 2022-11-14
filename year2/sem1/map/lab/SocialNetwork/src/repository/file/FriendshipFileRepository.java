package repository.file;

import domain.Friendship;
import domain.User;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;

import java.time.DateTimeException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

import static constants.DateTime.DATATIME_FORMATTER;

public class FriendshipFileRepository extends AbstractFileRepository<Set<String>, Friendship> {


    /**
     * Contructor for creating a repository with persistence in file
     * @param filename - the path where the data is stored
     */
    public FriendshipFileRepository(String filename) {
        super(filename);
    }

    /**
     * Method that converts a list of attributes to a friendship
     * @param atributes the atributes of the returned entity
     * @return Friendship - the converted friendship
     */
    @Override
    public Friendship extractEntity(List<String> atributes) {
        Friendship friendship = new Friendship(atributes.get(0), atributes.get(1), LocalDateTime.parse(atributes.get(2), DATATIME_FORMATTER));
        return friendship;
    }

    /**
     * Method that converts a user to the storable form
     * @param friendship E - the entity to be converted to string
     * @return String - the conversion of the user into String
     */
    @Override
    protected String entityEntityToString(Friendship friendship) {
        List<String> usersList = new ArrayList<>(friendship.getId());
        return usersList.get(0) + ";" + usersList.get(1) + ";" + friendship.getFriendshipDate().format(DATATIME_FORMATTER) + "\n";
    }
}
