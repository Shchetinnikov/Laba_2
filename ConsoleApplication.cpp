#include <iostream>
#include <string>

#include "Exception.h"
#include "ConsoleColors.h"
#include "Interface.h"

using namespace std;

//#include "BinaryTreeNode.h"
//#include "BinaryTree.h"
//#include "Queue.hpp"
//#include "Complex.h"


int main()
{
    setlocale(LC_ALL, "Russian");

    string state;
    while (true) 
    {
        try {
            ShowCurrentMenu(state);
            char choice;
            cin >> choice;
            get<1>(allfuncs[state])(state, choice);
        }
        catch (Exception error) 
        {   
            PrintError(error);
        }
    }
   return 0;
}