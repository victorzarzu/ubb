package bugs.persistance.repository.comment;

import bugs.model.Bug;
import bugs.model.Comment;
import bugs.persistance.dao.bug.BugDAO;
import bugs.persistance.dao.comment.CommentDAO;
import bugs.persistance.repository.bug.BugsRepository;
import org.hibernate.cfg.NotYetImplementedException;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

@Repository
@Transactional
public class CommentsDbRepository implements CommentsRepository {
    private CommentDAO commentDAO;

    public void setTesterDAO(CommentDAO commentDAO) {
        this.commentDAO = commentDAO;
    }

    @Override
    @Transactional
    public void add(Comment comment) {
        this.commentDAO.save(comment);
    }

    @Override
    @Transactional
    public void remove(Comment comment) {
        this.commentDAO.delete(comment);
    }

    @Override
    @Transactional
    public void modify(Comment comment) {
        throw new NotYetImplementedException();
    }

    @Override
    @Transactional
    public Iterable<Comment> findAll() {
        throw new NotYetImplementedException();
    }
}
