public class pairmat {
    public matrix F;
    public matrix S;
    public pairmat(matrix A, matrix B) {
        this.F = A;
        this.S = B;
    }
    public pairmat(pairmat other) {
        this.F = new matrix(other.F);
        this.S = new matrix(other.S);
    }
}