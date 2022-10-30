package lab1.logic;

import lab1.enums.Operation;
import lab1.exceptions.NumarComplexInvalidException;
import lab1.logic.factory.ExpressionFactory;
import lab1.logic.validation.NumarComplexValidator;
import lab1.models.NumarComplex;
import lab1.logic.parser.NumarComplexParser;

public class ExpressionParser {
    public static ComplexExpression parse(String expression) throws NumarComplexInvalidException {
        String[] array = expression.split(" ");
        NumarComplex[] numere = new NumarComplex[array.length - 1];

        for(int i = 0;i < array.length - 1;++i) {
            NumarComplexValidator.validate(array[i]);
            numere[i] = NumarComplexParser.parse(array[i]);
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
}
