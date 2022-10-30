package lab2.logic.container;

import lab2.models.Task;

public class StackContainer extends AbstractContainer {

    @Override
    public void add(Task task) {
        if(size == this.tasks.length) {
            this.resizeTasks();
        }
        this.tasks[size] = task;
        ++size;
    }
}
