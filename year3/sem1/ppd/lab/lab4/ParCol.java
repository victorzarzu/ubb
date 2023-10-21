import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class ParCol {
    public static void main(String[] args) {
        if(args.length != 4) {
            System.out.println("Usage: java Main <input_file> <conv_mat_file> <output_file> <no_threads>");
            System.exit(1);
        }

        String matFilePath = args[0];
        String convFilePath = args[1];
        String outputFilePath = args[2];
        noThreads = Integer.parseInt(args[3]);

        try(Scanner scanner = new Scanner(new File(matFilePath))) {
            nMat = scanner.nextInt();
            mMat = scanner.nextInt();
            mat = new int[nMat][mMat];
            result_mat = new int[nMat][mMat];
            
            for(int i = 0;i < nMat;++i) {
                for(int j = 0 ;j < mMat;++j) {
                    mat[i][j] = scanner.nextInt();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        try(Scanner scanner = new Scanner(new File(convFilePath))) {
            nConv = scanner.nextInt();
            mConv= scanner.nextInt();
            conv_mat = new int[nConv][mConv];
            
            for(int i = 0;i < nConv;++i) {
                for(int j = 0 ;j < mConv;++j) {
                    conv_mat[i][j] = scanner.nextInt();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        applyConv();

        try(FileWriter writer = new FileWriter(outputFilePath)) {
            writer.write(nMat + " " + mMat + "\n");
            for(int i = 0;i < nMat;++i, writer.write("\n")) {
                for(int j = 0;j < mMat;++j) {
                    writer.write(result_mat[i][j] + " ");
                }
            }
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    private static int conv(int i, int j) {
        int sum = 0;
        for(int row = i - (nConv / 2);row <= i + (nConv / 2);++row) {
            for(int column = j - (mConv / 2);column <= j + (mConv / 2);++column) {
                sum += mat[Math.min(nMat - 1, Math.max(0, row))][Math.min(mMat - 1, Math.max(0, column))] * conv_mat[row - i + (nConv / 2)][column - j + (mConv / 2)];
            }
        }
        return sum;
    }

    private static void applyConv() {
        List<Thread> threads = new ArrayList<>();
        
        if(noThreads <= mMat) {
            int colsPerThread = mMat / noThreads;
            for(int i = 0;i < noThreads;++i) {
                int startCol = i * colsPerThread;
                int endCol = (i + 1) * colsPerThread;
                if(i == noThreads - 1) {
                    endCol = mMat - 1;
                }
                Thread thread = new Thread(new ApplyConvCols(startCol, endCol));
                thread.start();
                threads.add(thread);
            }
        } else {
            for(int i = 0;i < mMat;++i) {
                Thread thread = new Thread(new ApplyConvCols(i, i));
                thread.start();
                threads.add(thread);
            }
        }

        try {
            for(Thread thread : threads) {
                thread.join();
            }
        } catch(InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static class ApplyConvCols implements Runnable {
        private int startCol, endCol;

        public ApplyConvCols(int startCol, int endCol) {
            this.startCol = startCol;
            this.endCol = endCol;
        }

        public void run() {
            for(int i = 0;i < nMat;++i) {
                for(int j = startCol;j <= endCol;++j) {
                    result_mat[i][j] = conv(i, j);
                }
            }
        }
    }

    private static int nMat, mMat, nConv, mConv, noThreads;
    private static int[][] mat, conv_mat, result_mat; 
}