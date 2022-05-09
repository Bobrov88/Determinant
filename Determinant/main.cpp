#include <iostream>
#include <math.h>
using namespace std;

void PrintMatrix(float**, const int, const int);
float GaussMethod(float**, const int);
void Matrix_Mul(float**, float**, const int, const int, const int);
void Matrix_Add_Sub(float**, float**, const int, const int, const char);
void FillRand(float**, const int, const int);
void Transponation(float**, const int, const int);

int main()
{
	setlocale(LC_ALL, "");
	int rows_1, cols_1, rows_2, cols_2;
	cout << "\t¬ведите размерность первой матрицы в формате [столбец] пробел [строка]: "; cin >> rows_1 >> cols_1;
	float** matrix_1 = new float* [rows_1];
	FillRand(matrix_1, rows_1, cols_1);
	cout << "\t¬ведите размерность второй матрицы в формате [столбец] пробел [строка]: "; cin >> rows_2 >> cols_2;
	float** matrix_2 = new float* [rows_2];
	FillRand(matrix_2, rows_2, cols_2);

	Matrix_Mul(matrix_1, matrix_2, rows_1, cols_2, rows_2);
	Matrix_Add_Sub(matrix_1, matrix_2, rows_1, cols_1, '+');
	Matrix_Add_Sub(matrix_1, matrix_2, rows_1, cols_1, '-');
	Transponation(matrix_1, rows_1, cols_1);
	Transponation(matrix_2, rows_2, cols_2);
	cout << "\n\n" << GaussMethod(matrix_1, rows_1);
	cout << "\n\n" << GaussMethod(matrix_2, rows_2);

	for (int i = 0; i < rows_1; i++)
	{
		delete[]matrix_1[i];
	}
	for (int i = 0; i < rows_2; i++)
	{
		delete[]matrix_2[i];
	}
	return 0;
}

void FillRand(float** matrix, const int rows, const int cols)
{
	cout << "Fill matrix: " << endl;
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new float[rows];
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = rand() % 10 * pow(-1, rand() % 2);
		}
	}
	PrintMatrix(matrix, rows, cols);
}

void PrintMatrix(float** matrix, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		cout << "\n";
		for (int j = 0; j < cols; j++)
		{
			cout << "\t" << matrix[i][j];
		}
	}
	cout << "\n";
}

void Transponation(float** matrix, const int rows, const int cols)
{
	cout << "Transponation: " << endl;
	float** transponed = new float* [cols];
	for (int i = 0; i < cols; i++)
	{
		transponed[i] = new float[rows] {0};
	}
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			transponed[j][i] = matrix[j][i];
		}
	}
	PrintMatrix(transponed, cols, rows);
}

float GaussMethod(float** matrix, const int dim)
{
	cout << "Determinant: " << endl;
	float koeff = 1;
	float determinant = 1;
		for (int i = 0; i < dim - 1; i++)
		{
			determinant *= matrix[i][i];
			for (int j = i + 1; j < dim; j++)
			{
				koeff = matrix[j][i] / matrix[i][i] * (-1);
				for (int k = i; k < dim; k++)
				{
					matrix[j][k] = matrix[i][k] * koeff + matrix[j][k];
				}
			}
		}
		return determinant * matrix[dim - 1][dim - 1];
}

void Matrix_Mul(float** matrix1, float** matrix2, const int rows, const int cols, const int rows_cols)
{
	cout << "Multiplication: " << endl;
	float** result = new float* [rows];
	for (int i = 0; i < rows; i++)
	{
		result[i] = new float[cols] {0};
		for (int j = 0; j < cols; j++)
		{
			for (int k = 0; k < rows_cols; k++)
			{
				result[i][j] = result[i][j] + matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	PrintMatrix(result, rows, cols);
}

void Matrix_Add_Sub(float** matrix1, float** matrix2, const int rows, const int cols, const char op)
{
	cout << "Add_Sub: " << endl;
	float** result = new float* [rows];
	for (int i = 0; i < rows; i++)
	{
		result[i] = new float[cols] {0};
		for (int j = 0; j < cols; j++)
		{
			result[i][j] = (op == '+') ? (matrix1[i][j] + matrix2[i][j]) : (matrix1[i][j] - matrix2[i][j]);
		}
	}
	PrintMatrix(result, rows, cols);
}
