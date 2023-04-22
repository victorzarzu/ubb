package bugs.persistance.dao.admin;

import bugs.model.Admin;
import bugs.model.User;

import java.util.List;

public interface AdminDAO {
    public void save(Admin admin);
    public void delete(Admin admin);

    public Iterable<Admin> getAll();

    public Admin findByUsernameAndPassword(String username, String password);
}
