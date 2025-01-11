/*
1. 对称矩阵只存储主对角线的下三角元素
a[i][j] = a[j][i] = S[1 + 2 + ... + i + j] = S[i(i+1)/2 + j]
*/
int getSymmetricMatrix(int **S, int i, int j) {
    // **以a[0][0]为起点**，行主序
    return S[i * (i + 1) / 2 + j];
}

/*
2. 三角矩阵
*/
int getLowerTriangleMatrix(int **T, int i, int j) {
    if (i < j) { // 下三角矩阵，上三角元素为0或常数C
        return 0;
    } else {
        return T[i * (i + 1) / 2 + j];
    }
}

int getUpperTriangleMatrix(int **T, int i, int j) {
    if (i > j) { // 上三角矩阵，下三角元素为0或常数C
        return 0;
    } else {
        // n + (n - 1) + (n - 2) + ... + (n - i + 1) + **(j - i)**
        // (2 * n - i + 1) * i / 2 + j - i
        // n * i - (i * (i - 1) / 2) + j - i
        // n * i - (i * (i + 1) / 2) + j
        return T[n * i - (i * (i + 1) / 2) + j];
    }
}

/*  
3. 三对角矩阵
*/
int getTridiagonalMatrix(int **D, int i, int j) {
    if (i == j + 1 || i == j - 1 || i == j) {
        // D[3i - 1], D[3i + 1], D[3i] 的一致化处理
        return D[i * 2 + j];
    } else {
        return 0;
    }
}

/*
4. 稀疏矩阵
*/
int const MAX_SIZE = 2<<5;
typedef struct {
    int row, col;
    int value;
} Triple;
typedef struct {
    Triple data[MAX_SIZE];
    int rows, cols, nums; // 行数，列数，非零元素个数
} TSMatrix;

void TransformMatrix(TSMatrix *A, TSMatrix *B) {
    int cnt_col[MAX_SIZE], index_pos[MAX_SIZE];
    B->rows = A->cols;
    B->cols = A->rows;
    B->nums = A->nums;
    if (B->nums == 0) {
        return;
    }
    for (int i = 0; i < A->cols; i++) { // O(n)
        cnt_col[i] = 0;
    }
    for (int i = 0; i < A->nums; i++) { // O(t)
        cnt_col[A->data[i].col]++;
    } // eg. 2, 2, 1, 0, 1
    index_pos[0] = 0;
    for (int i = 1; i < A->cols; i++) { // O(n)
        index_pos[i] = index_pos[i - 1] + cnt_col[i - 1];
    } // eg. 0, 2, 4, 5, 5
    for (int i = 0; i < A->nums; i++) { // O(t)
        int col = A->data[i].col;
        int index = index_pos[col];
        B->data[index].row = A->data[i].col;
        B->data[index].col = A->data[i].row;
        B->data[index].value = A->data[i].value;
        index_pos[col]++;
    }
}
