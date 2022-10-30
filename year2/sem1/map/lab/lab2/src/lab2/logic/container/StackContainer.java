package logic.container;

import models.Task;

import java.util.Arrays;

public class StackContainer extends AbstractContainer {

    @Override
    public Task remove() {
        if(!isEmpty()) {
            size--;
            return this.tasks[size];
        }

        return null;
    }

    @Override
    public void add(Task task) {
        if(size == this.tasks.length) {
            this.resizeTasks();
        }
        this.tasks[size] = task;
        ++size;
    }
}
