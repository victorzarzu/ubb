package bugs.persistance.repository.admin;

import bugs.model.Admin;
import bugs.persistance.repository.Repository;
import org.springframework.transaction.annotation.Transactional;

@org.springframework.stereotype.Repository
@Transactional
public interface AdminsRepository extends Repository<Integer, Admin> {
    @Transactional
    public Admin findByUsernamePassword(String username, String password);
}
