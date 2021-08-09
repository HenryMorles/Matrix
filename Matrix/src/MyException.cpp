#include "MyException.h"

MyException::MyException() {}

MyException::MyException(std::string InError) {
	Error = InError;
}

OverFlowException::OverFlowException(std::string InError) {
	Error = InError;
}

const std::string OverFlowException::GetError() {
	return Error;
}

InvalidIndexException::InvalidIndexException(std::string InError) {
	Error = InError;
}

const std::string InvalidIndexException::GetError() {
	return Error;
}

InvalidArgumentException::InvalidArgumentException(std::string InError) {
	Error = InError;
}

const std::string InvalidArgumentException::GetError() {
	return Error;
}

IncorrectDataEntryException::IncorrectDataEntryException(std::string InError) {
	Error = InError;
}

const std::string IncorrectDataEntryException::GetError() {
	return Error;
}

FileOpenErrorException::FileOpenErrorException(std::string InError) {
	Error = InError;
}

const std::string FileOpenErrorException::GetError() {
	return Error;
}