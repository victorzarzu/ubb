package Logic.Validation;

import Exceptions.NumarComplexInvalidException;

public class NumarComplexValidator {

    static private boolean isDigit(char character) {
        return character >= '0' && character <= '9';
    }

    public static void validate(String numarComplex) throws NumarComplexInvalidException {
        if(numarComplex.isEmpty()) {
            throw new NumarComplexInvalidException("Numar gol\n");
        }
        int position = 0;
        while(position < numarComplex.length()) {
            if(numarComplex.charAt(position) == '-') {
                ++position;
            }
            while(position < numarComplex.length() && isDigit(numarComplex.charAt(position))) {
                position++;
            }
            if(position == numarComplex.length() - 1) {
                break;
            }
            if(numarComplex.charAt(position) == 'i') {
                position++;
                continue;
            }
            if(!("+-").contains(Character.toString(numarComplex.charAt(position)))) {
                throw new NumarComplexInvalidException("Numar invalid: " + numarComplex + "\n");
            }
            ++position;
        }
//        if(numarComplex.charAt(position) == '-') {
//            position++;
//        }
//        while(position < numarComplex.length() && isDigit(numarComplex.charAt(position))) {
//            position++;
//        }
//        if(numarComplex.charAt(position) == 'i' && position == numarComplex.length() - 1) {
//            return;
//        }
//        if(!("+-").contains(Character.toString(numarComplex.charAt(position)))) {
//            throw new NumarComplexInvalidException("Numar invalid: " + numarComplex + "\n");
//        }
//        ++position;
//        while(position < numarComplex.length() && isDigit(numarComplex.charAt(position))) {
//            position++;
//        }
//        if(!(numarComplex.charAt(position) == 'i')) {
//            throw new NumarComplexInvalidException("Numar invalid: " + numarComplex + "\n");
//        }
    }
}
