package lab1.logic.expression;

import lab1.models.ComplexNumber;
import lab1.enums.Operation;

public abstract class ComplexExpression {

    private Operation operation;
    private ComplexNumber[] args;

    ComplexExpression(ComplexNumber[] args, Operation operation) {
        this.args = args;
        this.operation = operation;
    }

    abstract ComplexNumber executeOneOperation(ComplexNumber complexNumber, ComplexNumber result);

    public ComplexNumber execute() {
        ComplexNumber result = args[0];
        for(int i = 1;i < args.length;++i) {
            result = executeOneOperation(args[i], result);
        }
        return result;
    }
}
