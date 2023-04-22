package bugs.persistance.repository.tester;

import bugs.model.Tester;
import bugs.persistance.repository.Repository;

import javax.transaction.Transactional;

@org.springframework.stereotype.Repository
@Transactional
public interface TestersRepository extends Repository<Integer, Tester> {
    @Transactional
    public Tester findByUsernamePassword(String username, String password);
}
