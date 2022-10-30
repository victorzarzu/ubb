package utils.runner;

import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

public class PrinterTaskRunner extends AbstractTaskRunner {

    public PrinterTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }

    @Override
    public void executeOneTask() {
        System.out.println("Time: " + LocalTime.now().format(DateTimeFormatter.ISO_LOCAL_TIME));
        super.executeOneTask();
    }
}
