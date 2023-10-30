import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

public class Secv {
    public static void main(String[] args) {
        if(args.length != 3) {
            System.out.println("Usage: java Main <input_file> <conv_mat_file> <output_file>");
            System.exit(1);
        }

        String matFilePath = args[0];
        String convFilePath = args[1];
        String outputFilePath = args[2];

        try(Scanner scanner = new Scanner(new File(matFilePath))) {
            nMat = scanner.nextInt();
            mMat = scanner.nextInt();
            mat = new int[nMat][mMat];
            temp = new int[2][mMat];
            
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
        for(int i = 0;i < mMat;++i) {
            temp[0][i] = mat[0][i];
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

    private static int getMatValue(int i, int j, int row, int column) {
        if(row < i) {
            return temp[0][Math.min(mMat - 1, Math.max(0, column))];
        } 
        if(row == i && column < j) {
            return temp[1][Math.min(mMat - 1, Math.max(0, column))];
        }
        if(row > nMat - 1 && column < j) {
            return temp[1][Math.min(mMat - 1, Math.max(0, column))];
        }
        return mat[Math.min(nMat - 1, Math.max(0, row))][Math.min(mMat - 1, Math.max(0, column))];
    }

    // Aplica operatia de convolutie pe matricea mat in locatia data de i si j cu matricea de convolutie conv_mat
    private static int conv(int i, int j) {
        int sum = 0;
        for(int row = i - (nConv / 2);row <= i + (nConv / 2);++row) {
            for(int column = j - (mConv / 2);column <= j + (mConv / 2);++column) {
                int conv_val = conv_mat[row - i + (nConv / 2)][column - j + (mConv / 2)];
                int mat_val = getMatValue(i, j, row, column);
                sum += mat_val * conv_val;
            }
        }

        return sum;
    }

    // Aplica operatia de convolutie pe toata matricea de intrare si salveaza rezultatul in result_mat
    private static void applyConv() {
        for(int i = 0;i < nMat;++i) {
            for(int j = 0;j < mMat;++j) {
                temp[1][j] = mat[i][j];
                mat[i][j] = conv(i, j);
            }
            for(int j = 0;j < mMat;++j) {
                temp[0][j] = temp[1][j];
            }
        }
    }

    private static int nMat, mMat, nConv, mConv;
    private static int[][] mat, conv_mat, temp; 
}