package bugs.services;

import java.util.HashSet;
import java.util.Set;

public class ConcreteObservable implements BugsObservable {

    Set<BugsObserver> bugsObservers = new HashSet<BugsObserver>();

    @Override
    public void addObserver(BugsObserver observer) {
        bugsObservers.add(observer);
    }

    @Override
    public void removeObserver(BugsObserver observer) {
        bugsObservers.remove(observer);
    }
}
