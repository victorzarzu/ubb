package bugs.persistance.dao.tester;

import bugs.model.Programmer;
import bugs.model.Tester;
import org.springframework.stereotype.Repository;

import javax.transaction.Transactional;
import java.util.List;

@Repository
@Transactional
public interface TesterDAO {
    public void save(Tester tester);
    public void delete(Tester tester);
    public void update(Tester tester);

    public Tester findByUsernameAndPassword(String username, String password);

    public List<Tester> getAll();
}
