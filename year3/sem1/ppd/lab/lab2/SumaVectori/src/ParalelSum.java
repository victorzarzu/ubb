import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class ParalelSum {
    public static void main(String[] args) {
        if(args.length != 3) {
            System.out.println("Usage: java Main <input_file> <output_file> <no_threads>");
            System.exit(1);
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];
        int numberOfThreads = Integer.parseInt(args[2]);

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

            ExecutorService executorService = Executors.newFixedThreadPool(numberOfThreads);
            int chunkSize = vectorSize / numberOfThreads;

            for(int i = 0;i < numberOfThreads; ++i)
            {
                int start = i * chunkSize;
                int end = (i == numberOfThreads - 1 ? vectorSize : (i + 1) * chunkSize);
                executorService.submit(new ParallelLiniar(start, end, A, B, C));
                //executorService.submit(new ParallelCyclic(i, numberOfThreads, A, B, C));
            }

            executorService.shutdown();
            try {
                executorService.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
            } catch (InterruptedException e) {
                e.printStackTrace();
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


    private static class ParallelLiniar implements Runnable {
        private int start, end;
        private long[] A, B, C;

        public ParallelLiniar(int start, int end, long[] A, long[] B, long[] C) {
            this.start = start;
            this.end = end;
            this.A = A;
            this.B = B;
            this.C = C;
        }

        public void run() {
            for(int i = start;i < end;i++) {
                C[i] = power(A[i], B[i]);
            }
        }
    }

    private static class ParallelCyclic implements Runnable {
        private int index, step;
        private long[] A, B, C;

        public ParallelCyclic(int index, int step, long[] A, long[] B, long[] C) {
            this.index = index;
            this.step = step;
            this.A = A;
            this.B = B;
            this.C = C;

        public void run() {
            for(int i = this.index;i < A.length;i += this.step) {
                C[i] = power(A[i], B[i]);
            }
        }
    }
}