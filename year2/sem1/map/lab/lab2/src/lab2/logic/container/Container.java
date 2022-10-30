package lab2.logic.container;

import lab2.models.Task;

public interface Container {
    public static final int CONTAINER_INIT_LENGTH = 10;
    Task remove();
    void add(Task task);
    int size();
    boolean isEmpty();
}
