package bugs.persistance.dao.comment;

import bugs.model.Comment;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

public class CommentDAOImpl implements CommentDAO {
    private SessionFactory sessionFactory;

    public void setSessionFactory(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public void save(Comment comment) {
        Session session = this.sessionFactory.openSession();
        Transaction transaction = session.beginTransaction();
        session.persist(comment);
        transaction.commit();
        session.close();
    }

    @Override
    public void delete(Comment comment) {
        Session session = this.sessionFactory.openSession();
        Transaction transaction = session.beginTransaction();
        session.remove(comment);
        transaction.commit();
        session.close();
    }
}
