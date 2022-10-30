package lab1;

import lab1.exceptions.NumarComplexInvalidException;
import lab1.logic.expression.ComplexExpression;
import lab1.logic.parser.ExpressionParser;
import lab1.models.ComplexNumber;

public class Main {
    public static void main(String[] args) {
        String input = "2+2+5i 5-2i 3+1i -5i 3+2i-1i+2i+2 +";
        try {
            ComplexExpression expression = ExpressionParser.getInstance().parse(input);
            ComplexNumber result = expression.execute();
            System.out.println(String.valueOf(result.getRe()) + " " + String.valueOf(result.getIm()));
        } catch (NumarComplexInvalidException exception) {
            System.out.println(exception.getMessage());
            return;
        }
    }
}