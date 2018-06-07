public class matrix
{
    double[][] mat;
    int N, M;
    public matrix(int n, int m) { //identity
        this.N = n; this.M = m;
        mat = new double[N][M];
        for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) mat[i][j] = 0.0;
    }
    public matrix(matrix other) {
        this.N = other.N;
        this.M = other.M;
        this.mat = new double[N][M];
        for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) {
            this.mat[i][j] = other.mat[i][j];
        }
    }
    public matrix times(matrix other) {
        if(M != other.N) throw new RuntimeException("Dimensions don't match up");
        matrix ans = new matrix(N, other.M);
        for(int i = 0; i < N; i++) for(int j = 0; j < other.M; j++) {
            ans.mat[i][j] = 0;
            for(int k = 0; k < M; k++) ans.mat[i][j] += mat[i][k] * other.mat[k][j];
        }
        return ans;
    }
    public matrix times(double k) {
        matrix ans = new matrix(N, M);
        for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) ans.mat[i][j] = mat[i][j]*k;
        return ans;
    }
    public matrix plus(matrix other) {
        if(N != other.N || M != other.M) {
            throw new RuntimeException("Dimensions don't match up");
        }
        matrix ans = new matrix(N, M);
        for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) {
            ans.mat[i][j] = mat[i][j] + other.mat[i][j];
        }
        return ans;
    }
    public matrix transpose() {
        matrix ans = new matrix(M, N);
        for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) {
            ans.mat[j][i] = this.mat[i][j];
        }
        return ans;
    }
    public matrix hadamardmult(matrix other) {
        if(N != other.N || M != other.M) throw new RuntimeException("Dimensions don't match up");
        matrix ans = new matrix(N, M);
        for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) {
            ans.mat[i][j] = mat[i][j] * other.mat[i][j];
        }
        return ans;
    }
    public String toString() {
        String ans = "";
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if(j != 0) ans += " ";
                ans += Double.toString(mat[i][j]);
            }
        }
        return ans;
    }
}