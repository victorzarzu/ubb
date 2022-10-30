package lab1.logic;

import lab1.models.NumarComplex;
import lab1.enums.Operation;

public class ComplexExpressionSubstraction extends ComplexExpression {

    public ComplexExpressionSubstraction(NumarComplex[] args, Operation operation) {
        super(args, operation);
    }
    @Override
    NumarComplex executeOneOperation(NumarComplex numarComplex, NumarComplex result) {
        result.scadere(numarComplex);
        return result;
    }
}
