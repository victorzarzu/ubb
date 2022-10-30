package lab1.logic;

import lab1.models.NumarComplex;
import lab1.enums.Operation;

public class ComplexExpressionMultiplication extends ComplexExpression {

    public ComplexExpressionMultiplication(NumarComplex[] args, Operation operation) {
        super(args, operation);
    }
    @Override
    NumarComplex executeOneOperation(NumarComplex numarComplex, NumarComplex result) {
        result.inmultire(numarComplex);
        return result;
    }
}
