#pragma once

#include <string>

#include "Exception.h"
#include "Sequence.h"
#include "ISorter.h"


//IFunctions
char ChooseSequence();
char ChooseType();

// Interface
int AskOrder();


template<class T>
void Sort(Sequence<T>* input, ISorter<T>* sorter)
{
	
	cout << "Sequence length: " << input->GetLength() << endl;
	PrintSequence(*input, "\nInitial data:\n");

	sorter->Sort(input);
	
	PrintSequence(*input, "\nSorter result:\n");

	cout << "\nRunning time: " << sorter->GetTimerValue() << " milliseconds" << endl;

}

template<class T>
Sequence<T>* NewSequence()
{
	char seq_choice = ChooseSequence();
	switch (seq_choice)
	{
	case '1':
	{
		Sequence<T>* input = new ArraySequence<T>();
		GetSequence(*input);
		return input;
	}
	case '2':
	{
		Sequence<T>* input = new ListSequence<T>();
		GetSequence(*input);
		return input;

	}
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}

}


void ShakerSort()
{
	char type_choice = ChooseType();
	switch (type_choice)
	{
	case '1':
	{
		Sequence<int>* input = NewSequence<int>();
		ISorter<int>* sorter;
		
		if (AskOrder())
		{
			ISorter<int>* sorter = new ShakerSorter<int>(AscendingComparer<int>);
			Sort(input, sorter);
			delete sorter;

		}
		else
		{
			ISorter<int>* sorter = new ShakerSorter<int>(DescendingComparer<int>);
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	case '2':
	{
		Sequence<float>* input = NewSequence<float>();
		ISorter<float>* sorter;

		if (AskOrder())
		{
			ISorter<float>* sorter = new ShakerSorter<float>(AscendingComparer<float>);
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<float>* sorter = new ShakerSorter<float>(DescendingComparer<float>);
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	case '3':
	{
		Sequence<double>* input = NewSequence<double>();
		ISorter<double>* sorter;

		if (AskOrder())
		{
			ISorter<double>* sorter = new ShakerSorter<double>(AscendingComparer<double>);
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<double>* sorter = new ShakerSorter<double>(DescendingComparer<double>);
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	case '4':
	{
		Sequence<char>* input = NewSequence<char>();
		ISorter<char>* sorter;

		if (AskOrder())
		{
			ISorter<char>* sorter = new ShakerSorter<char>(AscendingComparer<char>);
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<char>* sorter = new ShakerSorter<char>(DescendingComparer<char>);
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	case '5':
	{
		Sequence<string>* input = NewSequence<string>();
		ISorter<string>* sorter;

		if (AskOrder())
		{
			ISorter<string>* sorter = new ShakerSorter<string>(AscendingComparer<string>);
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<string>* sorter = new ShakerSorter<string>(DescendingComparer<string>);
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
}


void TreeSort()
{
	char type_choice = ChooseType();
	switch (type_choice)
	{
	case '1':
	{
		Sequence<int>* input = NewSequence<int>();
		ISorter<int>* sorter;

		if (AskOrder())
		{
			ISorter<int>* sorter = new TreeSorter<int>("LNR");
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<int>* sorter = new TreeSorter<int>("RNL");
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	case '2':
	{
		Sequence<float>* input = NewSequence<float>();
		ISorter<float>* sorter;

		if (AskOrder())
		{
			ISorter<float>* sorter = new TreeSorter<float>("LNR");
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<float>* sorter = new TreeSorter<float>("RNL");
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	case '3':
	{
		Sequence<double>* input = NewSequence<double>();
		ISorter<double>* sorter;

		if (AskOrder())
		{
			ISorter<double>* sorter = new TreeSorter<double>("LNR");
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<double>* sorter = new TreeSorter<double>("RNL");
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	case '4':
	{
		Sequence<char>* input = NewSequence<char>();
		ISorter<char>* sorter;

		if (AskOrder())
		{
			ISorter<char>* sorter = new TreeSorter<char>("LNR");
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<char>* sorter = new TreeSorter<char>("RNL");
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	case '5':
	{
		Sequence<string>* input = NewSequence<string>();
		ISorter<string>* sorter;

		if (AskOrder())
		{
			ISorter<string>* sorter = new TreeSorter<string>("LNR");
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<string>* sorter = new TreeSorter<string>("RNL");
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
}


void ShellSort()
{
	char type_choice = ChooseType();
	switch (type_choice)
	{
	case '1':
	{
		Sequence<int>* input = NewSequence<int>();
		ISorter<int>* sorter;

		if (AskOrder())
		{
			ISorter<int>* sorter = new ShellSorter<int>(AscendingComparer<int>);
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<int>* sorter = new ShellSorter<int>(DescendingComparer<int>);
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	case '2':
	{
		Sequence<float>* input = NewSequence<float>();
		ISorter<float>* sorter;

		if (AskOrder())
		{
			ISorter<float>* sorter = new ShellSorter<float>(AscendingComparer<float>);
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<float>* sorter = new ShellSorter<float>(DescendingComparer<float>);
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	case '3':
	{
		Sequence<double>* input = NewSequence<double>();
		ISorter<double>* sorter;

		if (AskOrder())
		{
			ISorter<double>* sorter = new ShellSorter<double>(AscendingComparer<double>);
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<double>* sorter = new ShellSorter<double>(DescendingComparer<double>);
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	case '4':
	{
		Sequence<char>* input = NewSequence<char>();
		ISorter<char>* sorter;

		if (AskOrder())
		{
			ISorter<char>* sorter = new ShellSorter<char>(AscendingComparer<char>);
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<char>* sorter = new ShellSorter<char>(DescendingComparer<char>);
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	case '5':
	{
		Sequence<string>* input = NewSequence<string>();
		ISorter<string>* sorter;

		if (AskOrder())
		{
			ISorter<string>* sorter = new ShellSorter<string>(AscendingComparer<string>);
			Sort(input, sorter);
			delete sorter;
		}
		else
		{
			ISorter<string>* sorter = new ShellSorter<string>(DescendingComparer<string>);
			Sort(input, sorter);
			delete sorter;
		}

		delete input;
		break;
	}
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
}