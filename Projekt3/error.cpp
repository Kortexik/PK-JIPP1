#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

void read_file_error(FILE* file) {
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku.\n");
        exit(1);
    }
}

void vector_alloc_fail(double* vector) {
    if (vector == NULL) {
        printf("Alokacja pamieci sie nie powiodla.\n");
        exit(1);
    }
}

void matrix_alloc_fail(double** matrix) {
    if (matrix == NULL) {
        printf("Alokacja pamieci sie nie powiodla.\n");
        exit(1);
    }
}

void matrix_item_alloc_fail(double* item) {
    if (item == NULL) {
        printf("Alokacja pamieci sie nie powiodla.\n");
        exit(1);
    }
}

int isSymetrical(double** matrix, int size){
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}