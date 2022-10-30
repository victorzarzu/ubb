package lab1.logic;

import lab1.models.NumarComplex;
import lab1.enums.Operation;

public class ComplexExpressionDivision extends ComplexExpression {

    public ComplexExpressionDivision(NumarComplex[] args, Operation operation) {
        super(args, operation);
    }
    @Override
    NumarComplex executeOneOperation(NumarComplex numarComplex, NumarComplex result) {
        result.impartire(numarComplex);
        return result;
    }
}
