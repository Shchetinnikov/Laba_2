#pragma once

#include "Exception.h"

/*

	Узел бинарного дерева поиска

*/


template <class U, class T>
struct TreeNode 
{
	U key;
	T data;
};

template <class U, class T>
class BinaryTreeNode 
{
private:
	TreeNode<U, T> item;
	BinaryTreeNode<U, T>* left;
	BinaryTreeNode<U, T>* right;
public:
	BinaryTreeNode(const U& key);
	BinaryTreeNode(const U& key, const T& data);
	BinaryTreeNode(const U& key, const T& data, BinaryTreeNode<U, T>* left, BinaryTreeNode<U, T>* right);
public:
	TreeNode<U, T> GetTreeNode() const { return this->item; };
	BinaryTreeNode<U, T>* GetLeft() const { return this->left; };
	BinaryTreeNode<U, T>* GetRight() const { return this->right; };
public:
	// содержимое узла не изменяется
	void SetLeft(BinaryTreeNode<U, T>* left);
	void SetRight(BinaryTreeNode<U, T>* right);
};


/*
	Нет проверки уникальности ключей
*/

template<class U, class T>
BinaryTreeNode<U, T> ::BinaryTreeNode(const U& key) : left(nullptr), right(nullptr)
{
	this->item.key = key;
}


template <class U, class T>
BinaryTreeNode<U, T> ::BinaryTreeNode(const U& key, const T& data) : left(nullptr), right(nullptr)
{
	this->item.key = key;
	this->item.data = data;
}


template <class U, class T>
BinaryTreeNode<U, T> ::BinaryTreeNode(const U& key, const T& data, BinaryTreeNode<U, T>* left, BinaryTreeNode<U, T>* right)
{
	this->item.key = key;
	this->item.data = data;
	this->left = left;
	this->right = right;
}


template <class U, class T>
void BinaryTreeNode<U, T> ::SetLeft(BinaryTreeNode<U, T>* left)
{
	if (!left)
	{
		this->left = nullptr;
		return;
	};
	this->left = new BinaryTreeNode<U, T>(left->item.key, left->item.data, left->left, left->right);
};


template <class U, class T>
void BinaryTreeNode<U, T> ::SetRight(BinaryTreeNode<U, T>* right)
{
	if (!right)
	{
		this->right = nullptr;
		return;
	};
	this->right = new BinaryTreeNode<U, T>(right->item.key, right->item.data, right->left, right->right);
};



template<class U, class T>
void DeleteNode(BinaryTreeNode<U, T>* node) { delete node; };


template<class U, class T>
BinaryTreeNode<U, T>* CopyNode(BinaryTreeNode<U, T>* node)
{
	BinaryTreeNode<U, T>* new_node = new BinaryTreeNode<U, T>(node->GetTreeNode().key, node->GetTreeNode().data,
		node->GetLeft(), node->GetRight());
	return new_node;
}


template<class U, class T>
ostream& operator<<(ostream& stream, const BinaryTreeNode<U, T>& node)
{
	stream << "{ " << node.GetTreeNode().key << ", " << node.GetTreeNode().data << " }" << endl;
	return stream;
}
