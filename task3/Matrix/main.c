#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;  // Matrix content
    int rows;    // Number of rows
    int cols;    // Number of columns
} Matrix;

// Function to create a new matrix
Matrix *createMatrix(int rows, int cols) {
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    if (matrix == NULL) {
        printf("Failed to allocate memory for the matrix\n");
        exit(EXIT_FAILURE);
    }

    matrix->rows = rows;
    matrix->cols = cols;

    // Allocate memory for matrix elements
    matrix->data = (int **)malloc(rows * sizeof(int *));
    if (matrix->data == NULL) {
        printf("Failed to allocate memory for matrix elements\n");
        free(matrix);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (int *)malloc(cols * sizeof(int));
        if (matrix->data[i] == NULL) {
            printf("Failed to allocate memory for matrix elements\n");
            free(matrix->data);
            free(matrix);
            exit(EXIT_FAILURE);
        }
    }

    return matrix;
}

// Function to free memory and delete a matrix
void destroyMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

// Function to resize a matrix while preserving its content
Matrix *resizeMatrix(Matrix *matrix, int newRows, int newCols) {
    Matrix *newMatrix = createMatrix(newRows, newCols);
    int minRows = (matrix->rows < newRows) ? matrix->rows : newRows;
    int minCols = (matrix->cols < newCols) ? matrix->cols : newCols;

    for (int i = 0; i < minRows; i++) {
        for (int j = 0; j < minCols; j++) {
            newMatrix->data[i][j] = matrix->data[i][j];
        }
    }

    return newMatrix;
}

// Function to get the number of rows in a matrix
int numRows(Matrix *matrix) {
    return matrix->rows;
}

// Function to get the number of columns in a matrix
int numCols(Matrix *matrix) {
    return matrix->cols;
}

// Function to set the value of an element in a matrix
void setElement(Matrix *matrix, int row, int col, int value) {
    if (row >= 0 && row < matrix->rows && col >= 0 && col < matrix->cols) {
        matrix->data[row][col] = value;
    } else {
        printf("Invalid index\n");
    }
}

// Function to get the value of an element in a matrix
int getElement(Matrix *matrix, int row, int col) {
    if (row >= 0 && row < matrix->rows && col >= 0 && col < matrix->cols) {
        return matrix->data[row][col];
    } else {
        printf("Invalid index\n");
        return 0;
    }
}

// Function to print a matrix
void printMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%d\t", matrix->data[i][j]);
        }
        printf("\n");
    }
}

// Function to save a matrix to a file
void saveMatrixToFile(Matrix *matrix, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open the file for writing\n");
        return;
    }

    fprintf(file, "%d %d\n", matrix->rows, matrix->cols);

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            fprintf(file, "%d ", matrix->data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Function to load a matrix from a file
Matrix *loadMatrixFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file for reading\n");
        return NULL;
    }

    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);

    Matrix *matrix = createMatrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &matrix->data[i][j]);
        }
    }

    fclose(file);
    return matrix;
}

// Function to add matrices
Matrix *addMatrix(Matrix *matrix1, Matrix *matrix2) {
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols) {
        printf("Matrices have different dimensions, cannot perform addition.\n");
        return NULL;
    }

    Matrix *result = createMatrix(matrix1->rows, matrix1->cols);

    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix1->cols; j++) {
            result->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
        }
    }

    return result;
}

// Function to subtract matrices
Matrix *subtractMatrix(Matrix *matrix1, Matrix *matrix2) {
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols) {
        printf("Matrices have different dimensions, cannot perform subtraction.\n");
        return NULL;
    }

    Matrix *result = createMatrix(matrix1->rows, matrix1->cols);

    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix1->cols; j++) {
            result->data[i][j] = matrix1->data[i][j] - matrix2->data[i][j];
        }
    }

    return result;
}

// Function to multiply a matrix by a scalar
Matrix *multiplyMatrixByScalar(Matrix *matrix, int scalar) {
    Matrix *result = createMatrix(matrix->rows, matrix->cols);

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            result->data[i][j] = matrix->data[i][j] * scalar;
        }
    }

    return result;
}

// Function to multiply two matrices
Matrix *multiplyMatrix(Matrix *matrix1, Matrix *matrix2) {
    if (matrix1->cols != matrix2->rows) {
        printf("Number of columns in the first matrix does not match the number of rows in the second matrix, cannot perform multiplication.\n");
        return NULL;
    }

    Matrix *result = createMatrix(matrix1->rows, matrix2->cols);

    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix2->cols; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < matrix1->cols; k++) {
                result->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
            }
        }
    }

    return result;
}

int main() {
    Matrix *matrix1 = createMatrix(3, 3);
    Matrix *matrix2 = createMatrix(3, 3);

    // Fill matrices with some values
    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix1->cols; j++) {
            matrix1->data[i][j] = i + j;
            matrix2->data[i][j] = i - j;
        }
    }

    printf("Matrix 1:\n");
    printMatrix(matrix1);
    printf("\nMatrix 2:\n");
    printMatrix(matrix2);

    Matrix *resultAdd = addMatrix(matrix1, matrix2);
    if (resultAdd != NULL) {
        printf("\nResult of addition:\n");
        printMatrix(resultAdd);
        destroyMatrix(resultAdd);
    }

    Matrix *resultSubtract = subtractMatrix(matrix1, matrix2);
    if (resultSubtract != NULL) {
        printf("\nResult of subtraction:\n");
        printMatrix(resultSubtract);
        destroyMatrix(resultSubtract);
    }

    Matrix *resultMultiplyScalar = multiplyMatrixByScalar(matrix1, 2);
    if (resultMultiplyScalar != NULL) {
        printf("\nResult of multiplication by scalar (2):\n");
        printMatrix(resultMultiplyScalar);
        destroyMatrix(resultMultiplyScalar);
    }

    Matrix *matrix3 = createMatrix(3, 2);
    Matrix *matrix4 = createMatrix(2, 3);

    for (int i = 0; i < matrix3->rows; i++) {
        for (int j = 0; j < matrix3->cols; j++) {
            matrix3->data[i][j] = i + j;
            matrix4->data[j][i] = i - j;
        }
    }

    printf("\nMatrix 3:\n");
    printMatrix(matrix3);
    printf("\nMatrix 4:\n");
    printMatrix(matrix4);

    Matrix *resultMultiply = multiplyMatrix(matrix3, matrix4);
    if (resultMultiply != NULL) {
        printf("\nResult of matrix multiplication between matrix 3 and 4:\n");
        printMatrix(resultMultiply);
        destroyMatrix(resultMultiply);
    }

    saveMatrixToFile(matrix1, "task3/Matrix/example.txt");
    Matrix *loadedMatrix = loadMatrixFromFile("task3/Matrix/example.txt");
    if (loadedMatrix != NULL) {
        printf("\nLoaded matrix from file:\n");
        printMatrix(loadedMatrix);
        destroyMatrix(loadedMatrix);
    }

    destroyMatrix(matrix1);
    destroyMatrix(matrix2);
    destroyMatrix(matrix3);
    destroyMatrix(matrix4);

    return 0;
}
