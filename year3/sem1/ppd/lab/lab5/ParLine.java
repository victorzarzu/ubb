import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.*;

public class ParLine {
    public static void main(String[] args) {
        if(args.length != 4) {
            System.out.println("Usage: java Main <input_file> <conv_mat_file> <output_file> <no_threads>");
            System.exit(1);
        }

        String matFilePath = args[0];
        String convFilePath = args[1];
        String outputFilePath = args[2];
        noThreads = Integer.parseInt(args[3]);
        barrier = new CyclicBarrier(noThreads);

        try(Scanner scanner = new Scanner(new File(matFilePath))) {
            nMat = scanner.nextInt();
            mMat = scanner.nextInt();
            mat = new int[nMat][mMat];
            
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
                    writer.write(mat[i][j] + " ");
                }
            }
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    // Aplica operatia de convolutie pe matricea mat in locatia data de i si j cu matricea de convolutie conv_mat
    private static int conv(int i, int j, int[][] temp) {
        int sum = 0;
        for(int row = 0;row < nConv;++row) {
            for(int column = j - (mConv / 2);column <= j + (mConv / 2);++column) {
                int convVal = conv_mat[row][column - j + (mConv / 2)];
                sum += temp[row][Math.min(mMat - 1, Math.max(0, column))] * convVal;
            }
        }
        return sum;
    }

    // Aplica operatia de convolutie pe matricea de intrare, distribuind linii thread-urilor
    private static void applyConv() {
        List<Thread> threads = new ArrayList<>();
        
        if(noThreads <= nMat) {
            int linesPerThread = nMat / noThreads;
            for(int i = 0;i < noThreads;++i) {
                int startLine = i * linesPerThread;
                int endLine = (i + 1) * linesPerThread - 1;
                if(i == noThreads - 1) {
                    endLine = nMat - 1;
                }

                System.out.println(startLine + " " + endLine);
                Thread thread = new Thread(new ApplyConvLines(startLine, endLine, mMat));
                thread.start();
                threads.add(thread);
            }
        } else {
            for(int i = 0;i < nMat;++i) {
                Thread thread = new Thread(new ApplyConvLines(i, i, mMat));
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

    // Clasa care aplica operatia de convolutie intre liniile startLine si endLine
    private static class ApplyConvLines implements Runnable {
        private int startLine, endLine, mMat;
        private int[] below;
        private int[][] temp;

        public ApplyConvLines(int startLine, int endLine, int mMat) {
            this.startLine = startLine;
            this.endLine = endLine;
            this.mMat = mMat;
            this.below = new int[mMat];
            this.temp = new int[3][mMat];

            for(int i = 0;i < mMat;++i) {
                temp[0][i] = mat[Math.max(0, startLine - 1)][i];
                below[i] = mat[Math.min(nMat - 1, endLine + 1)][i];
            }
            for(int i = 0;i < mMat;++i) {
                temp[1][i] = mat[startLine][i];
            }

        }

        public void run() {
            try { 
                barrier.await();
            } catch(InterruptedException ex) {
                ex.printStackTrace();
            } catch (BrokenBarrierException ex) {
                return;
            }

            for(int i = startLine;i <= endLine;++i) {
                if(i == endLine) {
                    for(int j = 0;j < mMat;++j) {
                        temp[2][j] = below[j];
                    }
                } else {
                    for(int j = 0;j < mMat;++j) {
                        temp[2][j] = mat[i + 1][j];
                    }
                }
                for(int j = 0;j < mMat;++j) {
                    mat[i][j] = conv(i, j, temp);
                }
                for(int j = 0;j < mMat;++j) {
                    temp[0][j] = temp[1][j];
                    temp[1][j] = temp[2][j];
                }
            }
        }
    }

    private static int nMat, mMat, nConv, mConv, noThreads;
    private static int[][] mat, conv_mat, result_mat; 
    private static CyclicBarrier barrier;
}