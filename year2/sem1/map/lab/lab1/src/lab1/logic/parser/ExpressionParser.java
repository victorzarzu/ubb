package lab1.logic.parser;

import lab1.enums.Operation;
import lab1.exceptions.NumarComplexInvalidException;
import lab1.logic.expression.ComplexExpression;
import lab1.logic.factory.ExpressionFactory;
import lab1.logic.validation.NumarComplexValidator;
import lab1.models.ComplexNumber;

public class ExpressionParser {

    private static ExpressionParser instance = new ExpressionParser();
    public ComplexExpression parse(String expression) throws NumarComplexInvalidException {
        String[] array = expression.split(" ");
        ComplexNumber[] numere = new ComplexNumber[array.length - 1];

        for(int i = 0;i < array.length - 1;++i) {
            NumarComplexValidator.validate(array[i]);
            numere[i] = ComplexNumberParser.parse(array[i]);
        }

        switch (array[array.length - 1]) {
            case "+":
                return ExpressionFactory.getInstance().createExpression(Operation.ADDITION, numere);
            case "-":
                return ExpressionFactory.getInstance().createExpression(Operation.SUBSTRACTION, numere);
            case "*":
                return ExpressionFactory.getInstance().createExpression(Operation.MULTIPLICATION, numere);
            default:
                return ExpressionFactory.getInstance().createExpression(Operation.DIVISION, numere);
        }
    }

    public static ExpressionParser getInstance() {
        return instance;
    }
}
