#include "s21_matrix.h"

void flip_rows(matrix_t *A, int row1, int row2);
void mult_sum_rows(matrix_t *A, int row1, int row2, double l); // row2 = row2 + row1 * l

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
			ratio = - result->matrix[j][i] / result->matrix[i][i];
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

void mult_sum_rows(matrix_t *A, int row1, int row2, double l) { // row2 = row2 + row1 * l
	if (!A || A->rows < row1 || A->rows < row2 || l == 0)
		return;
	for (int i = 0; i < A->columns; ++i) 
		A->matrix[row2][i] += A->matrix[row1][i] * l;
}
