package lab2.logic.container;

import lab2.constants.Constants;
import lab2.models.Task;

import java.util.Arrays;

public abstract class AbstractContainer implements Container {
    protected Task[] tasks;
    protected int size;

    protected void resizeTasks() {
        Task[] newTasks = new Task[this.tasks.length * 2];
        System.arraycopy(this.tasks, 0, newTasks, 0, size);
        this.tasks = newTasks;
    }

    public AbstractContainer() {
        this.tasks = new Task[CONTAINER_INIT_LENGTH];
        size = 0;
    };

    @Override
    public Task remove() {
        if(!isEmpty()) {
            Task result = this.tasks[size - 1];
            --size;

            return result;
        }
        return null;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }
}
