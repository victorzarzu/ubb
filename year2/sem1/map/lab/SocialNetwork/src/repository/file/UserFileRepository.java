package repository.file;

import domain.User;

import java.util.List;

public class UserFileRepository extends AbstractFileRepository<String, User> {
    public UserFileRepository(String filename) {
        super(filename);
    }

    @Override
    public User extractEntity(List<String> atributes) {
        User user = new User(atributes.get(0), atributes.get(1), atributes.get(2), atributes.get(3), atributes.get(4), atributes.get(5));
        return user;
    }

    @Override
    protected String entityEntityToString(User user) {
        return user.getId() + ";" + user.getPassword() + ";" + user.getEmail() +
                ";" + user.getFirstName() + ";" + user.getLastName() + ";" + user.getGender();
    }
}
