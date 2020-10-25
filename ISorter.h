#pragma once

#include <chrono>

#include "Exception.h"
#include "Sequence.h"
#include "BinaryTree.h"
#include "BinaryTreeNode.h"

using namespace std::chrono;


template <class T>
class ISorter
{
protected:
    int order = 1;
    bool timerflag = true;
    void Swap(Sequence<T>* seq, const int index1, const int index2)
    {
        if (!seq || index1 < 0 || index2 < 0)
            throw OperationError(0, __FILE__, __LINE__);
        T item = seq->Get(index1);
        seq->Set(index1, seq->Get(index2));
        seq->Set(index2, item);
    }
public:
    int GetTimerFlag()
    {
        return this->timerflag;
    }
public:
    void SetOrder(const int order = 1)
    {
        this->order = order;
    }
    void SetTimerFlag(const bool flag = true)
    {
        this->timerflag = flag;
    }
    double SortWithTimer(Sequence<T>* input);
    virtual void Sort(Sequence<T>* input) = 0;
};


template <class T>
class ShakerSorter : public ISorter<T>
{
public:
    virtual void Sort(Sequence<T>* input) override;
};


template <class U>
class TreeSorter: public ISorter<U> 
{
public:
    virtual void Sort(Sequence<U>* input) override;
};


template <class T>
class ShellSorter : public ISorter<T> 
{
public:
    virtual void Sort(Sequence<T>* input) override;
};



template<class T>
double ISorter<T>::SortWithTimer(Sequence<T>* input)
{
    auto start = system_clock::now();
    this->Sort(input);
    auto finish = system_clock::now();
    duration<double> elapsed = finish - start;
    return elapsed.count() * 1000;
    /*auto start = steady_clock::now();
    this->Sort(input);
    auto finish = steady_clock::now();
    return duration_cast<microseconds>(finish - start).count();*/
}


template<class T>
void ShakerSorter<T>::Sort(Sequence<T>* input)
{
    if (!input)
        throw OperationError(0, __FILE__, __LINE__);
    int left = 0;
    int right = input->GetLength() - 1;
    int flag = 1;                                           // идентификатор смещения
    while ((left < right) && flag > 0)
    {
        flag = 0;
        for (int i = left; i < right; i++)
        {
            if (this->order)
            {
                if (input->Get(i) > input->Get(i + 1))
                {
                    this->Swap(input, i, i + 1);
                    flag = 1;
                }
            }
            else
            {
                if (input->Get(i) < input->Get(i + 1))
                {
                    this->Swap(input, i, i + 1);
                    flag = 1;
                }
            }
        }
        right--;
        for (int i = right; i > left; i--)
        {
            if (this->order)
            {
                if (input->Get(i - 1) > input->Get(i))
                {
                    this->Swap(input, i - 1, i);
                    flag = 1;
                }
            }
            else
            {
                if (input->Get(i - 1) < input->Get(i))
                {
                    this->Swap(input, i - 1, i);
                    flag = 1;
                }
            }
        }
        left++;
    }
}


template <class U>
void TreeSorter<U> ::Sort(Sequence<U>* input)
{
    string mode;
    if (!input)
        throw OperationError(0, __FILE__, __LINE__);
    typedef void* T;
    if (this->order == 1)
    {
        mode = "LNR";
    }
    else
    {
        mode = "RNL";
    }
    BinaryTree<U, T> tree;
    BinaryTreeNode<U, T>* node;
    Sequence<BinaryTreeNode<U, T>*>* thread;
    for (int i = 0; i < input->GetLength(); i++)
    {
        node = new BinaryTreeNode<U, T>(input->Get(i));
        tree.Insert(node);
    }
    bool flag = false;
    if (mode == "LNR")
    {
        flag = true;
        tree.Thread(mode);
    }
    if (mode == "RNL")
    {
        flag = true;
        tree.Thread(mode);
    }
    if (!flag)
    {
        throw OperationError(0, __FILE__, __LINE__);
    }
    thread = tree.GetThread();
    for (int i = 0; i < thread->GetLength(); i++)
    {
        input->Set(i, thread->Get(i)->GetTreeNode().key);
    }
}


template<class T>
void ShellSorter<T> ::Sort(Sequence<T>* input)
{
    if (!input)
        throw OperationError(0, __FILE__, __LINE__);
    int increment = 3;
    while (increment > 0)
    {
        for (int i = 0; i < input->GetLength(); i++)
        {
            int j = i;
            T temp = input->Get(i);
            if (this->order)
            {
                while ((j >= increment) && (input->Get(j - increment) > temp))
                {
                    input->Set(j, input->Get(j - increment));
                    j = j - increment;
                }
            }
            else
            {
                while ((j >= increment) && (input->Get(j - increment) < temp))
                {
                    input->Set(j, input->Get(j - increment));
                    j = j - increment;
                }
            }
            input->Set(j, temp);
        }
        if (increment > 1)
        {
            increment = increment / 2;
        }
        else
        {
            if (increment == 1)
                break;
        }
    }
}

