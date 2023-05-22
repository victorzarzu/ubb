package bugs.controllers;

import bugs.services.BugsService;

public abstract class Controller {
    protected BugsService bugsService;

    public void setBugsService(BugsService bugsService) {
        this.bugsService = bugsService;
    }

    protected abstract void initComponents();
}
