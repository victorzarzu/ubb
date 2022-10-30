package utils.runner;

public class DelayTaskRunner extends AbstractTaskRunner {

    public DelayTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }

    @Override
    public void executeOneTask() {
        try{
            Thread.sleep(1000);
            super.executeOneTask();
        } catch (InterruptedException exception) {
            exception.printStackTrace();
        }
    }
}
