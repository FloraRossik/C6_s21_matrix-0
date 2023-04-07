#include "s21_matrix.h"

int s21_copy_matrix(matrix_t *src, matrix_t *dest) {
  if (!src || !dest)
    return ERROR;
  if (src->rows != dest->rows || src->columns != dest->columns)
    return ERROR;

  for (int i = 0; i < src->rows; ++i) {
    memcpy(dest->matrix[i], src->matrix[i], src->columns * sizeof(double));
  }
  return OK;
}

int s21_is_inversible(matrix_t *A) {
  if (!A || A->rows != A->columns || A->rows <= 0)
    return FAILURE;
  double d;
  s21_determinant(A, &d);
  return fabs(d) >= EPS;
}

int s21_check_matrix(matrix_t *A) {
  int error = 0;
  if (A->matrix != NULL && A->columns >= 1 && A->rows >= 1 && A != NULL)
    error = 1;
  return error;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {

  if (rows <= 0 || columns <= 0 || !result)
    return ERROR;

  result->matrix = (double **)malloc(rows * sizeof(double *));
  if (result->matrix == NULL)
    return ERROR;
  for (int i = 0; i < rows; ++i) {
    result->matrix[i] = (double *)malloc(columns * sizeof(double));
    if (result->matrix[i] == NULL)
      return ERROR;
  }

  result->rows = rows;
  result->columns = columns;

  return OK;
}

#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (!A || !A->matrix || A->rows <= 0 || A->columns <= 0)
    return;

  for (int i = 0; i < A->rows; ++i)
    free(A->matrix[i]);
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!A || !B || A->columns <= 0 || A->rows <= 0)
    return FAILURE;
  if (A->rows != B->rows || A->columns != B->columns)
    return FAILURE;

  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS)
        return FAILURE;
    }
  }
  return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B || !result)
    return ERROR;
  if (A->rows != B->rows || A->columns != B->columns)
    return CALC_ERROR;

  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return ERROR;

  for (int i = 0; i < A->rows; ++i)
    for (int j = 0; j < A->columns; ++j)
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];

  return SUCCESS;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B || !result)
    return ERROR;
  if (A->rows != B->rows || A->columns != B->columns)
    return CALC_ERROR;

  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return ERROR;

  for (int i = 0; i < A->rows; ++i)
    for (int j = 0; j < A->columns; ++j)
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];

  return SUCCESS;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!A || !result)
    return ERROR;

  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return ERROR;

  for (int i = 0; i < A->rows; ++i)
    for (int j = 0; j < A->columns; ++j)
      result->matrix[i][j] = A->matrix[i][j] * number;

  return SUCCESS;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B || !result)
    return ERROR;
  if (A->columns != B->rows)
    return CALC_ERROR;

  if (s21_create_matrix(A->rows, B->columns, result) != OK)
    return ERROR;

  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < B->columns; ++j) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; ++k)
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
    }
  }

  return OK;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!A || !result)
    return ERROR;

  if (s21_create_matrix(A->columns, A->rows, result) != OK)
    return ERROR;

  for (int i = 0; i < A->rows; ++i)
    for (int j = 0; j < A->columns; ++j)
      result->matrix[j][i] = A->matrix[i][j];
  return OK;
}

void s21_minor_creat(int rows, int columns, matrix_t *A, matrix_t *result) {
  int error = OK;
  if (s21_check_matrix(A)) {
    error = s21_create_matrix(A->rows - 1, A->columns - 1, result);
    int a = 0, b = 0;
    if (error == OK) {
      for (int m = 0; m < A->rows; m++)
        for (int n = 0; n < A->columns; n++)
          if (m != rows && n != columns) {
            result->matrix[a][b++] = M[m][n];
            if (b == result->columns)
              a++, b = 0;
          }
    }
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (s21_check_matrix(A)) {
    if (A->columns == A->rows) {
      error = s21_create_matrix(A->rows, A->rows, result);
      if (A->columns == 1) {
        result->matrix[0][0] = M[0][0];
      } else {
        if (error == OK) {
          for (int m = 0; m < result->rows; m++)
            for (int n = 0; n < result->columns; n++) {
              matrix_t tmp;
              s21_minor_creat(m, n, A, &tmp);
              result->matrix[m][n] = s21_minor_calc(&tmp) * pow(-1, m + n);
              s21_remove_matrix(&tmp);
            }
        }
      }
    } else {
      error = CALC_ERROR;
    }
  } else {
    error = ERROR;
  }
  return error;
}

int s21_determinant(matrix_t *A, double *result) {
  if (!A || !result)
    return ERROR;
  matrix_t tmp;
  int negative;
  s21_triangulate(A, &tmp, &negative);
  *result = 1;
  for (int i = 0; i < A->rows; ++i)
    *result *= tmp.matrix[i][i];
  *result *= (double)negative;
  s21_remove_matrix(&tmp);
  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (!s21_check_matrix(A)) {
    error = ERROR;
  } else {
    if (A->rows != A->columns) {
      error = CALC_ERROR;
    } else {
      double determinate = 0;
      error = s21_determinant(A, &determinate);
      if (determinate != 0) {
        if (!error) {
          matrix_t tmp_complements;
          matrix_t tmp_complements_trans;
          error = s21_calc_complements(A, &tmp_complements);
          error = s21_transpose(&tmp_complements, &tmp_complements_trans);
          error =
              s21_mult_number(&tmp_complements_trans, 1 / determinate, result);
          s21_remove_matrix(&tmp_complements);
          s21_remove_matrix(&tmp_complements_trans);
        }
      } else {
        error = CALC_ERROR;
      }
    }
  }
  return error;
}

int s21_triangulate(matrix_t *A, matrix_t *result, int *coef) {
  if (!A || !result)
    return ERROR;
  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return ERROR;

  s21_copy_matrix(A, result);

  *coef = 1;
  double ratio = 1;
  for (int i = 0; i < result->rows; ++i) {
    int j = i;
    for (j = i; j < result->rows; j++) {
      if (result->matrix[j][i] != 0)
        break;
    }
    if (j == result->rows - 1 && result->matrix[j][i] == 0)
      continue;
    else if (i != j) {
      flip_rows(result, i, j);
      *coef *= -1;
    }
    for (int j = i + 1; j < result->rows; ++j) {
      if (result->matrix[j][i] == 0)
        continue;
      ratio = -result->matrix[j][i] / result->matrix[i][i];
      mult_sum_rows(result, i, j, ratio);
    }
  }
  return OK;
}

void flip_rows(matrix_t *A, int row1, int row2) {
  if (!A || row1 <= A->rows || row2 <= A->rows)
    return;
  double tmp;
  for (int i = 0; i < A->columns; ++i) {
    tmp = A->matrix[row1][i];
    A->matrix[row1][i] = A->matrix[row2][i];
    A->matrix[row2][i] = tmp;
  }
}

void mult_sum_rows(matrix_t *A, int row1, int row2,
                   double l) { // row2 = row2 + row1 * l
  if (!A || A->rows < row1 || A->rows < row2 || l == 0)
    return;
  for (int i = 0; i < A->columns; ++i)
    A->matrix[row2][i] += A->matrix[row1][i] * l;
}