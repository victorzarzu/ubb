package bugs.persistance.repository.bug;

import bugs.model.Bug;
import bugs.persistance.repository.Repository;
import org.springframework.transaction.annotation.Transactional;

@org.springframework.stereotype.Repository
@Transactional
public interface BugsRepository extends Repository<Integer, Bug> {
}
