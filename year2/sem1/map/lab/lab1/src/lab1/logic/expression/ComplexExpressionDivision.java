package lab1.logic.expression;

import lab1.models.ComplexNumber;
import lab1.enums.Operation;

public class ComplexExpressionDivision extends ComplexExpression {

    public ComplexExpressionDivision(ComplexNumber[] args, Operation operation) {
        super(args, operation);
    }
    @Override
    ComplexNumber executeOneOperation(ComplexNumber complexNumber, ComplexNumber result) {
        result.impartire(complexNumber);
        return result;
    }
}
