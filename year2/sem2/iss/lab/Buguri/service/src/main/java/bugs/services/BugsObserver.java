package bugs.services;

import bugs.model.Bug;

public interface BugsObserver {
    public void bugAdded(Bug bug);

    public void bugDeleted(Bug bug);

    public void bugModified(Bug bug);
}
