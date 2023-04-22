package bugs.persistance.repository.comment;

import bugs.model.Comment;
import bugs.persistance.repository.Repository;
import org.springframework.transaction.annotation.Transactional;

@org.springframework.stereotype.Repository
@Transactional
public interface CommentsRepository extends Repository<Integer, Comment> {
}
