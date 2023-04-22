package bugs.persistance.repository.admin;

import bugs.model.Admin;
import bugs.persistance.dao.admin.AdminDAO;
import org.hibernate.cfg.NotYetImplementedException;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

@Repository
@Transactional
public class AdminsDbRepository implements AdminsRepository {
    private AdminDAO adminDAO;

    public void setAdminDAO(AdminDAO adminDAO) {
        this.adminDAO = adminDAO;
    }

    @Override
    @Transactional
    public void add(Admin admin) {
        adminDAO.save(admin);
    }

    @Override
    @Transactional
    public void remove(Admin admin) {
        adminDAO.delete(admin);
    }

    @Override
    @Transactional
    public void modify(Admin admin) {
        throw new NotYetImplementedException("Update not implemented");
    }

    @Override
    @Transactional
    public Iterable<Admin> findAll() {
        return adminDAO.getAll();
    }

    @Override
    @Transactional
    public Admin findByUsernamePassword(String username, String password) {
        return adminDAO.findByUsernameAndPassword(username, password);
    }
}
