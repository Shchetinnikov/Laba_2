#pragma once

#include <iostream>

#include "Exception.h"

using namespace std;

	
template <class T>
class Sequence {
public:
	virtual int GetLength() const = 0;
	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual T Get(const int i) const = 0;
	virtual Sequence<T>* GetSubsequence(const int start, const int end) const = 0;
public:
	virtual void Append(const T value) = 0;
	virtual void Prepend(const T value) = 0;
	virtual void Set(const int index, const T value) = 0;
	virtual void InsertAt(const int index, const T value) = 0;
	virtual void RemoveAt(const int index) = 0;
	virtual void Remove(const T value) = 0;
	virtual void RemoveAll(const T value) = 0;
	virtual Sequence<T>* Concat(const Sequence<T>& other) const = 0;
	virtual Sequence<T>* Copy() const = 0;
	virtual void CopyTo(Sequence<T>* target, const int startIndex) const = 0;
public:
	template<class T>
	friend bool operator!= (const Sequence<T>& lhs, const Sequence<T>& rhs);

	template<class T>
	friend ostream& operator<< (ostream& out, const Sequence<T>& sequence);
	
	template<class T>
	friend void operator>> (istream& in, Sequence<T>& sequence);
};


template<class T>
bool operator!= (const Sequence<T>& lhs, const Sequence<T>& rhs)
{
	if (lhs.GetLength() != lhs.GetLength())
		return true;
	for (int i = 0; i < lhs.GetLength(); i++)
	{
		if (lhs.Get(i) != rhs.Get(i))
			return true;
	}
	return false;
}


template<class T>
ostream& operator<< (ostream& out, const Sequence<T>& sequence)
{
	int i = 0;
	out << "[ ";
	if (sequence.GetLength() != 0)
	{
		for (i = 0; i < sequence.GetLength() - 1; i++)
		{
			out << sequence.Get(i) << ", ";
		}
		out << sequence.Get(i);
	}
	out << " ]";
	return out;
}


template<class T>
void operator>> (istream& in, Sequence<T>& sequence)
{
	if (sequence.GetLength() != 0)
	{
		throw OperationError(0, __FILE__, __LINE__);
	}
	char flag;
	T data;
	in >> flag;
	if (flag == '[')
	{
		if (in.peek() != ']')
		{
			while (in.peek() == ' ')
			{
				in.ignore(1);
			}
			while (in.peek() != ']')
			{
				in >> data;
				sequence.Append(data);
				while (in.peek() == ' ')
				{
					in.ignore(1);
				}
			}
		}
		in.ignore(1);
	}
	else
	{
		throw OperationError(0, __FILE__, __LINE__);
	}
}