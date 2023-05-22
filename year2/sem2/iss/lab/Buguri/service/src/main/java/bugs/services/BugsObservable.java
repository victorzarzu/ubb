package bugs.services;

import bugs.model.Bug;

public interface BugsObservable {
    public void addObserver(BugsObserver observer);
    public void removeObserver(BugsObserver observer);

    public void notifyObserversBugDeleted(Bug bug);

    public void notifyObserversBugAdded(Bug bug);
    public void notifyObserversBugModified(Bug bug);
}
