package bugs.persistance.dao.user;

import bugs.model.User;

import java.util.List;

public interface UserDAO {
    public void save(User user);
    public void delete(User user);
    public void update(User user);

    public List<User> getAll();
}
