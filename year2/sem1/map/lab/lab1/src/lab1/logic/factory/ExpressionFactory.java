package lab1.logic.factory;

import lab1.enums.Operation;
import lab1.logic.expression.*;
import lab1.models.ComplexNumber;

public class ExpressionFactory {
    private static final ExpressionFactory instance = new ExpressionFactory();

    private ExpressionFactory() {}

    public ComplexExpression createExpression(Operation operation, ComplexNumber[] args) {
        return switch (operation) {
            case ADDITION -> new ComplexExpressionAddition(args, operation);
            case SUBSTRACTION -> new ComplexExpressionSubstraction(args, operation);
            case MULTIPLICATION -> new ComplexExpressionMultiplication(args, operation);
            default -> new ComplexExpressionDivision(args, operation);
        };
    }

    public static ExpressionFactory getInstance() {
        return instance;
    }
}