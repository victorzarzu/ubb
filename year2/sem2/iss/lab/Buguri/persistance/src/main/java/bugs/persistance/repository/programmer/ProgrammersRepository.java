package bugs.persistance.repository.programmer;

import bugs.model.Programmer;
import bugs.persistance.repository.Repository;

import javax.transaction.Transactional;

public interface ProgrammersRepository extends Repository<Integer, Programmer> {
    @Transactional
    public Programmer findByUsernamePassword(String username, String password);
}
