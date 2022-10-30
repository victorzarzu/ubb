package lab2.utils.runner;

import lab2.models.Task;

public abstract class AbstractTaskRunner implements TaskRunner {
    private TaskRunner taskRunner;

    AbstractTaskRunner(TaskRunner taskRunner) {
        this.taskRunner = taskRunner;
    }

    @Override
    public void executeOneTask() {
        this.taskRunner.executeOneTask();
    }

    @Override
    public void executeAll() {
        while(this.taskRunner.hasTask()) {
            this.executeOneTask();
        }
    }
    @Override
    public boolean hasTask() {
        return taskRunner.hasTask();
    }

    @Override
    public void addTask(Task task) {
        this.taskRunner.addTask(task);
    }
}
