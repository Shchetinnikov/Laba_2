#pragma once

#include <iostream>
#include <string>

#include "Exception.h"
#include "Sequence.h"
#include "ListSequence.h"
#include "BinaryTreeNode.h"

using namespace std;

/*
	Бинарное дерево поиска
	Полное упорядочивание с отношением родетель-дочерний узел (Ключи не повторяются):
		- левое поддерево <= корень
		- правое поддерево > корень

*/


template <class U, class T>
class BinaryTree 
{
private:
	BinaryTreeNode<U, T>* root;
	Sequence<BinaryTreeNode<U, T>*>* thread;										// прошитое дерево
protected:																		
	// вспомогательные функции рекурсивного вызова
	BinaryTreeNode<U, T>* GetParent(BinaryTreeNode<U, T>* child, BinaryTreeNode<U, T>* start, string& place);
	BinaryTreeNode<U, T>* MapRecursive(BinaryTreeNode<U, T>* node, BinaryTreeNode<U, T>* (*mfun)(BinaryTreeNode<U, T>*));
	void WhereRecursive(BinaryTreeNode<U, T>* start, BinaryTree<U, T>* result, bool (*wfun)(BinaryTreeNode<U, T>*));
	void InsertRecursive(BinaryTreeNode<U, T>* node, BinaryTreeNode<U, T>* start);
	void ThreadRecursive(BinaryTreeNode<U, T>* start, Sequence<BinaryTreeNode<U, T>*>* seq, const string order);
public:	
	// конструкторы
	BinaryTree() { this->root = nullptr; this->thread = nullptr; };					// пустое дерево
	BinaryTree(const BinaryTree<U, T>& btree);										// копирующий конструктор
public: 
	// декомпозиция 
	BinaryTreeNode<U, T>* GetRoot() const 
	{ 
		return this->root; 
	};
	Sequence<BinaryTreeNode<U, T>*>* GetThread() const 
	{ 
		return this->thread; 
	};
	BinaryTreeNode<U, T>* GetNode(const U& key, BinaryTreeNode<U, T>* start) const;
	BinaryTree<U, T>* GetSubTree(const U& key, BinaryTreeNode<U, T>* start) const;
	bool Find(const U& key, BinaryTreeNode<U, T>* start) const;
	bool FindSubTree(BinaryTree<U, T>* subtree) const;
public: 
	// операции над деревом
	void Round(BinaryTreeNode<U, T>* start, void (*visit)(BinaryTreeNode<U, T>*), const string order = "NLR");
	void Insert(BinaryTreeNode<U, T>* node);
	void Insert(const U& key, const T& item);
	bool RemoveNode(const U& key);																	// ЛОМАЕТСЯ НА УДАЛЕНИИ КОРНЯ
	bool RemoveNode(BinaryTreeNode<U, T>* node);													//		
	bool RemoveSubTree(const U& rootkey);
	//BinaryTree<U, T>* AvlTree(const string order = "NLR") const;									
	BinaryTree<U, T>* Map(BinaryTreeNode<U, T>* (*mfun)(BinaryTreeNode<U, T>*)) const;
	BinaryTree<U, T>* Where(bool (*wfun)(BinaryTreeNode<U, T>*)) const;
	T Reduce(T(*rfun)(T, T), const T& startvalue, const string order = "NLR") const;
	void Thread(const string order = "NLR");
	//Sequence<BinaryTreeNode<U, T>*>* ConvertToSequence(const string order = "NLR") const;			
public:
	// деструктор
	~BinaryTree() {
		if (this->root)
		{
			Round(this->root, DeleteNode, "LRN");
		}
		if (thread)
		{
			delete thread;
		}
	}
};


template <class U, class T>
BinaryTree<U, T> ::BinaryTree(const BinaryTree<U, T>& btree) : root(nullptr), thread(nullptr)
{
	this->root = MapRecursive(btree.GetRoot(), CopyNode);
}


template <class U, class T>
BinaryTreeNode<U, T>* BinaryTree<U, T> ::GetNode(const U& key, BinaryTreeNode<U, T>* start) const
{
	if (!start)
	{
		return nullptr;
	}
	if (start->GetTreeNode().key == key)
	{
		return start;
	}
	BinaryTreeNode<U, T>* left = GetNode(key, start->GetLeft());
	BinaryTreeNode<U, T>* right = GetNode(key, start->GetRight());
	if (left)
	{
		return left;
	}
	if (right)
	{
		return right;
	}
	return nullptr;
}


template <class U, class T>
BinaryTree<U, T>* BinaryTree<U, T> ::GetSubTree(const U& key, BinaryTreeNode<U, T>* start) const
{
	BinaryTree<U, T>* btree = new BinaryTree<U, T>();
	btree->root = this->GetNode(key, start);
	BinaryTree<U, T>* subtree = new BinaryTree<U, T>(*btree);
	btree->root = nullptr;
	delete btree;
	return subtree;
}


template <class U, class T>
bool BinaryTree<U, T> ::Find(const U& key, BinaryTreeNode<U, T>* start) const
{
	string order = "NLR";
	if (!start)
	{
		return false;
	}
	for (int i = 0; i < order.size(); i++)
		switch (order[i])
		{
		case 'N':
			if (start->GetTreeNode().key == key)
			{
				return true;
			}
			break;
		case 'L':
			if (Find(key, start->GetLeft()))
			{
				return true;
			}
			break;
		case 'R':
			if (Find(key, start->GetRight()))
			{
				return true;
			}
			break;
		};
	return false;
}


template <class U, class T>
bool BinaryTree<U, T> ::FindSubTree(BinaryTree<U, T>* subtree) const
{
	if (!subtree->root)
	{
		throw OperationError(0, __FILE__, __LINE__);
	}
	if (!this->root)
	{
		return false;
	}
	BinaryTree<U, T>* btree = new BinaryTree<U, T>(*this);							// копия
	btree->Thread();
	subtree->Thread();
	BinaryTreeNode<U, T>* start = subtree->GetThread()->GetFirst();
	BinaryTreeNode<U, T>* item;
	BinaryTreeNode<U, T>* node;
	bool flag = false;
	for (int i = 0; i < btree->GetThread()->GetLength(); i++)
	{
		item = btree->GetThread()->Get(i);
		if (start->GetTreeNode().key == item->GetTreeNode().key && start->GetTreeNode().data == item->GetTreeNode().data)
		{
			flag = true;
			for (int k = 1; k < subtree->GetThread()->GetLength(); k++)
			{
				item = btree->GetThread()->Get(i + k);
				node = subtree->GetThread()->Get(k);
				if (node->GetTreeNode().data != item->GetTreeNode().data || node->GetTreeNode().key != item->GetTreeNode().key)
				{
					flag = false;
					break;
				}
			}
			break;
		};
	};
	return flag;
}


template <class U, class T>
void BinaryTree<U, T> ::Round(BinaryTreeNode<U, T>* start, void (*visit)(BinaryTreeNode<U, T>*), const string order)
{
	if (!start)
		return;
	for (int i = 0; i < order.size(); i++)
		switch (order[i])
		{
		case 'N':
			visit(start);
			break;
		case 'L':
			Round(start->GetLeft(), visit, order);
			break;
		case 'R':
			Round(start->GetRight(), visit, order);
			break;
		default:
			throw OperationError(0, __FILE__, __LINE__);
		}
}


template <class U, class T>
void BinaryTree<U, T> ::Insert(BinaryTreeNode<U, T>* node)
{
	if (!node)
		throw OperationError(0, __FILE__, __LINE__);
	if (!this->root)
	{
		this->root = new BinaryTreeNode<U, T>(node->GetTreeNode().key, node->GetTreeNode().data,
			node->GetLeft(), node->GetRight());
		return;
	};
	InsertRecursive(node, this->root);
}


template <class U, class T>
void BinaryTree<U, T> ::Insert(const U& key, const T& item)
{
	BinaryTreeNode<U, T>* node = new BinaryTreeNode<U, T>(key, item);
	this->Insert(node);
}


template <class U, class T>
bool BinaryTree<U, T> ::RemoveNode(BinaryTreeNode<U, T>* node)
{
	BinaryTreeNode<U, T>* node_f = this->GetNode(node->GetTreeNode().key, this->root);
	if (!(node_f && node_f->GetTreeNode().data == node->GetTreeNode().data))
		return false;
	string place = "";
	BinaryTreeNode<U, T>* left = node_f->GetLeft();
	BinaryTreeNode<U, T>* right = node_f->GetRight();
	BinaryTreeNode<U, T>* parent = GetParent(node_f, this->root, place);
	if (!left && !right) {
		if (parent)
			if (place == "left")
				parent->SetLeft(nullptr);
			else
				parent->SetRight(nullptr);
		delete node_f;
		return true;
	};
	if (left) {
		while (left->GetRight())
			left = left->GetRight();
		if (!left->GetLeft() && !left->GetRight()) {
			string place_left = "";
			BinaryTreeNode<U, T>* parent_left = GetParent(left, node_f, place_left);
			if (place_left == "left")
				parent_left->SetLeft(nullptr);
			else
				parent_left->SetRight(nullptr);
			if (parent) {
				if (place == "left") {
					parent->SetLeft(left);
					delete left;
					parent->GetLeft()->SetLeft(node_f->GetLeft());
					parent->GetLeft()->SetRight(node_f->GetRight());
				}
				if (place == "right") {
					parent->SetRight(left);
					delete left;
					parent->GetRight()->SetLeft(node_f->GetLeft());
					parent->GetRight()->SetRight(node_f->GetRight());
				}
			}
			else {
				left->SetLeft(node_f->GetLeft());
				left->SetRight(node_f->GetRight());
			}
			if (node_f->GetLeft())
				delete node_f->GetLeft();
			if (node_f->GetRight())
				delete node_f->GetRight();
			delete node_f;
			return true;
		};
	};
	if (right) {
		while (right->GetLeft())
			right = right->GetLeft();
		if (!right->GetLeft() && !right->GetRight()) {
			string place_right = "";
			BinaryTreeNode<U, T>* parent_right = GetParent(right, node_f, place_right);
			if (place_right == "left")
				parent_right->SetLeft(nullptr);
			else
				parent_right->SetRight(nullptr);
			if (parent) {
				if (place == "left") {
					parent->SetLeft(right);
					delete right;
					parent->GetLeft()->SetLeft(node_f->GetLeft());
					parent->GetLeft()->SetRight(node_f->GetRight());
				}
				if (place == "right") {
					parent->SetRight(right);
					delete right;
					parent->GetRight()->SetLeft(node_f->GetLeft());
					parent->GetRight()->SetRight(node_f->GetRight());
				}
			}
			else {
				right->SetLeft(node_f->GetLeft());
				right->SetRight(node_f->GetRight());
			}
			if (node_f->GetLeft())
				delete node_f->GetLeft();
			if (node_f->GetRight())
				delete node_f->GetRight();
			delete node_f;
			return true;
		};
	};
	return false;
}


template <class U, class T>
bool BinaryTree<U, T> ::RemoveNode(const U& key)
{
	BinaryTreeNode<U, T>* node = this->GetNode(key, this->root);
	if (!node)
	{
		return false;
	}
	return this->RemoveNode(node);
}


template <class U, class T>
bool BinaryTree<U, T> ::RemoveSubTree(const U& rootkey)
{
	string place = "";
	BinaryTreeNode<U, T>* node = this->GetNode(rootkey, this->root);
	if (!node)
	{
		return false;
	}
	BinaryTreeNode<U, T>* parent = GetParent(node, this->root, place);
	Round(node, DeleteNode, "LRN");
	if (parent)
	{
		if (place == "left")
		{
			parent->SetLeft(nullptr);
		}
		else
		{
			parent->SetRight(nullptr);
		}
	}
	return true;
}


//template <class U, class T>
//BinaryTree<U, T>* BinaryTree<U, T> :: AvlTree(const string order) const {
//
//}


template <class U, class T>
BinaryTree<U, T>* BinaryTree<U, T> ::Map(BinaryTreeNode<U, T>* (*mfun)(BinaryTreeNode<U, T>*)) const
{
	BinaryTree<U, T>* new_btree = new BinaryTree<U, T>();
	new_btree->root = MapRecursive(this->root, mfun);
	new_btree->thread = nullptr;
	return new_btree;
}


template <class U, class T>
BinaryTree<U, T>* BinaryTree<U, T> ::Where(bool (*wfun)(BinaryTreeNode <U, T>*)) const
{
	BinaryTree<U, T>* result = new BinaryTree<U, T>();
	WhereRecursive(this->root, result, wfun);
	return result;
}


template <class U, class T>
void BinaryTree<U, T> ::Thread(const string order)
{
	if (!this->root)
	{
		throw NoneValue(7, __FILE__, __LINE__);
	}
	Sequence<BinaryTreeNode<U, T>*>* seq = new ListSequence<BinaryTreeNode<U, T>*>();
	ThreadRecursive(this->root, seq, order);
	this->thread = seq;
}

template <class U, class T>
T BinaryTree<U, T> ::Reduce(T(*rfun)(T, T), const T& startvalue, const string order) const
{
	BinaryTree<U, T>* btree = new BinaryTree<U, T>(*this);
	btree->Thread(order);
	int i = 0;
	while (i < btree->thread->GetLength())
	{
		startvalue = rfun(btree->thread->Get(i)->GetTreeNode().data, startvalue);
		i++;
	}
	delete btree;
	return startvalue;
}


//template <class U, class T>
//Sequence<BinaryTreeNode<U, T>*>* BinaryTree<U, T> :: ConvertToSequence(const string order) const {
//	BinaryTree<U, T>* btree = new BinaryTree<U, T>(*this);
//	btree->Thread(order);
//	ListSequence<BinaryTreeNode<U, T>*>* list;
//	list = static_cast<ListSequence<BinaryTreeNode<U, T>*>*>(btree->GetThread());
//	Sequence<BinaryTreeNode<U, T>*>* seq = new ListSequence<BinaryTreeNode<U, T>*>(*list);
//	delete btree;
//	return seq;
//}




template <class U, class T>
BinaryTreeNode<U, T>* BinaryTree<U, T>::GetParent(BinaryTreeNode<U, T>* child, BinaryTreeNode<U, T>* start, string& place)
{
	if (!child || !start)
	{
		return nullptr;
	}
	if (!start->GetLeft() && !start->GetRight())
	{
		return nullptr;
	}
	if (start->GetLeft())
	{
		if (start->GetLeft()->GetTreeNode().key == child->GetTreeNode().key)
		{
			place = "left";
			return start;
		};
		BinaryTreeNode<U, T>* left = GetParent(child, start->GetLeft(), place);
		if (left)
		{
			return left;
		}
	};
	if (start->GetRight())
	{
		if (start->GetRight()->GetTreeNode().key == child->GetTreeNode().key)
		{
			place = "right";
			return start;
		};
		BinaryTreeNode<U, T>* right = GetParent(child, start->GetRight(), place);
		if (right)
		{
			return right;
		}
	};
	return nullptr;
}


template <class U, class T>
BinaryTreeNode<U, T>* BinaryTree<U, T>::MapRecursive(BinaryTreeNode<U, T>* node, BinaryTreeNode<U, T>* (*mfun)(BinaryTreeNode<U, T>*))
{
	string order = "NLR";
	BinaryTreeNode<U, T>* new_node = nullptr;
	if (!node)
	{
		return nullptr;
	}
	for (int i = 0; i < order.size(); i++)
	{
		switch (order[i])
		{
		case 'N':
			new_node = mfun(node);
			break;
		case 'L':
			new_node->SetLeft(MapRecursive(node->GetLeft(), mfun));
			break;
		case 'R':
			new_node->SetRight(MapRecursive(node->GetRight(), mfun));
			break;
		default:
			throw OperationError(0, __FILE__, __LINE__);
		}
	}
	return new_node;
}


template <class U, class T>
void BinaryTree<U, T>::WhereRecursive(BinaryTreeNode<U, T>* node, BinaryTree<U, T>* result, bool (*wfun)(BinaryTreeNode<U, T>*))
{
	string order = "NLR";
	if (!node)
	{
		return;
	}
	for (int i = 0; i < order.size(); i++)
		switch (order[i]) {
		case 'N':
			if (wfun(node)) {
				BinaryTreeNode<U, T>* new_node = new BinaryTreeNode<U, T>(node->GetTreeNode().key, node->GetTreeNode().data);
				result->Insert(new_node);
			};
			break;
		case 'L':
			WhereRecursive(node->GetLeft(), result, wfun);
			break;
		case 'R':
			WhereRecursive(node->GetRight(), result, wfun);
			break;
		default:
			throw OperationError(0, __FILE__, __LINE__);
		}
}


template <class U, class T>
void BinaryTree<U, T>::ThreadRecursive(BinaryTreeNode<U, T>* node, Sequence<BinaryTreeNode<U, T>*>* seq, const string order) {
	if (!node)
		return;
	for (int i = 0; i < order.size(); i++)
	{
		switch (order[i])
		{
		case 'N':
			seq->Append(node);
			break;
		case 'L':
			ThreadRecursive(node->GetLeft(), seq, order);
			break;
		case 'R':
			ThreadRecursive(node->GetRight(), seq, order);
			break;
		default:
			throw OperationError(0, __FILE__, __LINE__);
		}
	}
}


template <class U, class T>
void BinaryTree<U, T>::InsertRecursive(BinaryTreeNode<U, T>* node, BinaryTreeNode<U, T>* start)
{
	if (!node || !start)
	{
		return;
	}
	if (start->GetTreeNode().key >= node->GetTreeNode().key)
	{
		if (!start->GetLeft())
		{
			start->SetLeft(node);
		}
		else
		{
			InsertRecursive(node, start->GetLeft());
		}
	};
	if (start->GetTreeNode().key < node->GetTreeNode().key)
	{
		if (!start->GetRight())
		{
			start->SetRight(node);
		}
		else
		{
			InsertRecursive(node, start->GetRight());
		}
	}
}

