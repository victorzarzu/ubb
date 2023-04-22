package bugs.persistance.repository.exceptions;

public class ExistentEntityException extends RepositoryException {
    public ExistentEntityException(String message) {
        super(message);
    }

    public ExistentEntityException(String message, Throwable cause) {
        super(message, cause);
    }

    public ExistentEntityException(Throwable cause) {
        super(cause);
    }
}
