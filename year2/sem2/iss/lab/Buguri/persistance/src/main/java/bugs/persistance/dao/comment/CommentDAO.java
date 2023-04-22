package bugs.persistance.dao.comment;

import bugs.model.Comment;
import bugs.model.Programmer;

public interface CommentDAO {

    public void save(Comment comment);
    public void delete(Comment comment);
}
