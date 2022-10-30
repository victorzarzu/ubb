import Models.NumarComplex;

public class Tester {
    private static void TestNumarComplex() {
        NumarComplex numar1 = new NumarComplex(1, 2);
        NumarComplex numar2 = new NumarComplex(2, 3);

        numar1.adunare(numar2);
        System.out.println(String.valueOf(numar1.getRe()) + " " + String.valueOf(numar1.getIm()));
    }

    public void Run() {
        TestNumarComplex();
    }
}
