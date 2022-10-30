package lab1.logic;

import lab1.models.NumarComplex;
import lab1.enums.Operation;

public abstract class ComplexExpression {

    private Operation operation;
    private NumarComplex[] args;

    ComplexExpression(NumarComplex[] args, Operation operation) {
        this.args = args;
        this.operation = operation;
    }

    abstract NumarComplex executeOneOperation(NumarComplex numarComplex, NumarComplex result);

    public NumarComplex execute() {
        NumarComplex result = args[0];
        for(int i = 1;i < args.length;++i) {
            result = executeOneOperation(args[i], result);
        }
        return result;
    }
}
