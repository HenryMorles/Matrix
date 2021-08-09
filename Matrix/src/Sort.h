#pragma once
#include "Matrix.h"

class Sorter {
public:
	virtual void Sort(std::vector<Matrix>& ArrayMatrix) = 0;
	virtual void Sort(Matrix* ArrayMatrix, const int Size) = 0;
};

class QuickSort : public Sorter {
public:
	void Sort(std::vector<Matrix>& ArrayMatrix)override;
	void Sort(Matrix* ArrayMatrix, const int Size)override;
};

class UsualSort : public Sorter {
public:
	void Sort(std::vector<Matrix>& ArrayMatrix)override;
	void Sort(Matrix* ArrayMatrix, const int Size)override;
};

