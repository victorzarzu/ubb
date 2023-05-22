package bugs.controllers;

import bugs.model.Admin;
import bugs.model.Bug;
import bugs.services.BugsObserver;
import bugs.services.BugsService;

public class AdminController extends Controller {
    private Admin admin;

    public void setAdmin(Admin admin) {
        this.admin = admin;
    }

    @Override
    public void setBugsService(BugsService bugsService) {
        super.setBugsService(bugsService);
    }

    @Override
    protected void initComponents() {

    }
}
