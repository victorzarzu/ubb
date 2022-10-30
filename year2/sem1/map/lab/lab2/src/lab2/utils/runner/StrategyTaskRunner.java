package utils.runner;

import logic.container.Strategy;
import logic.factory.TaskContainerFactory;
import models.Task;
import logic.container.Container;

public class StrategyTaskRunner implements TaskRunner {
    private Container container;

    public StrategyTaskRunner(Strategy strategy) {
        container = TaskContainerFactory.getInstance().createContainer(strategy);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }

    @Override
    public void addTask(Task task) {
        container.add(task);
    }

    @Override
    public void executeOneTask() {
        Task task = container.remove();
        System.out.println("S-a exectutat: " + task.toString());
    }

    @Override
    public void executeAll() {
        while(!container.isEmpty()) {
            this.executeOneTask();
        }
    }
}
