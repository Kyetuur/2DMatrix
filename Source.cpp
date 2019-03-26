
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <initializer_list>
#include <random>
#include <ostream>



class Matrix
{
	double * implementationArray;
	int heightDimension;
	int widthDimension;

public:

	Matrix()
	{
		std::cout << "Constructor of empty matrix" << std::endl;
		implementationArray = nullptr;
		heightDimension = 0;
		widthDimension = 0;
	}

	Matrix(int N, int M)
	{
		std::cout << "Constructor of "<< N<<"*"<<M <<" matrix" << std::endl;
		heightDimension = N;
		widthDimension = M;
		implementationArray = new double[N*M];
		for (int i = 0; i < N*M; i++)
		{
			implementationArray[i] = 0.0;
		}

	}

	Matrix(std::initializer_list<std::vector<double>> list)
	{
		int N = list.size();
		int M = 0;
		for (auto& row : list)
		{
			if (row.size() > M)
			{
				M = row.size();
			}
		}
		std::cout << "Constructor of " << N << "*" << M << " matrix from initializer_list" << std::endl;

		implementationArray = new double[N*M];
		heightDimension = N;
		widthDimension = M;

		auto currentRow = list.begin();
		for (int i = 0; i < N; i++)
		{

			for (int j = 0; j < M; j++)
			{
				for (auto& z : *currentRow)
				{
					implementationArray[i*M + j] = z;
					j++;

				}
				if (j >= M)
				{
					break;
				}
				implementationArray[i*M + j] = 0.0;
			}
			if(currentRow != list.end())
				currentRow++;
		}


	}

	Matrix(const Matrix& original)
	{
		std::cout << "Copy constructor" << std::endl;
		widthDimension = original.widthDimension;
		heightDimension = original.heightDimension;
		implementationArray = new double[widthDimension*heightDimension];
		for (int i = 0; i < widthDimension * heightDimension; i++)
		{
			implementationArray[i] = original.implementationArray[i];
		}
	}



	~Matrix()
	{
		std::cout << "Destructor of matrix" << std::endl;
		delete[] implementationArray;
	}


	friend std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);
	Matrix& operator=(const Matrix& original)
	{
		std::cout << "Assigment copy" << std::endl;
		widthDimension = original.widthDimension;
		heightDimension = original.heightDimension;
		implementationArray = new double[widthDimension*heightDimension];
		for (int i = 0; i < widthDimension * heightDimension; i++)
		{
			implementationArray[i] = original.implementationArray[i];
		}
		return *this;
	}

	double operator()(int n, int m)
	{
		return implementationArray[(n)*(m) + (m-1)];
	}


};
std::ostream& operator<<(std::ostream& stream, const Matrix& matrix)
{
	
	for (int i = 0; i < matrix.heightDimension; i++)
	{
		stream << "{";
		for (int j = 0; j < matrix.widthDimension; j++)
		{
			if( j!=0)
				stream <<", " << matrix.implementationArray[i*matrix.widthDimension + j];
			else
				stream << matrix.implementationArray[i*matrix.widthDimension + j];

		}
		stream << "}" << std::endl;
		
	}
	stream << std::endl;
	return stream;
}


int main()
{
	using std::cout;
	using std::endl;
	Matrix m1;         // default constructor: N=M=0, data=nullptr
	Matrix m2(3,4);    // N = 3, M = 4, data = N*M doubles set to 0.0 
	Matrix m3({{1,2,3},{32, 23, 22},{3,234,23,44}}); // from initializer_list 
	cout << m2(1,1) << endl;    // 0  - the first element in data (we count from 1)
	cout << m3(2,2) << endl;    // 23 
	cout << m3;                 // prints matrix 
	cout << "Copy semantics \n"; 
	Matrix m4 = m2;     // copy constructor that makes deep copy of the matrix m2 
	cout << m4;
	m4 = m3;            // copy assignment makes deep copy of the matrix m3
	
	//cout << m4;
	cout << m4;

}