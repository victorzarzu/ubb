package lab2.utils.runner;

import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

public class PrinterTaskRunner extends AbstractTaskRunner {

    public PrinterTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }

    @Override
    public void executeOneTask() {
        super.executeOneTask();
        decorate();
    }

    private void decorate() {
        System.out.println("Time: " + LocalTime.now().format(DateTimeFormatter.ISO_LOCAL_TIME));
    }
}
