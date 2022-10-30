package logic.factory;

import utils.sorter.AbstractSorter;
import utils.sorter.BubbleSorter;
import utils.sorter.QuickSorter;
import utils.sorter.SortingStrategy;

public class SorterFactory {

    private static SorterFactory instance = new SorterFactory();
    public AbstractSorter createSorter(SortingStrategy strategy) {
        AbstractSorter sorter;
        if (strategy == SortingStrategy.BUBBLE) {
            sorter = new BubbleSorter();
        }
        sorter = new QuickSorter();
        return sorter;
    }

    public static SorterFactory getInstance() {
       return instance;
    }
}
