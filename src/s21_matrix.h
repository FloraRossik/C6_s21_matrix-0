#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define OK	0
#define ERROR	1
#define CALC_ERROR 2

#define SUCCESS 1
#define FAILURE 0

#define EPS		1e-7

#define M A->matrix
#define L A.matrix


typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;


int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);
void s21_minor_creat(int rows, int columns, matrix_t *A, matrix_t *result);
double s21_minor_calc(matrix_t *A);

int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

void flip_rows(matrix_t *A, int row1, int row2);
void mult_sum_rows(matrix_t *A, int row1, int row2, double l);

int	s21_triangulate(matrix_t *A, matrix_t *result, int *coef);
int s21_is_inversible(matrix_t *A);

int s21_copy_matrix(matrix_t *src, matrix_t *dest);
int s21_check_matrix(matrix_t *A);



#endif  // SRC_S21_MATRIX_H_
