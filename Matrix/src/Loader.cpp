#include "Loader.h"
#include <fstream>
#include "MyException.h"


void ConsoleLoader::Load(Matrix& OutMatrix) {
	for (int i = 0; i < OutMatrix.GetRows(); ++i) {
		for (int j = 0; j < OutMatrix.GetColumns(); ++j) {
			system("cls");
			std::cout << "Rows number " << i << " Columns number " << j << '\n';
			int TempValue;
			std::cin >> TempValue;
			OutMatrix.SetElement(i, j, TempValue);
		}
	}
}

FileLoader::FileLoader(const std::string& InPathToFile) {
	PathToFile = InPathToFile;
}

void FileLoader::Load(Matrix& OutMatrix) {
	std::ifstream in(PathToFile);
	if (in.is_open()) {
		std::string TempString = "";
		std::getline(in, TempString);
		Matrix TempMatrix(TempString);
		OutMatrix = TempMatrix;
	}
	else {
		throw FileOpenErrorException("Error ! Could not open file");
	}
	in.close();
}