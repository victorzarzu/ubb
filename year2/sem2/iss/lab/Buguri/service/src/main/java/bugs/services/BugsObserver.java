package bugs.services;

import bugs.model.Bug;

public interface BugsObserver {
    public void bugAdded(Bug bug);
}
