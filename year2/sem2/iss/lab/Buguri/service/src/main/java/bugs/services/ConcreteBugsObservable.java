package bugs.services;

import bugs.model.Bug;

import java.util.HashSet;
import java.util.Set;

public abstract class ConcreteBugsObservable implements BugsObservable {

    protected Set<BugsObserver> bugsObservers = new HashSet<BugsObserver>();

    @Override
    public void addObserver(BugsObserver observer) {
        bugsObservers.add(observer);
    }

    @Override
    public void removeObserver(BugsObserver observer) {
        bugsObservers.remove(observer);
    }

    public void notifyObserversBugDeleted(Bug bug) {
        for(BugsObserver bugsObserver : this.bugsObservers) {
            bugsObserver.bugDeleted(bug);
        }
    }

    public void notifyObserversBugAdded(Bug bug) {
        for(BugsObserver bugsObserver : this.bugsObservers) {
            bugsObserver.bugAdded(bug);
        }
    }

    public void notifyObserversBugModified(Bug bug) {
        for(BugsObserver bugsObserver : this.bugsObservers) {
            bugsObserver.bugModified(bug);
        }
    }
}
