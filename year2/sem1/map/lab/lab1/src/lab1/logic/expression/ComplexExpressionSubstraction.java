package lab1.logic.expression;

import lab1.models.ComplexNumber;
import lab1.enums.Operation;

public class ComplexExpressionSubstraction extends ComplexExpression {

    public ComplexExpressionSubstraction(ComplexNumber[] args, Operation operation) {
        super(args, operation);
    }
    @Override
    ComplexNumber executeOneOperation(ComplexNumber complexNumber, ComplexNumber result) {
        result.scadere(complexNumber);
        return result;
    }
}
