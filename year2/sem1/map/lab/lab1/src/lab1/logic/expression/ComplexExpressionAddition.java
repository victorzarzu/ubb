package lab1.logic;

import lab1.models.NumarComplex;
import lab1.enums.Operation;

public class ComplexExpressionAddition extends ComplexExpression {

    public ComplexExpressionAddition(NumarComplex[] args, Operation operation) {
        super(args, operation);
    }
    @Override
    NumarComplex executeOneOperation(NumarComplex numarComplex, NumarComplex result) {
        result.adunare(numarComplex);
        return result;
    }
}
