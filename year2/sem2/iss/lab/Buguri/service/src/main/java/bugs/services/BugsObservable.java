package bugs.services;

public interface BugsObservable {
    public void addObserver(BugsObserver observer);
    public void removeObserver(BugsObserver observer);
}
