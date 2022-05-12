#include <iostream>
#include <math.h>
#include <conio.h>
using namespace std;

#define ROWS_COUNT cout<<"\t Количество строк -> "
#define COLS_COUNT cout<<"\t Количество столбцов -> "
#define MATRIX "\n\t Матрица "
#define RANDOMFILLED " заполнена случайными числами"
#define ADD_SUB_CONDITIONS_FAILED cout<<"\t Размерность матриц не одинаковая!\n\t Сложение и вычитание не выполнено\n"
#define DETERMINANT_CONDITIONS_FAILED cout<<"\t Для нахождения определителя и обратной матрицы\n\t количество строк и столбцов должны быть одинаково\n"
#define MULT_CONDITIONS_FAILED cout<<"\t Количество столбцов матрицы А должны быть равно количеству строк матрицы В!"

void PrintMatrix(float**, const int, const int);
void GaussMethod(float**, float**, const int);
void Matrix_Mul(float**, float**, float**, const int, const int, const int);
void Matrix_Add_Sub(float**, float**, float**, const int, const int, const char);
void FillRand(float**, const int, const int);
void Delete(float**, const int);

int main()
{
	setlocale(LC_ALL, "");
	int rows_1, cols_1, rows_2, cols_2;
	float** matrix_A = nullptr, ** matrix_B = nullptr;
	cout << MATRIX << "A:\n";
	ROWS_COUNT; cin >> rows_1;
	COLS_COUNT; cin >> cols_1;
	cout << MATRIX << "B:\n";
	ROWS_COUNT; cin >> rows_2;
	COLS_COUNT; cin >> cols_2;
	matrix_A = new float* [rows_1];
	matrix_B = new float* [rows_2];

	for (int i = 0; i < rows_1; i++)
	{
		matrix_A[i] = new float[rows_1];
	}
	FillRand(matrix_A, rows_1, cols_1);

	for (int i = 0; i < rows_2; i++)
	{
		matrix_B[i] = new float[rows_2];
	}
	FillRand(matrix_B, rows_2, cols_2);

	cout << MATRIX << "A" << RANDOMFILLED << ": ";
	PrintMatrix(matrix_A, rows_1, cols_1);
	cout << MATRIX << "B" << RANDOMFILLED << ": ";
	PrintMatrix(matrix_B, rows_2, cols_2);
	/* -------------Сложение и вычитание------------------ */
	if ((rows_1 == rows_2) && (cols_1 == cols_2))
	{
		float** result = new float* [rows_1];
		for (int i = 0; i < rows_1; i++)
		{
			result[i] = new float[cols_1] {0};
		}
		Matrix_Add_Sub(matrix_A, matrix_B, result, rows_1, cols_1, '+');
		Matrix_Add_Sub(matrix_A, matrix_B, result, rows_1, cols_1, '-');
		Delete(result, rows_1);
	}
	else ADD_SUB_CONDITIONS_FAILED;
	/*------------------- Умножение ----------------------*/
	if (cols_1 == rows_2)
	{
		float** result = new float* [rows_1];
		for (int i = 0; i < rows_1; i++)
		{
			result[i] = new float[cols_2] {0};
		}
		Matrix_Mul(matrix_A, matrix_B, result, rows_1, cols_2, rows_2);
		Delete(result, rows_1);
	}
	else MULT_CONDITIONS_FAILED;;
	/*----- Определитель одной из матриц и обратная матрица ----*/
	if (rows_1 == cols_1)
	{
		float** unit_matrix = new float* [rows_1];
		for (int i = 0; i < rows_1; i++)
		{
			unit_matrix[i] = new float[cols_1] {0};
			unit_matrix[i][i] = 1;
		}
		GaussMethod(matrix_A, unit_matrix, rows_1);
		Delete(unit_matrix, rows_1);
	}
	else DETERMINANT_CONDITIONS_FAILED;
	
	Delete(matrix_A, rows_1);
	Delete(matrix_B, rows_2);
	return 0;
}


void FillRand(float** matrix, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = (float)(rand() % 10 * pow(-1, rand() % 2));
		}
	}
}

void PrintMatrix(float** matrix, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		cout << "\n ";
		for (int j = 0; j < cols; j++)
		{
			cout << "\t" << matrix[i][j];
		}
	}
	cout << "\n";
}

void GaussMethod(float** matrix, float** unit_matrix, const int dim)
{
	float DETERMINANT = 1, koeff;
	for (int i = 0; i < dim - 1; i++) // верхняя треугольная матрица
	{
		koeff = matrix[i][i];
		DETERMINANT *= koeff;
		for (int j = 0; j < dim; j++)
		{
			matrix[i][j] = matrix[i][j] / koeff;
			unit_matrix[i][j] = unit_matrix[i][j] / koeff;
		}
		for (int j = i + 1; j < dim; j++)
		{
			koeff = matrix[j][i] / matrix[i][i] * (-1);
			for (int k = 0; k < dim; k++)
			{
				matrix[j][k] = matrix[i][k] * koeff + matrix[j][k];
				unit_matrix[j][k] = unit_matrix[i][k] * koeff + unit_matrix[j][k];
			}
		}
	}

	DETERMINANT *= matrix[dim - 1][dim - 1];
	cout << "\n\t Определитель матрицы А = " << DETERMINANT << endl;
	if (DETERMINANT == 0)
	{
		cout << "\t Так как определитель равен 0, обратной матрицы не существует" << endl;
	}
	else
	{
		for (int j = 0; j < dim; j++) // единицы на главной диагонали
		{
			unit_matrix[dim - 1][j] = unit_matrix[dim - 1][j] / matrix[dim - 1][dim - 1];
		}
		matrix[dim - 1][dim - 1] = 1;
		for (int i = dim - 1; i > 0; i--) // нижняя треугольная матрица
		{
			float koeff = 1;
			for (int j = i - 1; j >= 0; j--)
			{
				koeff = matrix[j][i] / matrix[i][i] * (-1);
				for (int k = dim - 1; k >= 0; k--)
				{
					matrix[j][k] = matrix[i][k] * koeff + matrix[j][k];
					unit_matrix[j][k] = unit_matrix[i][k] * koeff + unit_matrix[j][k];
				}
			}
		}
		cout << "\n\t Обратная матрица к матрице А = ";
		PrintMatrix(unit_matrix, dim, dim);
	}
}

void Matrix_Mul(float** matrix1, float** matrix2, float** result, const int rows, const int cols, const int rows_cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			for (int k = 0; k < rows_cols; k++)
			{
				result[i][j] = result[i][j] + matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	cout << "\n\t A x B = ";
	PrintMatrix(result, rows, cols);
}

void Matrix_Add_Sub(float** matrix1, float** matrix2, float **result, const int rows, const int cols, const char op)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			result[i][j] = (op == '+') ? (matrix1[i][j] + matrix2[i][j]) : (matrix1[i][j] - matrix2[i][j]);
		}
	}
	cout << "\n\t A "<<op<<" B = ";
	PrintMatrix(result, rows, cols);
}

void Delete(float **matrix, const int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[]matrix[i];
	}
}


