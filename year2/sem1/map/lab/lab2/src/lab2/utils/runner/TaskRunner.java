package lab2.utils.runner;

import lab2.models.Task;

public interface TaskRunner {
    void executeOneTask();
    void executeAll();
    void addTask(Task t);
    boolean hasTask();
}
