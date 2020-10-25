#pragma once

#include <sstream>
#include <iostream>
#include <exception>
#include <map>

using namespace std;


map<int, string> ErrorCodes = { 
	{0, "***OperationError: invalid meanings of arguments***" },
	{1, "***IndexError: array is empty or index is out of range***" },
	{2, "***IndexError: list is empty or index is out of range***" },
	{3, "***ValueError: value is not defined***" },
	{4, "***ValueError: there is not value of argument in the array***" },
	{5, "***ValueError: there is not value of argument in the list***" },
	{6, "***ValueError: there is not such subsequence in the current sequence***" },
	{7, "***ValueError: there is not value of argument in the binary tree***" }
};

class Exception: public exception {
protected:
	int code;
	string message;
	string file;
	int line;
public:
	string report() {
		ostringstream os;
		os << this->message << endl << "Hint: File " << this->file << ", Line " << this->line << endl;
		return os.str();
	}
};

class OperationError : public Exception {
public:
	OperationError(const int code, const string& file, const int& line)
	{
		this->code = code;
		this->message = ErrorCodes[code];
		this->file = file;
		this->line = line;
	}
};

class IndexOutOfRange : public Exception {
public:
	IndexOutOfRange(const int code, const string& file, const int& line)
	{
		this->code = code;
		this->message = ErrorCodes[code];
		this->file = file;
		this->line = line;
	}
};

class NoneValue : public Exception {
public:
	NoneValue(const int code, const string& file, const int& line)
	{
		this->code = code;
		this->message = ErrorCodes[code];
		this->file = file;
		this->line = line;
	}
};