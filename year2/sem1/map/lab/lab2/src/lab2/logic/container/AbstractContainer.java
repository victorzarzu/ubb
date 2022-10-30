package logic.container;

import constants.Constants;
import models.Task;

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
        this.tasks = new Task[Constants.CONTAINER_INIT_LENGTH];
        size = 0;
    };

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }
}
