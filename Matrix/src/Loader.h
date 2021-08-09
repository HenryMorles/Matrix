#pragma once
#include "Matrix.h"

class Loader {
public:
	virtual void Load(Matrix& OutMatrix) = 0;
};

class ConsoleLoader : public Loader {
public:
	void Load(Matrix& OutMatrix)override;
};

class FileLoader : public Loader {
	std::string PathToFile;
public:
	FileLoader(const std::string& InPathToFile);
	void Load(Matrix& OutMatrix)override;
};