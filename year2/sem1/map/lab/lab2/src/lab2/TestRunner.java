package lab2;

import lab2.logic.container.Strategy;
import lab2.models.MessageTask;
import lab2.models.SortingTask;
import lab2.utils.runner.DelayTaskRunner;
import lab2.utils.runner.PrinterTaskRunner;
import lab2.utils.runner.StrategyTaskRunner;
import lab2.utils.runner.TaskRunner;
import lab2.utils.sorter.SortingStrategy;

import java.time.LocalDateTime;

public class TestRunner {
    private Strategy strategy;

    public TestRunner(String strategy) {
        this.strategy = Strategy.valueOf(strategy);
    }
    private static MessageTask[] createMessages() {
        MessageTask m1 = new MessageTask("1", "tema pentru lab", "ai primit o tema pentru lab", "Victor", "Andrei", LocalDateTime.now());
        MessageTask m2 = new MessageTask("2", "tema pentru lab", "ai primit o tema pentru lab", "Victor", "Oana", LocalDateTime.now());
        MessageTask m3 = new MessageTask("3", "tema pentru seminar", "ai primit o tema pentru seminar", "Andrei", "Emi", LocalDateTime.now());

        return new MessageTask[]{m1, m2, m3};
    }

    private static int[] createIntArray() {
        return new int[]{7, 10, -5, 3, -100, 5, 0, 5, 10};
    }

    private static SortingTask[] createSorters() {
        SortingTask s1 = new SortingTask("1", "sort with bubble sort", SortingStrategy.BUBBLE, createIntArray());
        SortingTask s2 = new SortingTask("2", "sort with quick sort", SortingStrategy.QUICK, createIntArray());

        return new SortingTask[]{s1, s2};
    }

    public void runStrategyTaskRunner() {
        MessageTask[] messageTasks = createMessages();
        TaskRunner strategyTaskRunner = new StrategyTaskRunner(this.strategy);
        for(MessageTask messageTask : messageTasks) {
            strategyTaskRunner.addTask(messageTask);
        }
        strategyTaskRunner.executeAll();
    }

    public void runPrinterTaskRunner() {
        MessageTask[] messageTasks = createMessages();
        TaskRunner strategyTaskRunner = new StrategyTaskRunner(this.strategy);
        for(MessageTask messageTask : messageTasks) {
            strategyTaskRunner.addTask(messageTask);
        }
        strategyTaskRunner.executeAll();
        System.out.println();

        for(MessageTask messageTask : messageTasks) {
            strategyTaskRunner.addTask(messageTask);
        }
        TaskRunner printerTaskRunner = new PrinterTaskRunner(strategyTaskRunner);
        printerTaskRunner.executeAll();
    }

    public void runAllTaskRunners() {
        MessageTask[] messageTasks = createMessages();
        TaskRunner strategyTaskRunner = new StrategyTaskRunner(this.strategy);
        for(MessageTask messageTask : messageTasks) {
            strategyTaskRunner.addTask(messageTask);
        }
        strategyTaskRunner.executeAll();
        System.out.println();

        TaskRunner delayTaskRunner = new DelayTaskRunner(strategyTaskRunner);
        for(MessageTask messageTask : messageTasks) {
            delayTaskRunner.addTask(messageTask);
        }
        delayTaskRunner.executeAll();
        System.out.println();

        TaskRunner printerTaskRunner = new PrinterTaskRunner(strategyTaskRunner);
        for(MessageTask messageTask : messageTasks) {
            printerTaskRunner.addTask(messageTask);
        }
        printerTaskRunner.executeAll();
    }


    public void Run() {
        MessageTask[] lista = createMessages();
        for(MessageTask mesaj : lista) {
            mesaj.execute();
        }

        SortingTask[] sortingTasks = createSorters();
        for(SortingTask sortingTask : sortingTasks) {
            sortingTask.execute();
        }

        this.runStrategyTaskRunner();
        this.runPrinterTaskRunner();
        this.runAllTaskRunners();
    }
}
