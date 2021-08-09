#pragma once
#include "Matrix.h"

template <class T>
class Iterators {
public:
	virtual T* First() = 0;
	virtual T* Next() = 0;
};