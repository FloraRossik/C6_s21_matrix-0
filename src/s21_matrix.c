#include "s21_matrix.h"

typedef struct matrix_struct2 {
  double **matrix;
  int rows;
  int columns;
} matrix_t2;

// void matrix_1(int n, int m) {
//   int new_buff[50][50];
//   int i, j, number;
//   char str[12];

//   i = 0;
//   while(i < n) {
//     j = 0;
//     while (j < m) {
//       scanf("%12s", str);
//       sscanf(str, "%d", &number);
//       new_buff[i][j] = number;
//       j++;
//     }
//     i++;
//   }
//   for(int i = 0; i < n - 1; i++) {
//     for (int j = 0; j < m; j++) {
//       printf("%d", new_buff[i][j]);
//     }
//     printf("\n");
//   }
//   for (int j = 0; j < m; j++) {
//     printf("%d", new_buff[n -1][j]);
//   }
// }

int s21_check_matrix(matrix_t *A) {
    int error = 0;
    if (A->matrix != NULL && A->columns >= 1 && A->rows >= 1 && A != NULL)
        error = 1;
    return error;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {

    int error = 0;

    if (rows <= 0 || columns <= 0) 
      error = 1;

    result->rows = rows, result->columns = columns;
    
    result->matrix = (double **)malloc(rows * sizeof(double *));

    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
    }
    if (error == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++){
              result->matrix[i][j] = 0;
            }
        }
    }
    return error;
  }

  void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
      for (int i = 0; i < A->rows; i++) {
        free(A->matrix[i]);
      }
      free(A->matrix);
    }
    A->rows = 0;
    A->columns = 0;
  }
  
  int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {

    int error = 0;

    if (s21_check_matrix(A) && s21_check_matrix(B)) {
        if (A->rows == B->rows && A->columns == B->columns) 
        {
            error = s21_create_matrix(A->rows, A->columns, result);
            if (error == 0) {
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < A->columns; j++) {
                      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
                    }
                }
            }
        } 
        else
            error = 1;
    } else {
        error = 1;
    }
    return error;
  }

  int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {

    int error = 0;

    if (s21_check_matrix(A) && s21_check_matrix(B)) {
        if (A->rows == B->rows && A->columns == B->columns) 
        {
            error = s21_create_matrix(A->rows, A->columns, result);
            if (!error) {
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < A->columns; j++) {
                        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
                    }
                }
            }
        } 
        else
            error = 1;
    } else {
        error = 1;
    }
    return error;
  }

  int s21_mult_number(matrix_t *A, double number, matrix_t *result) {

    int error = 0;

    if (s21_check_matrix(A)) {
      error = s21_create_matrix(A->rows, A->columns, result);
      if (!error) {
        for (int i = 0; i < A->rows, i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = number * A->matrix[i][j];
          }
        }
      }
    }
    return error;
  }

  int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {

    int error = 0;

    if (s21_check_matrix(A) && s21_check_matrix(B)) {
        if (A->rows == B->rows && A->columns == B->columns) 
        {
            error = s21_create_matrix(A->rows, A->columns, result);
            if (error == 0) {
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < A->columns; j++) {
                        result->matrix[i][j] += A->matrix[i][j] * B->matrix[i][j];
                    }
                }
            }
        } 
        else
            error = 1;
    } else {
        error = 1;
    }
    return error;
  }

int main() {
  
  matrix_t matrix;

  int rows = 3;
  int columns = 3;

  // int **new_buff;

  s21_create_matrix(rows, columns, &matrix);
  //s21_sub_matrix(&matrix, &matrix, &matrix);
  s21_remove_matrix(&matrix);

  return 0;
}