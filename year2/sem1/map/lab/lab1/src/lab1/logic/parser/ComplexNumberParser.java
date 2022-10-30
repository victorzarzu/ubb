package lab1.logic.parser;

import lab1.models.ComplexNumber;

public class ComplexNumberParser {
    static private boolean isDigit(char character) {
        return character >= '0' && character <= '9';
    }

    public static ComplexNumber parse(String numarComplex) {
        int position = 0, sign;
        double real = 0, imaginar = 0, number;
        while(position < numarComplex.length()) {
            number = 0; sign = 1;
            if("+-".contains(String.valueOf(numarComplex.charAt(position)))) {
                if(numarComplex.charAt(position) == '-') {
                    sign = -1;
                }
                ++position;
            }

            while(position < numarComplex.length() && isDigit(numarComplex.charAt(position))) {
                number = number * 10 + numarComplex.charAt(position) - '0';
                position++;
            }
            if(position < numarComplex.length() && numarComplex.charAt(position) == 'i') {
                imaginar += number * sign;
                ++position;
            }
            else {
                real += number * sign;
            }
        }

        return new ComplexNumber(real, imaginar);
    }
}
