package logic.container;

import models.Task;

import java.util.Arrays;

public class QueueContainer extends AbstractContainer {

    private Task deleteQueue() {
        Task result = this.tasks[0];
        for(int i = 0;i < size;++i) {
            this.tasks[i] = this.tasks[i + 1];
        }
        --size;

        return result;
    }
    @Override
    public Task remove() {
        if(!isEmpty()) {
            return deleteQueue();
        }

        return null;
    }

    @Override
    public void add(Task task) {
        if(size == this.tasks.length) {
            resizeTasks();
        }
        this.tasks[size] = task;
        ++size;
    }
}
