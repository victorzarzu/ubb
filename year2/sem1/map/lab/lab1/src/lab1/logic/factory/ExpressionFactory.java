package Logic;

import Enums.Operation;
import Models.NumarComplex;

public class ExpressionFactory {
    private static ExpressionFactory instance = new ExpressionFactory();

    private ExpressionFactory() {};

    public ComplexExpression createExpression(Operation operation, NumarComplex[] args) {
        switch (operation) {
            case ADDITION:
                return new ComplexExpressionAddition(args, operation);
            case SUBSTRACTION:
                return new ComplexExpressionSubstraction(args, operation);
            case MULTIPLICATION:
                return new ComplexExpressionMultiplication(args, operation);
            default:
                return new ComplexExpressionDivision(args, operation);
        }
    }

    public static ExpressionFactory getInstance() {
        return instance;
    }
}
