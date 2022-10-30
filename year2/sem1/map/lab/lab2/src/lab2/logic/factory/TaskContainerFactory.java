package lab2.logic.factory;

import lab2.logic.container.Strategy;
import lab2.logic.container.Container;
import lab2.logic.container.QueueContainer;
import lab2.logic.container.StackContainer;

public class TaskContainerFactory implements Factory {
    private static TaskContainerFactory instance = new TaskContainerFactory();

    @Override
    public Container createContainer(Strategy strategy) {
        switch (strategy) {
            case LIFO:
                return new StackContainer();
            case FIFO:
                return new QueueContainer();
            default:
                return null;
        }
    }

    private TaskContainerFactory() {};

    public static TaskContainerFactory getInstance() {
        return instance;
    }
}
