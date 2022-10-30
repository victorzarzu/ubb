package lab1;

import lab1.models.ComplexNumber;

public class Tester {
    private static void TestNumarComplex() {
        ComplexNumber numar1 = new ComplexNumber(1, 2);
        ComplexNumber numar2 = new ComplexNumber(2, 3);

        numar1.adunare(numar2);
        System.out.println(String.valueOf(numar1.getRe()) + " " + String.valueOf(numar1.getIm()));
    }

    public void Run() {
        TestNumarComplex();
    }
}
