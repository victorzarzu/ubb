package logic.factory;

import logic.container.Strategy;
import logic.container.Container;
import logic.container.QueueContainer;
import logic.container.StackContainer;

public class TaskContainerFactory implements Factory {
    private static TaskContainerFactory instance = new TaskContainerFactory();

    @Override
    public Container createContainer(Strategy strategy) {
        switch (strategy) {
            case LIFO:
                return new StackContainer();
            default:
                return new QueueContainer();
        }
    }

    private TaskContainerFactory(){};

    public static TaskContainerFactory getInstance() {
        return instance;
    }
}
