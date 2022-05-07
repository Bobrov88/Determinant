#include <iostream>
#include <math.h>
using namespace std;

void PrintMatrix(float**, const int);
float GaussMethod(float**, const int);

int main()
{
	setlocale(LC_ALL, "");
	int dim;
	cout << "\t¬ведите размерность матрицы: "; cin >> dim;
	float** matrix = new float* [dim];
	for (int i = 0; i < dim; i++)
	{
		matrix[i] = new float[dim];
		for (int j = 0; j < dim; j++)
		{
			cout << "Maxtrix: " << i+1 << ":" << j+1<<" ";
			cin>> matrix[i][j];// = rand() % 10 * pow(-1, rand() % 2);
		}
	}
	PrintMatrix(matrix, dim);
	cout << "=================";
	cout<<"\n\n"<<GaussMethod(matrix, dim);
	PrintMatrix(matrix, dim);

	for (int i = 0; i < dim; i++)
	{
		delete[]matrix[i];
	}
	return 0;
}

void PrintMatrix(float** matrix, const int dim)
{
	for (int i = 0; i < dim; i++)
	{
		cout << "\n";
		for (int j = 0; j < dim; j++)
		{
			cout << "\t" << matrix[i][j];
		}
	}
	cout << "\n";
}

float GaussMethod(float** matrix, const int dim)
{
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
					//	cout << "\nmatrix[" << j << "][" << k << "] = " << "matrix[" << i << "][" << k << "] * matrix[" << j << "][" << i << "] / matrix[" << i << "][" << i << "] * (-1) + matrix[" << j << "][" << k << "]";
						//	PrintMatrix(matrix, dim);
					//	cout << "\t " << matrix[i][k] << " * " << matrix[j][i] << " / " << matrix[i][i] << " * (-1)";
				}
			}
		}
		return determinant * matrix[dim - 1][dim - 1];
}