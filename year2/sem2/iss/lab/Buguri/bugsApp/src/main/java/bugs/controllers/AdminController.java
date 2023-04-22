package bugs.controllers;

import bugs.model.Admin;
import bugs.model.Bug;
import bugs.services.BugsObserver;
import bugs.services.BugsService;

public class AdminController implements BugsObserver {
    private BugsService bugsService;
    private Admin admin;



    public void setBugsService(BugsService bugsService) {
        this.bugsService = bugsService;
    }

    public void setAdmin(Admin admin) {
        this.admin = admin;
    }

    @Override
    public void bugAdded(Bug bug) {
        // TODO Auto-generated method stub
    }
}
