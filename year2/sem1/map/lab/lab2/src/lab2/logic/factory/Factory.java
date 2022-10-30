package lab2.logic.factory;

import lab2.logic.container.Strategy;
import lab2.logic.container.Container;

public interface Factory {
    Container createContainer(Strategy strategy);
}
