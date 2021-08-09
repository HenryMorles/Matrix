#pragma once
#include "Iterator.h"
#include <iostream>
#include <fstream>
#include <map>
#include <functional>


template <class T>
class MyFunctor {
private:
	std::function<T(T&, T&)> Function;
public:
	MyFunctor() {}
	MyFunctor(std::function<T(T&, T&)> InFunction) {
		Function = InFunction;
	}
	T operator()(T& Lhs, T& Rhs) {
		return Function(Lhs, Rhs);
	}
};

template <class T>
class FunctorContainer {
private:
	std::map<std::string, MyFunctor<T>> FunctorMap;
public:
	FunctorContainer() {
		FunctorMap["+"] = MyFunctor<T>([](T& Lhs, T& Rhs) {
			return Lhs + Rhs;
			});
		FunctorMap["-"] = MyFunctor<T>([](T& Lhs, T& Rhs) {
			return Lhs - Rhs;
			});
		FunctorMap["*"] = MyFunctor<T>([](T& Lhs, T& Rhs) {
			return Lhs * Rhs;
			});
		FunctorMap["/"] = MyFunctor<T>([](T& Lhs, T& Rhs) {
			return Lhs / Rhs;
			});
	}
	MyFunctor<T> GetFunctor(std::string Operation) {
		if (FunctorMap.find(Operation) != FunctorMap.end()) {
			return FunctorMap[Operation];
		}
	}
};

template <class T>
class MyIterator : Iterators<T> {
	template <class T> friend class Container;
private:
	T* MatrixPointer;
	MyIterator(T* InMatrixPointer) {
		MatrixPointer = InMatrixPointer;
	}
public:
	MyIterator(const MyIterator& InIterator) {
		MatrixPointer = InIterator.MatrixPointer;
	}
	T* First()override {
		return &MatrixPointer[0];
	}
	T* Next()override {
		return MatrixPointer + 1;
	}
	bool operator!=(MyIterator const& Other)const {
		return MatrixPointer != Other.MatrixPointer;
	}
	bool operator==(MyIterator const& Other)const {
		return MatrixPointer != Other.MatrixPointer;
	}
	T& operator*()const {
		return *MatrixPointer;
	}
	MyIterator& operator++() {
		++MatrixPointer;
		return 	*this;
	}
	MyIterator operator++(int) {
		Matrix* OldMatrixPoiter = MatrixPointer;
		++MatrixPointer;
		return OldMatrixPoiter;
	}
};


template <class T>
class Container {
private:
	std::vector<std::shared_ptr<T>> Data;
	int NumberOperations;
	std::string* OperationsArray;
	FunctorContainer<T> FunctorCont;
public:
	Container() : NumberOperations(0) { }
	T& operator[](const int Index) {
		if (Index >= 0 && Index < Data.size()) {
			return Data[Index];
		}
		else {
			throw InvalidIndexException("Error ! Going beyond the array");
		}
	}
	void PushBack(T& Object) {
		std::shared_ptr<T>TempPtr(new T);
		*TempPtr = Object;
		Data.push_back(std::move(TempPtr));
	}
	void Load(bool NumberLoad, const int Rows, const int Columns, const std::string& InPathToFile = " ") {
		if (!NumberLoad) {
			FileLoader TempLoader(InPathToFile);
			T TempMatrix(0, 0);
			TempLoader.Load(TempMatrix);
			PushBack(TempMatrix);
		}
		else {
			T TempMatrix(Rows, Columns);
			ConsoleLoader TempLoader;
			TempLoader.Load(TempMatrix);
			PushBack(TempMatrix);
		}
	}
	void Sort(bool bQuickSort = false) {
		if (!bQuickSort) {
			QuickSort Sort;
			Sort.Sort(Data.get(), Data.size());
		}
		else {
			UsualSort Sort;
			Sort.Sort(Data.get(), Data.size());
		}
	}
	void Erase(const int Index) {
		if (Index >= 0 && Index < Data.size()) {
			auto It = Data.begin();
			Data.erase(It + Index);
		}
		else {
			throw InvalidIndexException("Error ! Going beyond the array");
		}
	}
	void PrintListElements() {
		for (int i = 0; i < Data.size(); ++i) {
			Data[i].PrintMatrix();
		}
	}
	void LoadOperations(const std::string& InPathToFile, const int InNumberOperations) {
		NumberOperations = InNumberOperations;
		std::ifstream in(InPathToFile);
		if (in.is_open()) {
			std::string TempString = "";
			OperationsArray = new std::string[NumberOperations];
			for (int i = 0; i < NumberOperations; ++i) {
				std::getline(in, TempString);
				OperationsArray[i] = TempString;
			}
		}
		else {
			throw FileOpenErrorException("Error ! Could not open file");
		}
		in.close();
	}
	T& PerformOperation(T& Lhs, T& Rhs, const std::string& Operation) {
		if (Operation == OperationsArray[0]) {
			return Lhs += Rhs;
		}
		else if (Operation == OperationsArray[1]) {
			return Lhs -= Rhs;
		}
		else if (Operation == OperationsArray[2]) {
			return Lhs *= Rhs;
		}
		else if (Operation == OperationsArray[3]) {
			return Lhs /= Rhs;
		}
		else {
			throw IncorrectDataEntryException("Error ! Unknown symbol");
		}
	}
	T Calculate(const std::string& InPathToFile) {
		T TempValue;
		for (int i = 1, j = 0; i < Data.size(); ++i, ++j) {
			if (j == NumberOperations - 1) {
				j = 0;
			}
			if (i == 1) {
				MyFunctor<T> Functor = FunctorCont.GetFunctor(OperationsArray[j]);
				TempValue  = Functor(*Data[0], *Data[i]);
			}
			else {
				MyFunctor<T> Functor = FunctorCont.GetFunctor(OperationsArray[j]);
				TempValue = Functor(TempValue, *Data[i]);
			}
		}
		return TempValue;
	}
	MyIterator<T> Begin() {
		return MyIterator<T>(&Data[0]);
	}
	MyIterator<T> End() {
		return MyIterator<T>(Data.end());
	}
	const MyIterator<T> CBegin()const {
		return MyIterator<T>(&Data[0]);
	}
	const MyIterator<T> CEnd()const {
		return MyIterator<T>(Data.end());
	}
};
