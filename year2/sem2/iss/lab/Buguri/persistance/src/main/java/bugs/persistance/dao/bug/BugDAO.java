package bugs.persistance.dao.bug;

import bugs.model.Bug;
import bugs.model.Tester;

import java.util.List;

public interface BugDAO {
    public void save(Bug bug);
    public void delete(Bug bug);

    public void update(Bug bug);

    public List<Bug> getAll();
}
