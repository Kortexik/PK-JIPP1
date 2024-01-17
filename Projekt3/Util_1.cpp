#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996)
extern isSymetrical(double** matrix, int size);
extern void matrix_alloc_fail(double** matrix);
extern void matrix_item_alloc_fail(double* item);

// Function to allocate memory for a matrix
double** allocate_matrix(int rows, int cols) {
    double** matrix = (double**)malloc(rows * sizeof(double*));
    matrix_alloc_fail(matrix);
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
        matrix_item_alloc_fail(matrix[i]);
    }
    return matrix;
}

// Function to free memory allocated for a matrix
void free_matrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to read a matrix from a text file
void read_matrix(double** matrix, int rows, int cols, FILE* file) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (fscanf(file, "%lf", &matrix[i][j]) != 1) {
                printf("Blad odczytu danych");
                exit(1);
            }
        }
    }
    if (!isSymetrical(matrix, rows)) {
       printf("Macierz nie jest symetryczma.");
       exit(1);
        }
    
}

   

// Function to read a vector from a text file
void read_vector(double* vector, int size, FILE * file){
    for (int i = 0; i < size; i++) {
        if (fscanf(file, "%lf", &vector[i]) != 1) {
            printf("Blad odczytu danych");
            exit(1);
        }
    }
}

// Function to print a matrix
void print_matrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to print a vector
void print_vector(double* vector, int size) {
    for (int i = 0; i < size; i++) {
        printf("%lf ", vector[i]);
    }
    printf("\n");
}

