package bugs.persistance.repository.exceptions;

public class InexistentEntityException extends RepositoryException {
    public InexistentEntityException(String message) {
        super(message);
    }

    public InexistentEntityException(String message, Throwable cause) {
        super(message, cause);
    }

    public InexistentEntityException(Throwable cause) {
        super(cause);
    }
}
