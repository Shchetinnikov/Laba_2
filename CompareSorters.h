#pragma once

#include <string>

#include "Exception.h"
#include "Sequence.h"
#include "SequenceGen.h"
#include "ISorter.h"
#include "ExecuteSorter.h"

// Interface
void SorterItems();

//IFunctions
char ChooseType();

template<class T>
void GetSequenceToCompare(Sequence<T>& input);



char* CompareSortersItems()
{
	char* pair = (char*)malloc(2 * sizeof(char));
	istringstream in;

	PrintSubheading("\n Warning: input numbers of two sorters by space");
	SorterItems();

	for (int i = 0; i < 2; i++)
	{
		while (in.peek() == ' ')
		{
			in.ignore(1);
		}
		cin >> *(pair + i);
		if (*(pair + i) < '1' || *(pair + i) > '3')
		{
			in.str("");
			throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
		}
	}
	if (*(pair) == *(pair + 1))
	{
		in.str("");
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
	return pair;
}


template<class T>
void CompareSorters(ISorter<T>* sorter1, ISorter<T>* sorter2, Sequence<T>* input)
{
	Sequence<T>* copy = input->Copy();

	PrintHeading("\nFirst sorter output:");
	Sort(input, sorter1);

	PrintHeading("\nSecond sorter output:");
	Sort(copy, sorter2);

	delete input;
	delete copy;
}


template<class T>
ISorter<T>* GetFirstSorter(const char* pair, const int order)
{
	ISorter<T>* sorter;
	switch (*(pair))
	{
	case '1':
	{
		if (order)
		{
			ISorter<T>* sorter = new ShakerSorter<T>(AscendingComparer<T>);
			return sorter;

		}
		else
		{
			ISorter<T>* sorter = new ShakerSorter<T>(DescendingComparer<T>);
			return sorter;
		}
		
	}
	case '2':
	{
		if (order)
		{
			ISorter<T>* sorter = new TreeSorter<T>("LNR");
			return sorter;
		}
		else
		{
			ISorter<T>* sorter = new TreeSorter<T>("RNL");
			return sorter;
		}

	}
	case '3':
	{
		if (order)
		{
			ISorter<T>* sorter = new ShellSorter<T>(AscendingComparer<T>);
			return sorter;
		}
		else
		{
			ISorter<T>* sorter = new ShellSorter<T>(DescendingComparer<T>);
			return sorter;
		}
	}
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
}


template<class T>
ISorter<T>* GetSecondSorter(const char* pair, const int order)
{
	ISorter<T>* sorter;
	switch (*(pair + 1))
	{
	case '1':
	{
		if (order)
		{
			ISorter<T>* sorter = new ShakerSorter<T>(AscendingComparer<T>);
			return sorter;
		}
		else
		{
			ISorter<T>* sorter = new ShakerSorter<T>(DescendingComparer<T>);
			return sorter;
		}
	}
	case '2':
	{
		if (order)
		{
			ISorter<T>* sorter = new TreeSorter<T>("LNR");
			return sorter;
		}
		else
		{
			ISorter<T>* sorter = new TreeSorter<T>("RNL");
			return sorter;
		}
	}
	case '3':
	{
		if (order)
		{
			ISorter<T>* sorter = new ShellSorter<T>(AscendingComparer<T>);
			return sorter;
		}
		else
		{
			ISorter<T>* sorter = new ShellSorter<T>(DescendingComparer<T>);
			return sorter;
		}
	}
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
}


template<class T>
void GetSortersAndCompare(const char* pair, Sequence<T>* input)
{
	int order = AskOrder();
	ISorter<T>* sorter1 = GetFirstSorter<T>(pair, order);
	ISorter<T>* sorter2 = GetSecondSorter<T>(pair, order);

	CompareSorters(sorter1, sorter2, input);
	delete sorter1;
	delete sorter2;
}


template<class T>
void Compare(char* pair)
{
	char seq_choice = ChooseSequence();
	switch (seq_choice)
	{
	case '1':
	{
		Sequence<T>* seq = new ArraySequence<T>();
		GetSequenceToCompare(*seq);
		GetSortersAndCompare(pair, seq);
		break;
	}
	case '2':
	{
		Sequence<T>* seq = new ListSequence<T>();
		GetSequenceToCompare(*seq);
		GetSortersAndCompare(pair, seq); 
		break;
	}
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
	
}


void Compare()
{
	char* pair = CompareSortersItems();

	char type_choice = ChooseType();

	switch (type_choice)
	{
	case '1':
	{
		Compare<int>(pair);
		break;
	}
	case '2':
	{
		Compare<float>(pair);
		break;
	}
	case '3':
	{
		Compare<double>(pair);
		break;
	}
	case '4':
	{
		Compare<char>(pair);
		break;
	}
	case '5':
	{
		Compare<string>(pair);
		break;
	}
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
}