#pragma once
#include <vector>
#include <iostream>
#include <string>
class Matrix {
private:
	int** matrix;
	int columns; //Number of matrix columns
	int rows; //Number of matrix rows
	std::string matrix_str; //Storing a matrix as a string
	void Create(); //Creating and populating a dynamic array
	void GenerateString();
	void CrossingOutColumnAndRow(const Matrix& InMatrix, const int n, Matrix& OutMatrix, const int inRows, const int inColumns);
	int Determinant(const Matrix& matrix, const int inRows);
	void TransposeTheMatrix(const Matrix& InMatrix, Matrix& OutMatrix);
public:
	Matrix();
	Matrix(const int rows, const int columns);
	Matrix(const std::vector<std::vector<int>>& arr);
	Matrix(const Matrix& object); //Copy constructor
	Matrix(const int rows, const int columns, const int value);
	Matrix(Matrix&& object)noexcept; //Move constructor
	Matrix(const std::string& str); //Convert string to class object
	Matrix& operator=(const Matrix& object);
	Matrix& operator=(Matrix&& object)noexcept;
	friend Matrix& operator+(const Matrix& lhs, const Matrix& rhs) {
		(Matrix&)lhs += (Matrix)rhs;
		return (Matrix&)lhs;
	}
	friend Matrix& operator-(const Matrix& lhs, const Matrix& rhs) {
		(Matrix&)lhs -= (Matrix)rhs;
		return (Matrix&)lhs;
	}
	friend Matrix& operator*(const Matrix& lhs, const Matrix& rhs) {
		(Matrix&)lhs *= (Matrix)rhs;
		return (Matrix&)lhs;
	}
	friend Matrix& operator/(const Matrix& lhs, const Matrix& rhs) {
		(Matrix&)lhs /= (Matrix&)rhs;
		return (Matrix&)lhs;
	}

	Matrix& operator+=(const Matrix& object);
	Matrix& operator-=(const Matrix& object);
	Matrix& operator*=(const Matrix& object);
	Matrix& operator/=(const Matrix& object);

	friend Matrix& operator+(const Matrix& lhs, const int rhs) {
		(Matrix&)lhs += rhs;
		return (Matrix&)lhs;
	}
	friend Matrix& operator-(const Matrix& lhs, const int rhs) {
		(Matrix&)lhs -= rhs;
		return (Matrix&)lhs;
	}
	friend Matrix& operator*(const Matrix& lhs, const int rhs) {
		(Matrix&)lhs *= rhs;
		return (Matrix&)lhs;
	}
	friend Matrix& operator/(const Matrix& lhs, const int rhs) {
		(Matrix&)lhs /= rhs;
		return (Matrix&)lhs;
	}

	Matrix& operator+=(const int value);
	Matrix& operator-=(const int value);
	Matrix& operator*=(const int value);
	Matrix& operator/=(const int value);

	friend Matrix& operator+(const Matrix& lhs, const std::string& rhs) {
		(Matrix&)lhs += rhs;
		return (Matrix&)lhs;
	}
	friend Matrix& operator-(const Matrix& lhs, const std::string& rhs) {
		(Matrix&)lhs -= rhs;
		return (Matrix&)lhs;
	}
	friend Matrix& operator*(const Matrix& lhs, const std::string& rhs) {
		(Matrix&)lhs *= rhs;
		return (Matrix&)lhs;
	}
	friend Matrix& operator/(const Matrix& lhs, const std::string& rhs) {
		(Matrix&)lhs /= rhs;
		return (Matrix&)lhs;
	}

	Matrix operator+=(const std::string& value);
	Matrix operator-=(const std::string& value);
	Matrix operator*=(const std::string& value);
	Matrix operator/=(const std::string& value);

	bool operator>(Matrix& object);
	bool operator<(Matrix& object);
	bool operator>=(Matrix& object);
	bool operator<=(Matrix& object);
	bool operator==(Matrix& object);
	bool operator!=(Matrix& object);

	~Matrix();
	int GetRows();
	int GetColumns();
	int SumElementsMainDiagonal();
	int SumElementsSideDiagonal();
	int SumProductAxes();
	int TrailMatrix();
	int MatrixSum();
	void SetElement(const int rows, const int columns, const int value); //Element entry by index
	const std::string GetString()const;
	const int GetElement(const int rows, const int columns)const;//Element display by index
	void PrintMatrix()const;
};

