package lab2.logic.container;

import lab2.models.Task;

public class QueueContainer extends AbstractContainer {

    @Override
    public void add(Task task) {
        if(size == this.tasks.length) {
            resizeTasks();
        }
        if(size > 0) {
            for (int i = size; i >= 1; --i) {
                this.tasks[i] = this.tasks[i - 1];
            }
        }
        this.tasks[0] = task;
        ++size;
    }
}
