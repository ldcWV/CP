public class pairvmat {
    public matrix[] F;
    public matrix[] S;
    public pairvmat(matrix[] A, matrix[] B) {
        this.F = A;
        this.S = B;
    }
    public pairvmat(pairvmat other) {
        this.F = new matrix[other.F.length];
        for(int i = 0; i < other.F.length; i++) this.F[i] = new matrix(other.F[i]);
        this.S = new matrix[other.S.length];
        for(int i = 0; i < other.S.length; i++) this.S[i] = new matrix(other.S[i]);
    }
}