#include "Matrix.h"
#include "MyException.h"
#include <list>

Matrix::Matrix() {
	rows = 0;
	columns = 0;
	Create();
}

Matrix::Matrix(const int rows, const int columns) : rows(rows), columns(columns) {
	Create(); //Creating a dynamic array
	GenerateString();
}

Matrix::Matrix(const std::vector<std::vector<int>>& arr) {
	rows = (int)arr.size();
	columns = (int)arr[0].size();
	Create(); //Creating a dynamic array
	for (int i = 0; i < rows; ++i) { //Moving elements from vector to array
		for (int j = 0; j < columns; ++j) {
			matrix[i][j] = arr[i][j];
		}
	}
	GenerateString();
}

Matrix::Matrix(const int rows, const int columns, const int value) : rows(rows), columns(columns) {
	Create();
	for (int i = 0; i < rows; ++i) { //Filling an array with one element
		for (int j = 0; j < columns; ++j) {
			matrix[i][j] = value;
		}
	}
	GenerateString();
}

Matrix::Matrix(const Matrix& object) : rows(object.rows), columns(object.columns) { //Copy constructor
	Create();
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			matrix[i][j] = object.matrix[i][j];
		}
	}
	matrix_str = object.matrix_str;
}

Matrix::Matrix(Matrix&& object)noexcept : rows(object.rows), columns(object.columns) { //Move constructor
	Create();
	matrix = object.matrix;
	matrix_str = object.matrix_str;
	for (int i = 0; i < object.rows; ++i) {
		matrix[i] = object.matrix[i];
	}
	object.matrix = nullptr;
}

Matrix::Matrix(const std::string& str) {
	bool status_heck = true; //To check if there were any errors when converting a string
	std::string temp_string; //Temporary variable to populate the list
	std::vector<int> temp_vector; //Temporary list for further placement of elements in the matrix
	rows = 0;
	columns = 0;
	if (str[0] == '[' && str[str.size() - 1] == ']') { //the first and last element are '[' , ']'
		for (size_t i = 1; i < str.size() - 1; ++i) {
			if (str[i] == ',') { //If the current element is ',' go to the next column
				temp_vector.push_back(std::stoi(temp_string));
				temp_string = "";
				++columns;
			}
			else if (str[i] == ';') { //If the current element is ';' go to the next line
				int tmp1 = std::stoi(temp_string);
				temp_vector.push_back(tmp1);
				temp_string = "";
				++rows;
				++columns;
			}
			else if (isdigit(str[i])) { //Checking if the current element is a number
				temp_string += str[i];
			}
			else {
				std::cout << "Error ! Invalid string format";
				status_heck = false;
			}
		}
	}
	else {
		std::cout << "Error ! Invalid string format";
		status_heck = false;
	}
	if (status_heck) {
		columns /= rows; //Determine the number of elements in a string
		Create();
		int Itr = 0;
		for (int i = 0; i < rows; ++i) { //Moving items from a list to a matrix
			for (int j = 0; j < columns; ++j, ++Itr) {
				matrix[i][j] = temp_vector[Itr];
			}
		}
	}
	GenerateString();
}

Matrix::~Matrix() {
	if (matrix != nullptr) {
		for (int i = 0; i < rows; i++) {
			delete matrix[i];
		}
		delete matrix;
	}
}

Matrix& Matrix::operator+=(const Matrix& object) {
	if (rows == object.rows && columns == object.columns) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				if (matrix[i][j] < INT_MAX - object.matrix[i][j] || matrix[i][j] > INT_MIN - object.matrix[i][j]) {
					matrix[i][j] += object.matrix[i][j];
				}
				else {
					throw OverFlowException("Error ! Overflow");
				}
			}
		}
	}
	else {
		throw InvalidArgumentException("Error ! Wrong matrix size");
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& object) {
	if (rows == object.rows && columns == object.columns) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				if (matrix[i][j] > INT_MIN + object.matrix[i][j] || matrix[i][j] < INT_MAX + object.matrix[i][j]) {
					matrix[i][j] -= object.matrix[i][j];
				}
				else {
					throw OverFlowException("Error ! Overflow");
				}
			}
		}
	}
	else {
		throw InvalidArgumentException("Error ! Wrong matrix size");
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& object) {
	Matrix temp_matrix(rows, object.columns);
	if (columns == object.rows) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < object.columns; ++j) {
				temp_matrix.matrix[i][j] = 0;
			}
		}
		int temp = 0;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < object.columns; ++j) {
				for (int k = 0; k < columns; ++k) {
					int temp = matrix[i][k];
					int temp1 = object.matrix[i][k];
					if (matrix[i][k] < INT_MAX / object.matrix[k][j] || matrix[i][k] > INT_MIN * object.matrix[k][j]) {
						temp_matrix.matrix[i][j] += matrix[i][k] * object.matrix[k][j];
					}
					else {
						std::cout << "Error ! Overflow";
						break;
					}
				}
			}
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < object.columns; ++j) {
				matrix[i][j] = temp_matrix.matrix[i][j];
			}
		}
	}
	else {
		throw InvalidArgumentException("Error ! Wrong matrix size");
	}
	return *this;
}

Matrix& Matrix::operator/=(const Matrix& object) {
	Matrix matr(rows, columns);
	Matrix obr_matr(rows, columns);
	Matrix tobr_matr(rows, columns);
	Matrix temp_matr(rows, rows);
	matr.matrix = object.matrix;
	int det = Determinant(matr, rows);
	if (det) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < rows; j++) {
				int m = rows - 1;
				CrossingOutColumnAndRow(matr, rows, temp_matr, i, j);
				obr_matr.matrix[i][j] = (int)pow(-1.0, i + j + 2) * Determinant(temp_matr, m) / det;
			}
		}
		TransposeTheMatrix(obr_matr, tobr_matr);
	}
	else {
		throw InvalidArgumentException("Error !The determinant is 0");
	}
	*this *= tobr_matr;
	return *this;

}

Matrix& Matrix::operator/=(const int value) {
	if (value != 0) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				matrix[i][j] /= value;
			}
		}
	}
	else {
		throw IncorrectDataEntryException("Error !The determinant is 0");
	}
	return *this;
}

Matrix& Matrix::operator+=(const int value) {
	if (value != 0) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				if (matrix[i][j] < INT_MAX - value || matrix[i][j] > INT_MIN - value) {
					matrix[i][j] += value;
				}
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const int value) {
	if (value != 0) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				if (matrix[i][j] > INT_MIN + value || matrix[i][j] < INT_MAX + value) {
					matrix[i][j] -= value;
				}
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const int value) {
	if (value != 0) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				if (matrix[i][j] < INT_MAX / value || matrix[i][j] > INT_MIN / value) {
					matrix[i][j] *= value;
				}
			}
		}
	}
	else {
		throw IncorrectDataEntryException("Error ! The value is 0");
	}
	return *this;
}

Matrix Matrix::operator+=(const std::string& value) {
	std::string temp_string = "";
	for (size_t i = 0; i < value.size(); ++i) {
		if (isdigit(value[i])) {
			temp_string += value[i];
		}
		else {
			throw IncorrectDataEntryException("Error ! Unknown symbol");
			return *this;
		}
	}
	int temp_value = std::stoi(temp_string);;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (matrix[i][j] < INT_MAX - temp_value || matrix[i][j] > INT_MIN - temp_value) {
				matrix[i][j] += temp_value;
			}
		}
	}
	return *this;
}

Matrix Matrix::operator-=(const std::string& value) {
	std::string temp_string = "";
	for (size_t i = 0; i < value.size(); ++i) {
		if (isdigit(value[i])) {
			temp_string += value[i];
		}
		else {
			throw IncorrectDataEntryException("Error ! Unknown symbol");
			return *this;
		}
	}
	int temp_value = std::stoi(temp_string);;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (matrix[i][j] > INT_MIN + temp_value || matrix[i][j] < INT_MAX + temp_value) {
				matrix[i][j] -= temp_value;
			}
		}
	}
	return *this;
}

Matrix Matrix::operator*=(const std::string& value) {
	std::string temp_string = "";
	for (size_t i = 0; i < value.size(); ++i) {
		if (isdigit(value[i])) {
			temp_string += value[i];
		}
		else {
			throw IncorrectDataEntryException("Error ! Unknown symbol");
			return *this;
		}
	}
	int temp_value = std::stoi(temp_string);;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (matrix[i][j] < INT_MAX / temp_value || matrix[i][j] > INT_MIN / temp_value) {
				matrix[i][j] *= temp_value;
			}
		}
	}
	return *this;
}

Matrix Matrix::operator/=(const std::string& value) {
	std::string temp_string = "";
	for (size_t i = 0; i < value.size(); ++i) {
		if (isdigit(value[i])) {
			temp_string += value[i];
		}
		else {
			throw IncorrectDataEntryException("Error ! Unknown symbol");
			return *this;
		}
	}
	int temp_value = std::stoi(temp_string);;
	if (temp_value != 0) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				matrix[i][j] /= temp_value;
			}
		}
	}
	else {
		throw IncorrectDataEntryException("Error ! The value is 0");
	}
	return *this;
}

bool Matrix::operator>=(Matrix& object) {
	if (MatrixSum() > object.MatrixSum()) {
		return true;
	}
	else if (MatrixSum() == object.MatrixSum()) {
		return true;
	}
	else {
		return false;
	}
}

bool Matrix::operator<=(Matrix& object) {
	if (MatrixSum() < object.MatrixSum()) {
		return true;
	}
	else if (MatrixSum() == object.MatrixSum()) {
		return true;
	}
	else {
		return false;
	}
}

bool Matrix::operator==(Matrix& object) {
	return MatrixSum() == object.MatrixSum();
}

bool Matrix::operator!=(Matrix& object) {
	return MatrixSum() != object.MatrixSum();
}

bool Matrix::operator<(Matrix& object) {
	return MatrixSum() < object.MatrixSum();
}

bool Matrix::operator>(Matrix& object) {
	return MatrixSum() > object.MatrixSum();
}

Matrix& Matrix::operator=(Matrix&& object)noexcept {
	if (&object != this) {
		if (matrix != nullptr) {
			for (int i = 0; i < rows; ++i) {
				delete[] matrix[i];
			}
			delete matrix;
		}
		rows = object.rows;
		columns = object.columns;
		matrix = object.matrix;
		matrix_str = object.matrix_str;
		object.matrix = nullptr;
	}
	return *this;
}

Matrix& Matrix::operator=(const Matrix& object) {
	if (&object != this) {
		rows = object.rows;
		columns = object.columns;
		Create();
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				matrix[i][j] = object.matrix[i][j];
			}
		}
	}
	return *this;
}

void Matrix::Create() { //Creating a dynamic array
	matrix = new int* [rows];
	for (int i = 0; i < rows; ++i) {
		matrix[i] = new int[columns];
	}
}

void Matrix::GenerateString() {
	matrix_str = "";
	matrix_str += '[';
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			matrix_str += std::to_string(matrix[i][j]);
			if (j != columns - 1) {
				matrix_str += ',';
			}
		}
		matrix_str += ';';
	}
	matrix_str += ']';
}

void Matrix::SetElement(const int rows, const int columns, const int value) {
	if (rows <= this->rows && columns <= this->columns) {
		matrix[rows][columns] = value;
		GenerateString();
	}
	else {
		throw InvalidIndexException("Error ! Going beyond the matrix");
	}
}

int Matrix::MatrixSum() {
	int temp_value = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			temp_value += matrix[i][j];
		}
	}
	return temp_value;
}

const std::string Matrix::GetString()const {
	return matrix_str;
}

int Matrix::SumElementsMainDiagonal() {
	int TempSum = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == j) {
				TempSum += matrix[i][j];
			}
		}
	}
	return TempSum;
}

int Matrix::SumElementsSideDiagonal() {
	int TempSum = 0;
	int i = (rows - 1);
	for (int j = 0; j < rows; j++) {
		TempSum += matrix[i][j];
		i--;
	}
	return TempSum;
}

int Matrix::SumProductAxes() {
	return SumElementsMainDiagonal() * SumElementsSideDiagonal();
}

int Matrix::TrailMatrix() {
	int TempSum = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (matrix[i] == matrix[j]) {
				TempSum += matrix[i][j];
			}
		}
	}
	return TempSum;
}

int Matrix::Determinant(const Matrix& matrix, const int InRows) {
	int temp = 0;   //Temporary variable to store the qualifier
	int k = 1;      //Power
	int m = InRows - 1;
	Matrix temp_matr(m, m);
	if (InRows < 1) {
		throw InvalidArgumentException("Error ! Wrong matrix size");
		return 0;
	}
	else if (InRows == 1) {
		temp = matrix.matrix[0][0];
	}
	else if (InRows == 2) {
		temp = matrix.matrix[0][0] * matrix.matrix[1][1] - matrix.matrix[1][0] * matrix.matrix[0][1];
	}
	else {
		for (int i = 0; i < InRows; i++) {
			CrossingOutColumnAndRow(matrix, InRows, temp_matr, 0, i);
			temp = temp + k * matrix.matrix[0][i] * Determinant(temp_matr, m);
			k = -k;
		}
	}
	return temp;
}

void Matrix::TransposeTheMatrix(const Matrix& InMatrix, Matrix& OutMatrix) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {
			OutMatrix.matrix[j][i] = InMatrix.matrix[i][j];
		}
	}
}

void Matrix::CrossingOutColumnAndRow(const Matrix& InMatrix, const int n, Matrix& OutMatrix, const int inRows, const int inColumns) {
	int ki = 0;
	for (int i = 0; i < n; i++) {
		if (i != inRows) {
			for (int j = 0, kj = 0; j < n; j++) {
				if (j != inColumns) {
					OutMatrix.matrix[ki][kj] = InMatrix.matrix[i][j];
					kj++;
				}
			}
			ki++;
		}
	}
}

const int Matrix::GetElement(const int InRows, const int InColumns)const {
	if (InRows <= rows && InColumns <= columns) {
		return matrix[InRows][InColumns];
	}
	return 0;
}

void Matrix::PrintMatrix()const {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			std::cout << matrix[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

int Matrix::GetRows() {
	return rows;
}

int Matrix::GetColumns() {
	return columns;
}