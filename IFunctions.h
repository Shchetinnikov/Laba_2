#pragma once
#include <string>

#include "Exception.h"
#include "ConsoleColors.h"
#include "Sequence.h"
#include "SequenceGen.h"
#include "tests.h"
#include "CompareSorters.h"
#include "ExecuteSorter.h"


// Interface
void TypesItems();
void SequenceItems();
void SequenceClasses();
void SequenceToCompareItems();


void Menu(string& state, char choice)
{
	switch (choice)
	{
	case '1':
		state = "SortMenu";
		break;
	case '2':
		TestAll();
		break;
	case '3':
		PrintConclusion("\nPROGRAM IS TERMINATED");
		exit(0);
		break;
	default:
		throw OperationError(0, __FILE__, __LINE__);
	}
}


void SortMenu(string& state, char choice)
{
	switch (choice)
	{
	case '1':
		state = "Sorters";
		break;
	case '2':
		Compare();
		break;
	case '3':
		state = "Menu";
		break;
	case '4':
		PrintConclusion("\nPROGRAM IS TERMINATED");
		exit(0);
	default:
		throw OperationError(0, __FILE__, __LINE__);
	}
}


void SortersMenu(string& state, char choice)
{
	switch (choice)
	{
	case '1':
		ShakerSort();
		break;
	case '2':
		TreeSort();
		break;
	case '3':
		ShellSort();
		break;
	case '4':
		state = "SortMenu";
		break;
	case '5':
		PrintConclusion("\nPROGRAM IS TERMINATED");
		exit(0);
	default:
		throw OperationError(0, __FILE__, __LINE__);
	}

}

char ChooseSequence()
{
	char choice;
	SequenceClasses();
	cin >> choice;
	if (choice < '1' || choice > '2')
		throw OperationError(0, __FILE__, __LINE__);
	return choice;
}

char ChooseType()
{
	char choice;
	TypesItems();
	cin >> choice;
	if (choice < '1' || choice > '5')
		throw OperationError(0, __FILE__, __LINE__);
	return choice;
}


template<class T>
void GetSequence(Sequence<T>& input)
{
	SequenceItems();
	char choice;
	cin >> choice;
	switch (choice)
	{
	case '1':
		ConstantSequence(input);
		break;
	case '2':
		GenerateSequence(input);
		break;
	case '3':
		PrintSubheading("Warning: include the sequence in square brackets and separate every element by space");
		PrintSubheading("Warning: if type of elements is 'string', use escape character '\\0' at the end of element");
		AccessInput();
		cin >> input;
		break;
	default:
		throw OperationError(0, __FILE__, __LINE__);
	}
	return;
}

template<class T>
void GetSequenceToCompare(Sequence<T>& input)
{
	SequenceToCompareItems();
	char choice;
	cin >> choice;
	switch (choice)
	{
	case '1':
		DirectSortedSequence(input);
		break;
	case '2':
		ReverseSortedSequence(input);
		break;
	case '3':
		ConstantSequence(input);
		break;
	default:
		throw OperationError(0, __FILE__, __LINE__);
	}
	return;
}
