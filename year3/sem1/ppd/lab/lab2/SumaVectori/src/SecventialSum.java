import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

public class SecventialSum {
    public static void main(String[] args) {
        if(args.length != 2) {
            System.out.println("Usage: java Main <input_file> <output_file>");
            System.exit(1);
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try(Scanner scanner = new Scanner(new File(inputFilePath))) {
            int vectorSize = scanner.nextInt();
            long[] A = new long[vectorSize];
            long[] B = new long[vectorSize];
            long[] C = new long[vectorSize];

            for(int i = 0;i < vectorSize;i++) {
                A[i] = scanner.nextInt();
            }
            for(int i = 0;i < vectorSize;i++) {
                B[i] = scanner.nextInt();
            }

            for(int i = 0;i < vectorSize;i++) {
                C[i] = power(A[i], B[i]);
            }

            try(FileWriter writer = new FileWriter(outputFilePath)) {
                writer.write(vectorSize + "\n");
                for(int i = 0;i < vectorSize;i++) {
                    writer.write(C[i] + " ");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static long power(long a, long b) {
        final long mod = 666013;
        for(int i = 1;i <= b;++i) {
            a = (a * a) % mod;
        }
        return a;
        //return Math.round(Math.pow(a, 3)) % mod + Math.round(Math.pow(b, 3)) % mod;
    }
}