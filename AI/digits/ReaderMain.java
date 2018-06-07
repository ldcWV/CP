import java.io.*;

public class ReaderMain {
    public static void main(String[] args) throws IOException {
        MnistMatrix[] mnistMatrix = new MnistDataReader().readData("data/train-images.idx3-ubyte", "data/train-labels.idx1-ubyte");
        for(int i = 0; i < mnistMatrix.length; i++) {
            int cnt = tool.getCnt();
            PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(tool.getFileName(i+1030))));
            sample s = new sample(mnistMatrix[i].getLabel());
            for(int j = 0 ; j < 784; j++) {
                s.vals[j] = mnistMatrix[i].getValue(27-j%28, j/28);
            }
            out.println(s);
            out.close();
            if(i%100 == 0) System.out.println(i);
        }
    }

    private static void printMnistMatrix(final MnistMatrix matrix) {
        System.out.println("label: " + matrix.getLabel());
        for (int r = 0; r < matrix.getNumberOfRows(); r++ ) {
            for (int c = 0; c < matrix.getNumberOfColumns(); c++) {
                System.out.print(matrix.getValue(r, c) + " ");
            }
            System.out.println();
        }
    }
}
