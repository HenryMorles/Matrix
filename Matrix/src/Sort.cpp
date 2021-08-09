#include "Sort.h"
#include <algorithm>

bool Compare(Matrix& object1, Matrix& object2) {
	return object1.SumProductAxes() < object2.SumProductAxes();
}


void QuickSort::Sort(std::vector<Matrix>& ArrayMatrix) {
	std::sort(ArrayMatrix.begin(), ArrayMatrix.end(), Compare);
}

void QuickSort::Sort(Matrix* ArrayMatrix, const int Size) {
	std::vector<Matrix> TempVector;
	for (int i = 0; i < Size; ++i) {
		TempVector.push_back(ArrayMatrix[i]);
	}
	Sort(TempVector);
	for (int i = 0; i < Size; ++i) {
		ArrayMatrix[i] = TempVector[i];
	}
}

void UsualSort::Sort(std::vector<Matrix>& ArrayMatrix) {
	for (int i = 0; i < ArrayMatrix.size() - 1; ++i) {
		for (size_t j = 0; j < ArrayMatrix.size() - i - 1; ++j) {
			if (ArrayMatrix[j].SumProductAxes() > ArrayMatrix[j + 1].SumProductAxes()) {
				Matrix TempMatrix(ArrayMatrix[j]);
				ArrayMatrix[j] = ArrayMatrix[j + 1];
				ArrayMatrix[j + 1] = TempMatrix;
			}
			else if (ArrayMatrix[j].SumProductAxes() == ArrayMatrix[j + 1].SumProductAxes() && ArrayMatrix[j].TrailMatrix() > ArrayMatrix[j + 1].TrailMatrix()) {
				Matrix TempMatrix(ArrayMatrix[j]);
				ArrayMatrix[j] = ArrayMatrix[j + 1];
				ArrayMatrix[j + 1] = TempMatrix;
			}
		}
	}
}

void UsualSort::Sort(Matrix* ArrayMatrix, const int Size) {
	std::vector<Matrix> TempVector;
	for (int i = 0; i < Size; ++i) {
		TempVector.push_back(ArrayMatrix[i]);
	}
	Sort(TempVector);
	for (int i = 0; i < Size; ++i) {
		ArrayMatrix[i] = TempVector[i];
	}
}