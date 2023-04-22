package bugs.controllers;

import bugs.model.Tester;
import bugs.services.BugsService;

public class ModifyBugController {
    private BugsService bugsService;
    private Tester tester;

    public void setBugsService(BugsService bugsService) {
        this.bugsService = bugsService;
    }

    public void setTester(Tester tester) {
        this.tester = tester;
    }
}
