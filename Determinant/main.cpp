#include <iostream>
#include <math.h>
using namespace std;

void PrintMatrix(float**, const int, const int);
void GaussMethod(float**, const int, bool);
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
	//cout << "\t¬ведите размерность второй матрицы в формате [столбец] пробел [строка]: "; cin >> rows_2 >> cols_2;
//	float** matrix_2 = new float* [rows_2];
//	FillRand(matrix_2, rows_2, cols_2);

//	Matrix_Mul(matrix_1, matrix_2, rows_1, cols_2, rows_2);
	//Matrix_Add_Sub(matrix_1, matrix_2, rows_1, cols_1, '+');
	//Matrix_Add_Sub(matrix_1, matrix_2, rows_1, cols_1, '-');
	//Transponation(matrix_1, rows_1, cols_1);
	//Transponation(matrix_2, rows_2, cols_2);
	GaussMethod(matrix_1, rows_1, true);
	//GaussMethod(matrix_2, rows_2, true);

	for (int i = 0; i < rows_1; i++)
	{
		delete[]matrix_1[i];
	}
//for (int i = 0; i < rows_2; i++)
	//{
//		delete[]matrix_2[i];
	//}
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
			cin >> matrix[i][j];
		//	matrix[i][j] = rand() % 10 * pow(-1, rand() % 2);
		}
	}
//	PrintMatrix(matrix, rows, cols);
}

void PrintMatrix(float** matrix, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		cout << "\n";
		for (int j = 0; j < cols; j++)
		{
			cout << "\t\t" << matrix[i][j];
		}
	}
	cout << "\n";
}

void Transponation(float** matrix, const int rows, const int cols)
{
	//cout << "Transponation: " << endl;
	float temp;
	for (int i = 0; i < rows-1; i++)
	{
		for (int j = i+1; j < cols; j++)
		{
			temp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = temp;
		}
	}
}

void GaussMethod(float** matrix, const int dim, bool inverse_matrix)
{
	int a = 0;
	float** unit_matrix = new float* [dim];
	float** temp_matrix = new float* [dim];
	for (int i = 0; i < dim; i++)
	{
		unit_matrix[i] = new float[dim] {0};
		unit_matrix[i][i] = 1;
		temp_matrix[i] = new float[dim];
	}
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			temp_matrix[i][j] = matrix[i][j];
		}
	}
	PrintMatrix(matrix, dim, dim);
	PrintMatrix(unit_matrix, dim, dim);
	for (int i = 0; i < dim - 1; i++)
	{
		float koeff = matrix[i][i];
		for (int j = 0; j < dim; j++)
		{
			matrix[i][j] = matrix[i][j] / koeff;
			unit_matrix[i][j] = unit_matrix[i][j] / koeff;
		}
		koeff = 1; 
		PrintMatrix(matrix, dim, dim);
		PrintMatrix(unit_matrix, dim, dim);
		cin >> a;
		for (int j = i + 1; j < dim; j++)
		{
			koeff = matrix[j][i] / matrix[i][i] * (-1);
			for (int k = 0; k < dim; k++)
			{
				matrix[j][k] = matrix[i][k] * koeff + matrix[j][k];
				(inverse_matrix) ? (unit_matrix[j][k] = unit_matrix[i][k] * koeff + unit_matrix[j][k]) : unit_matrix[j][k];
			}
			PrintMatrix(matrix, dim, dim);
			PrintMatrix(unit_matrix, dim, dim);
			cin >> a;
		}
	}
	for (int j = 0; j < dim; j++)
	{
		unit_matrix[dim-1][j] = unit_matrix[dim-1][j] / matrix[dim-1][dim-1];
	}		
	matrix[dim - 1][dim - 1] = 1;
	PrintMatrix(matrix, dim, dim);
	PrintMatrix(unit_matrix, dim, dim);
	cin >> a;
	cout << "\nBack way"<<endl;
	for (int i = dim-1; i > 0; i--)
	{
		float koeff = 1;
		for (int j = i - 1; j >= 0; j--)
		{
			koeff = matrix[j][i] / matrix[i][i] * (-1);
			for (int k = dim-1; k >= 0; k--)
			{
				matrix[j][k] = matrix[i][k] * koeff + matrix[j][k];
				(inverse_matrix) ? (unit_matrix[j][k] = unit_matrix[i][k] * koeff + unit_matrix[j][k]) : unit_matrix[j][k];
			}
			PrintMatrix(matrix, dim, dim);
			PrintMatrix(unit_matrix, dim, dim);
			cin >> a;
		}
	}
	cout << "\n\nAfter backway" << endl;
	PrintMatrix(matrix, dim, dim);
	//PrintMatrix(unit_matrix, dim, dim);
	//for (int i = 0; i < dim; i++)
	//{
	//	for (int j = 0; j < dim; j++)
	//	{
	//		unit_matrix[i][j] = unit_matrix[i][j] / matrix[i][i];
	//	}
	//	matrix[i][i] = 1;
	//}
	//cout << "\n\nAter cutting diagonal" << endl;
	//PrintMatrix(matrix, dim, dim);
	//PrintMatrix(unit_matrix, dim, dim);
	cout << "\n\n temp is:" << endl;
	PrintMatrix(temp_matrix, dim, dim);
	cout << "\n\n MUL" << endl;
	Matrix_Mul(unit_matrix, temp_matrix, dim, dim, dim);

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
