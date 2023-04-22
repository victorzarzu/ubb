package bugs.persistance.dao.programmer;

import bugs.model.Programmer;
import bugs.model.User;

import java.util.List;

public interface ProgrammerDAO {
    public void save(Programmer programmer);
    public void delete(Programmer programmer);
    public void update(Programmer programmer);

    public Programmer findByUsernameAndPassword(String username, String password);

    public List<Programmer> getAll();
}
