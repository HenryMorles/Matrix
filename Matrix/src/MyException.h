#pragma once
#include <string>
#include "Matrix.h"

class MyException {
public:
	std::string Error;
	MyException();
	MyException(std::string InError);
	virtual const std::string GetError() = 0;
};

class OverFlowException : public MyException {
public:
	OverFlowException(std::string InError);
	const std::string GetError()override;
};

class InvalidIndexException : public MyException {
public:
	InvalidIndexException(std::string InError);
	const std::string GetError()override;
};

class InvalidArgumentException : public MyException {
public:
	InvalidArgumentException(std::string InError);
	const std::string GetError()override;
};

class IncorrectDataEntryException : public MyException {
public:
	IncorrectDataEntryException(std::string InError);
	const std::string GetError()override;
};

class FileOpenErrorException : public MyException {
public:
	FileOpenErrorException(std::string InError);
	const std::string GetError()override;
};