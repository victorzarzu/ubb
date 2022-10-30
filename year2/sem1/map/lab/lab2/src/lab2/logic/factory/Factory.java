package logic.factory;

import logic.container.Strategy;
import logic.container.Container;

public interface Factory {
    Container createContainer(Strategy strategy);
}
