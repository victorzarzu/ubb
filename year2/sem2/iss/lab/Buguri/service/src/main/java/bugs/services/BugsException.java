package bugs.services;

public class BugsException extends RuntimeException {
    public BugsException(String message) {
        super(message);
    }

    public BugsException(String message, Throwable cause) {
        super(message, cause);
    }

    public BugsException(Throwable cause) {
        super(cause);
    }
}
