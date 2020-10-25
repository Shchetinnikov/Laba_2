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
bool AskTimer();


template<class T>
void Sort(Sequence<T>* input, ISorter<T>* sorter)
{
	cout << "Sequence length: " << input->GetLength() << endl;
	PrintSequence(*input, "\nInitial data:\n");

	if (sorter->GetTimerFlag())
	{
		cout << "\nRunning time: " << sorter->SortWithTimer(input) << " milliseconds" << endl;
	}
	else
	{
		sorter->Sort(input);
	}

	PrintSequence(*input, "\nSorter result:\n");
}


template<class T>
void Sort(ISorter<T>* sorter)
{
	char seq_choice = ChooseSequence();
	
	switch (seq_choice)
	{
	case '1':
	{
		Sequence<T>* input = new ArraySequence<T>();
		GetSequence(*input);

		sorter->SetOrder(AskOrder());
		sorter->SetTimerFlag(AskTimer());

		Sort(input, sorter);

		delete input;
		break;
	}
	case '2':
	{
		Sequence<T>* input = new ListSequence<T>();
		GetSequence(*input);

		sorter->SetOrder(AskOrder());
		sorter->SetTimerFlag(AskTimer());

		Sort(input, sorter);

		delete input;
		break;
	}
	default:
		throw OperationError(0, __FILE__, __LINE__);
	}
	
	
}


void ShakerSort()
{
	char type_choice = ChooseType();
	switch (type_choice)
	{
	case '1':
	{
		ISorter<int>* sorter = new ShakerSorter<int>();
		Sort(sorter);
		delete sorter;
		break;
	}
	case '2':
	{
		ISorter<float>* sorter = new ShakerSorter<float>();
		Sort(sorter);
		delete sorter;
		break;
	}
	case '3':
	{
		ISorter<double>* sorter = new ShakerSorter<double>();
		Sort(sorter);
		delete sorter;
		break;
	}
	case '4':
	{
		ISorter<char>* sorter = new ShakerSorter<char>();
		Sort(sorter);
		delete sorter;
		break;
	}
	case '5':
	{
		ISorter<string>* sorter = new ShakerSorter<string>();
		Sort(sorter);
		delete sorter;
		break;
	}
	default:
		throw OperationError(0, __FILE__, __LINE__);
	}
}


void TreeSort()
{
	char type_choice = ChooseType();
	switch (type_choice)
	{
	case '1':
	{
		ISorter<int>* sorter = new TreeSorter<int>();
		Sort(sorter);
		delete sorter;
		break;
	}
	case '2':
	{
		ISorter<float>* sorter = new TreeSorter<float>();
		Sort(sorter);
		delete sorter;
		break;
	}
	case '3':
	{
		ISorter<double>* sorter = new TreeSorter<double>();
		Sort(sorter);
		delete sorter;
		break;
	}
	case '4':
	{
		ISorter<char>* sorter = new TreeSorter<char>();
		Sort(sorter);
		delete sorter;
		break;
	}
	case '5':
	{
		ISorter<string>* sorter = new TreeSorter<string>();
		Sort(sorter);
		delete sorter;
		break;
	}
	default:
		throw OperationError(0, __FILE__, __LINE__);
	}
}


void ShellSort()
{
	char type_choice = ChooseType();
	switch (type_choice)
	{
	case '1':
	{
		ISorter<int>* sorter = new ShellSorter<int>();
		Sort(sorter);
		delete sorter;
		break;
	}
	case '2':
	{
		ISorter<float>* sorter = new ShellSorter<float>();
		Sort(sorter);
		delete sorter;
		break;
	}
	case '3':
	{
		ISorter<double>* sorter = new ShellSorter<double>();
		Sort(sorter);
		delete sorter;
		break;
	}
	case '4':
	{
		ISorter<char>* sorter = new ShellSorter<char>();
		Sort(sorter);
		delete sorter;
		break;
	}
	case '5':
	{
		ISorter<string>* sorter = new ShellSorter<string>();
		Sort(sorter);
		delete sorter;
		break;
	}
	default:
		throw OperationError(0, __FILE__, __LINE__);
	}
}
