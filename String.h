#pragma once

#include <iostream>

#include "Exception.h"

using namespace std;


class String
{
private:
	char* items;
	int length;
public:
	String(); // строка с нулевый указателем
	String(const char* str); // пустая строка или копия строки
	String(const String& str);
public:
	//void Print() const;
	int Length() const { return this->length; }; 
	char GetLetter(int index) const;
public:
	String operator+ (const String& str2);
	String operator* (int value);
	String operator= (const String& str2);
	bool operator== (const String& str2);
	bool operator!= (const String& str2);
	String operator()();
	friend ostream& operator<< (ostream &out, const String& str);
public:
	~String()
	{	
		if (this->items)
			delete[] this->items;
	};
};



String::String()
{
	this->items = nullptr;
	this->length = 0;
};

String :: String(const char* str) : length(0)
{
	if (!str)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	if (str == "\0")
	{
		this->items = new char[1];
		*(this->items) = '\0';
		this->length = 1;
	}
	else
	{
		int i = -1;
		int str_len = 0;
		do
		{
			i++;
			str_len++;
		} while (str[i] != '\0');

		items = new char[str_len];
		for (i = 0; i < str_len; i++)
		{
			items[i] = str[i];
		};
		this->length = str_len;
	};
};

String :: String(const String& str)
{
	if (!str.length || !str.items)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	this->length = str.length;
	this->items = new char[this->length];
	for (int i = 0; i < this->length; i++)
		items[i] = str.items[i];
};

char String :: GetLetter(int index) const
{
	if (index < 0 || index >= this->length || this->length <= 1 || !this->items)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	return this->items[index];
};

String String :: operator+ (const String& str2)
{
	if (!this->length || !this->items || !str2.length || !str2.items)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	String* concat = new String;
	concat->items = new char[this->length - 1 + str2.length];
	concat->length = this->length - 1 + str2.length;
	int index;
	for (index = 0; index < this->length - 1; index++)
	{
		concat->items[index] = this->items[index];
	};
	for (int i = 0; i < str2.length; i++)
	{
		concat->items[index] = str2.items[i];
		index++;
	};
	return *concat;
};

String String :: operator* (int value)
{
	if (value <= 0)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	String result("\0");
	for (int i = 0; i < value; i++)
	{
		result = result + *this;
	};
	return result;
};

String String :: operator= (const String& str2)
{
//	if (!this->length || !this->items || !str2.length || !str2.items)
//  	throw OperationError();
	delete[] this->items;
	String* ob = new String(str2);
	this->items = ob->items;
	this->length = ob->length;
	return *this;
};

bool String :: operator== (const String& str2)
{
	if (!this->length || !this->items || !str2.length || !str2.items)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	if (this->length == str2.length)
	{
		for (int i = 0; i < this->length; i++)
		{
			if (this->items[i] != str2.items[i])
				return false;
		};
	}
	else
		return false;
	return true;
};

bool String :: operator!= (const String& str2)
{
	if (!this->length || !this->items || !str2.length || !str2.items)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	if (this->length == str2.length)
	{
		for (int i = 0; i < this->length; i++)
		{
			if (this->items[i] != str2.items[i])
				return true;
		};
	}
	else
		return true;
	return false;
};

String String :: operator() ()
{
	return *this;
}

ostream& operator<< (ostream& out, const String& str) 
{
	if (!str.length)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	if (str.length > 1)
		for (int i = 0; i < str.length; i++)
			out << str.items[i];
	return out;
};