package bugs.controllers;

import bugs.model.Bug;
import bugs.model.Programmer;
import bugs.services.BugsObserver;
import bugs.services.BugsService;

public class ProgrammerController implements BugsObserver {
    private BugsService bugsService;
    private Programmer programmer;

    public void setBugsService(BugsService bugsService) {
        this.bugsService = bugsService;
    }

    public void setProgrammer(Programmer programmer) {
        this.programmer = programmer;
    }

    @Override
    public void bugAdded(Bug bug) {
        // TODO Auto-generated method stub
    }
}
