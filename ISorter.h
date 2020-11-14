#pragma once

#include <chrono>
#include <math.h>

#include "Exception.h"
#include "Sequence.h"
#include "BinaryTree.h"
#include "BinaryTreeNode.h"

using namespace std::chrono;

template <class T>
int AscendingComparer(T item1, T item2)
{
    if (item1 < item2)
        return -1;
    else
        if (item1 > item2)
            return 1;
        else
            return 0;
}

template <class T>
int DescendingComparer(T item1, T item2)
{
    if (item1 < item2)
        return 1;
    else
        if (item1 > item2)
            return -1;
        else
            return 0;
}

template <class T>
class ISorter
{
protected:
    int (*cmp)(T, T);
    double timer = 0;
protected:
    void Swap(Sequence<T>* seq, const int index1, const int index2)
    {
        if (!seq || index1 < 0 || index2 < 0)
            throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
        T item = seq->Get(index1);
        seq->Set(index1, seq->Get(index2));
        seq->Set(index2, item);
    }
public:
    double GetTimerValue()
    {
        return this->timer;
    }
public:
    virtual void Sort(Sequence<T>* input) = 0;
};


template <class T>
class ShakerSorter : public ISorter<T>
{
public:
    ShakerSorter(int (*cmp)(T, T))
    {
        this->cmp = cmp;
    }
public:
    virtual void Sort(Sequence<T>* input) override;
};


template <class U>
class TreeSorter: public ISorter<U> 
{
private:
    string mode;
public:
    TreeSorter(const string& mode)
    {
        this->mode = mode;
    }
public:
    virtual void Sort(Sequence<U>* input) override;
};


template <class T>
class ShellSorter : public ISorter<T> 
{
public:
    ShellSorter(int (*cmp)(T, T))
    {
        this->cmp = cmp;
    }
public:
    virtual void Sort(Sequence<T>* input) override;
};



template<class T>
void ShakerSorter<T>::Sort(Sequence<T>* input)
{
    if (!input)
        throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
   
    auto start = system_clock::now();
    int left = 0;
    int right = input->GetLength() - 1;
    int flag = 1;                                           // ������������� ��������
    
    while ((left < right) && flag > 0)
    {
        flag = 0;
        for (int i = left; i < right; i++)
        {
            if (this->cmp(input->Get(i), input->Get(i + 1)) == 1)
            {
                this->Swap(input, i, i + 1);
                flag = 1;
            }
        }
        right--;
        for (int i = right; i > left; i--)
        {
            if (this->cmp(input->Get(i - 1), input->Get(i)) == 1)
            {
                this->Swap(input, i - 1, i);
                flag = 1;
            }
         
        }
        left++;
    }

    auto finish = system_clock::now();
    duration<double> elapsed = finish - start;
    this->timer = elapsed.count() * 1000;
}


template <class U>
void TreeSorter<U> ::Sort(Sequence<U>* input)
{
    typedef void* T;
    if (!input || (this->mode != "LNR" && this->mode != "RNL"))
        throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

    auto start = system_clock::now();

    BinaryTree<U, T> tree;
    BinaryTreeNode<U, T>* node;
    Sequence<BinaryTreeNode<U, T>*>* thread;
    for (int i = 0; i < input->GetLength(); i++)
    {
        node = new BinaryTreeNode<U, T>(input->Get(i));
        tree.Insert(node);
    }

    tree.Thread(this->mode);
   
    thread = tree.GetThread();
    for (int i = 0; i < thread->GetLength(); i++)
    {
        input->Set(i, thread->Get(i)->GetTreeNode().key);
    }

    auto finish = system_clock::now();
    duration<double> elapsed = finish - start;
    this->timer = elapsed.count() * 1000;
}


template<class T>
void ShellSorter<T> ::Sort(Sequence<T>* input)
{
    if (!input)
        throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
   
    auto start = system_clock::now();

# if 0
    // ����� �������-���������
    // t = [log(n)]

    int t = floor(log2(input->GetLength()));
    int p = 2.5;  // 2,5, pi, exp

    if (t >= 8)
        t = 7;

    int* a = new int[t];
    for (int i = 0; i < t; i++)
        a[i] = floor(pow(p, i));

    std::vector<int> steps(t);
    for (int i = t - 1; i >= 0; i--)
    {
        steps[i] = 1;
        for (int j = 1; j <= i; j++)
            steps[i] *= a[j];
    }

    for (auto step : steps)
    {
        for (int i = 0; i < input->GetLength(); i++)
        {
            int j = i;
            T element = input->Get(i);
            while ((j >= step) && this->cmp(input->Get(j - step), element) == 1)  // ��������� ����/���� � ����� ������
            {
                input->Set(j, input->Get(j - step));
                j = j - step;
            }
            input->Set(j, element);
        }
    }

# endif

# if 0
    // ����������� ��������
    Sequence<int>* steps = new ListSequence<int>();
    int dist = 0;
    for (int i = 0; dist < input->GetLength(); i++)
    { 
        if (i % 2 == 0)
            dist = 9 * pow(2, i) - 9 * pow(2, i / 2) + 1;
        else
            dist = 8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1;
        steps->Prepend(dist);
    }

    for(int k = 0; k < steps->GetLength(); k++)
    {
        for (int i = 0; i < input->GetLength(); i++)
        {
            int j = i;
            T element = input->Get(i);
            while ((j >= steps->Get(k)) && this->cmp(input->Get(j - steps->Get(k)),element) == 1)  // ��������� ����/���� � ����� ������
            {
                input->Set(j, input->Get(j - steps->Get(k)));
                j = j - steps->Get(k);
            }
            input->Set(j, element);
        }
    }
    
# endif

# if 1
    // Distance d(i) / 2
    int step = input->GetLength() / 2;
    while(step > 0)
    {
        for (int i = 0; i < input->GetLength(); i++)
        {
            int j = i;
            T element = input->Get(i);
            while ((j >= step) && this->cmp(input->Get(j - step),element) == 1)  // ��������� ����/���� � ����� ������
            {
                input->Set(j, input->Get(j - step));
                j = j - step;
            }
            input->Set(j, element);
        }
        step = step / 2;
    }

# endif
    auto finish = system_clock::now();
    duration<double> elapsed = finish - start;
    this->timer = elapsed.count() * 1000;
}