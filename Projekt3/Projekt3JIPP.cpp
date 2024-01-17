#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#pragma warning (disable:4996)

// Util_1.cpp
extern double** allocate_matrix(int rows, int cols);
extern void free_matrix(double** matrix, int rows);
extern void read_matrix(double** matrix, int rows, int cols, FILE* file);
extern void read_vector(double* vector, int size, FILE* file);
extern void print_matrix(double** matrix, int rows, int cols);
extern void print_vector(double* vector, int size);
// error.cpp
extern void read_file_error(FILE* file);
extern void vector_alloc_fail(double* vector);

// Funkcja rozwiązująca system równań liniowych metodą Banachiewicza

void choleskyDecomposition(double** A, double* V, int size) {
    double** L = (double**)malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        L[i] = (double*)calloc(size, sizeof(double));
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0.0;
            if (j == i) {
                for (int k = 0; k < j; k++) {
                    sum += L[j][k] * L[j][k];
                }
                L[j][j] = sqrt(A[j][j] - sum);
                if (isnan(L[j][j])) {
                    printf("Macierz nie jest dodatnio określona.\n");
                    return;
                }
            }
            else {
                for (int k = 0; k < j; k++) {
                    sum += L[i][k] * L[j][k];
                }
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }

    double* y = (double*)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = (V[i] - sum) / L[i][i];
    }

    double* x = (double*)malloc(size * sizeof(double));
    for (int i = size - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < size; j++) {
            sum += L[j][i] * x[j];
        }
        x[i] = (y[i] - sum) / L[i][i];
    }

    printf("Rozwiazania ukladu rownan Ax = V:\n");
    for (int i = 0; i < size; i++) {
        printf("x[%d] = %f\n", i, x[i]);
    }

    // Cleanup
    free(y);
    free(x);
    for (int i = 0; i < size; i++) {
        free(L[i]);
    }
    free(L);
}

int main() {
    FILE* input_file = fopen("input.txt", "r");
    FILE* output_file = fopen("output.txt", "w");

    read_file_error(input_file);
    read_file_error(output_file);


    int size;
    if (fscanf(input_file, "%d", &size) != 1) {
        printf("Blad odczhytu");
        exit(1);
    }
    
    double** matrix = allocate_matrix(size, size);

    double* vector = (double*)malloc(size * sizeof(double));
    double* solution = (double*)malloc(size * sizeof(double));
    vector_alloc_fail(vector);

    read_matrix(matrix, size, size, input_file);

    read_vector(vector, size, input_file);

    printf("Macierz A:\n");
    print_matrix(matrix, size, size);
    printf("Vector b:\n");
    print_vector(vector, size);

    choleskyDecomposition(matrix, vector, size);

    fclose(input_file);
    fclose(output_file);
    free_matrix(matrix, size);
    free(vector);

    return 0;
}
