#include "Red-Black-Tree.h"
#include <stdexcept>


template <typename T, typename T2 >
RBTree<T, T2>::RBTree()
{
	reset_list();
	size = 0;
}

template <typename T, typename T2 >
RBTree<T, T2>::~RBTree()
{
	clear();
	/*	if (root != nullptr)
		{
			root->Del();
			if (root->next_left != nullptr)
				root->next_left = nullptr;
			if (root->next_right != nullptr)
				root->next_right = nullptr;
			root = nullptr;
		}*/
}

template <typename T, typename T2 >
void RBTree<T, T2> :: add_first(node *current)
{
	root = current;
	root->parent = nullptr;
}

template <typename T, typename T2 >
void RBTree<T, T2>::remove(T key)
{
	if (this->root == nullptr)
	{
		throw out_of_range("SOS! Dangerous! Error");
	}

	node *current;
	current = root;
	node *parent_of_leaf = NULL;
	node *leaf = NULL;
	int flag = 0;
	while (current != NULL && flag == 0)
	{
		if (current->key == key)
			flag = 1;
		if (flag == 0)
		{
			if (current->key < key)
				current = current->right;
			else
				current = current->left;
		}
	}
	if (flag == 0)
	{
		throw out_of_range("error");
	}
	else
	{
		if (current->left == nullptr || current->right == nullptr)
			parent_of_leaf = current;
		else
			parent_of_leaf = get_leaf(current);
		if (parent_of_leaf->left != nullptr)
			leaf = parent_of_leaf->left;
		else
		{
			if (parent_of_leaf->right != nullptr)
				leaf = parent_of_leaf->right;
			else
				leaf = nullptr;
		}
		if (leaf != nullptr)
			leaf->parent = parent_of_leaf->parent;
		if (parent_of_leaf->parent == nullptr)
			root = leaf;
		else
		{
			if (parent_of_leaf == parent_of_leaf->parent->left)
				parent_of_leaf->parent->left = leaf;
			else
				parent_of_leaf->parent->right = leaf;
		}
		if (parent_of_leaf != current)
		{
			current->color = parent_of_leaf->color;
			current->key = parent_of_leaf->key;
		}
		if (parent_of_leaf->color == 'b')
			delfix(leaf);
	}
	size--;
}

template <typename T, typename T2 >
void RBTree<T, T2>::delfix(node *current)
{
	node *temp_elem;
	while (current != root && current->color == 'b')
	{
		if (current->parent->left == current)
		{
			temp_elem = current->parent->right;
			if (temp_elem->color == 'r')
			{
				temp_elem->color = 'b';
				current->parent->color = 'r';
				leftrotate(current->parent);
				temp_elem = current->parent->right;
			}
			if (temp_elem->right->color == 'b' && temp_elem->left->color == 'b')
			{
				temp_elem->color = 'r';
				current = current->parent;
			}
			else
			{
				if (temp_elem->right->color == 'b')
				{
					temp_elem->left->color = 'b';
					temp_elem->color = 'r';
					rightrotate(temp_elem);
					temp_elem = current->parent->right;
				}
				temp_elem->color = current->parent->color;
				current->parent->color = 'b';
				temp_elem->right->color = 'b';
				leftrotate(current->parent);
				current = root;
			}
		}
		else
		{
			temp_elem = current->parent->left;
			if (temp_elem->color == 'r')
			{
				temp_elem->color = 'b';
				current->parent->color = 'r';
				rightrotate(current->parent);
				temp_elem = current->parent->left;
			}
			if (temp_elem->left->color == 'b'&&temp_elem->right->color == 'b')
			{
				temp_elem->color = 'r';
				current = current->parent;
			}
			else
			{
				if (temp_elem->left->color == 'b')
				{
					temp_elem->right->color = 'b';
					temp_elem->color = 'r';
					leftrotate(temp_elem);
					temp_elem = current->parent->left;
				}
				temp_elem->color = current->parent->color;
				current->parent->color = 'b';
				temp_elem->left->color = 'b';
				rightrotate(current->parent);
				current = root;
			}
		}
		current->color = 'b';
		root->color = 'b';
	}
}

template <typename T, typename T2 >
void RBTree<T, T2>::find(T key)
{
	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}

	auto it = create_bft_iterator();
	for (; it != nullptr; it++)
	{
		if (it.current_key() == key) cout << it.current_key();
	}
	
}

template <typename T, typename T2 >
void RBTree<T, T2>::get_keys()
{

	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}
	
	auto it = create_bft_iterator();
	for (; it != nullptr; it++)
	{
		cout << it.current_key() << ' ';
	}
	cout << '\n';
	auto it1 = create_bft_iterator();
	for (; it1 != nullptr; it1++)
	{
		cout << it1.current_color() << ' ';
	}

	cout << '\n';
}

template <typename T, typename T2 >
void RBTree<T, T2>::get_value()
{
	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}
	auto it1 = create_bft_iterator();
	for (; it1 != nullptr; it1++)
		cout <<it1.current_value() << ' ';
	cout << '\n';
}


template <typename T, typename T2 >
int RBTree<T, T2>::get_size() {
	return size;
}

template <typename T, typename T2 >
void RBTree<T, T2>::clear()                   //clear of RED-BLACK-TREE
{
	while (size > 0)
	remove(root->key);

	if (size == 0) cout << "RBTree is empty\n";
}

template <typename T, typename T2 >
void RBTree<T, T2>::reset_list()
{
	root = nullptr;
}

template <typename T, typename T2 >
typename RBTree<T, T2>::node * RBTree<T, T2>::get_leaf(node *current)      
{
	node *leaf = NULL;
	if (current->left != NULL)
	{
		leaf = current->left;
		while (leaf->right != NULL)
			leaf = leaf->right;
	}
	else
	{
		leaf = current->right;
		while (leaf->left != NULL)
			leaf = leaf->left;
	}
	return leaf;
}

template <typename T, typename T2 >
void RBTree<T, T2>::insert(T key, T2 value) {

	node *help_elem, *prev;
	node *current = new node(key, value);
	help_elem = root;
	prev = nullptr;
	if (root == nullptr)
	{
		add_first(current);
	
	}
	else
	{
		while (help_elem != nullptr)
		{
			prev = help_elem;
			if (help_elem->key < current->key)
				help_elem = help_elem->right;
			else
				help_elem = help_elem->left;
		}	
		current->parent = prev;
		if (prev->key < current->key)
			prev->right = current;
		else
			prev->left = current;
	}

	insertfix(current);
	size++;
}

template <typename T, typename T2 >
void RBTree<T, T2>::insertfix(node *current) {
	
	node *uncle;
	if (root == current)
	{
		current->color = 'b';
		return;
	}
	
	while (current->parent != nullptr && current->parent->color == 'r')
	{
		node *grandparents = current->parent->parent;
		if (grandparents->left == current->parent)
		{
			if (grandparents->right != nullptr)
			{
				uncle = grandparents->right;
				if (uncle->color == 'r')
				{
					current->parent->color = 'b';
					uncle->color = 'b';
					grandparents->color = 'r';
					current = grandparents;
				}
			}
			else
			{
				if (current->parent->right == current)
				{
					current = current->parent;
					leftrotate(current);
				}
				current->parent->color = 'b';
				grandparents->color = 'r';
				rightrotate(grandparents);
			}
		}
		else
		{
			if (grandparents->left != nullptr)
			{
				uncle = grandparents->left;
				if (uncle->color == 'r')
				{
					current->parent->color = 'b';
					uncle->color = 'b';
					grandparents->color = 'r';
					current = grandparents;
				}
			}
			else
			{
				if (current->parent->left == current)
				{
					current = current->parent;
					rightrotate(current);
				}
				current->parent->color = 'b';
				grandparents->color = 'r';
				leftrotate(grandparents);
			}
		}
		root->color = 'b';
	}

}

template <typename T, typename T2 >
void RBTree<T, T2>::leftrotate(node *current)
{
	if (current->right == nullptr)
		return;
	else
	{
		node *y = current->right;
		if (y->left != nullptr)
		{
			current->right = y->left;
			y->left->parent = current;
		}
		else
			current->right = nullptr;
		if (current->parent != nullptr)
			y->parent = current->parent;
		if (current->parent == nullptr)
			root = y;
		else
		{
			if (current == current->parent->left)
				current->parent->left = y;
			else
				current->parent->right = y;
		}
		y->left = current;
		current->parent = y;
	}
}

template <typename T, typename T2 >
void RBTree<T, T2>::rightrotate(node *current)
{
	if (current->left == nullptr)
		return;
	else
	{
		node *child = current->left;
		if (child->right != nullptr)
		{
			current->left = child->right;
			child->right->parent = current;
		}
		else
			current->left = nullptr;
		if (current->parent != nullptr)
			child->parent = current->parent;
		if (current->parent == nullptr)
			root = child;
		else
		{
			if (current == current->parent->left)
				current->parent->left = child;
			else
				current->parent->right = child;
		}
		child->right = current;
		current->parent = child;
	}
}

/*template <typename T>
typename RBTree<T>::node* RBTree<T>::get_uncle(node *cur) {
	node *granny = get_grandparent(cur);
	if (granny == nullptr)
		return nullptr; // No grandparent means no uncle
	if (cur->parent == granny->next_left)
		return granny->next_right;
	else
		return granny->next_left;
}
template <typename T>
typename RBTree<T>::node* RBTree<T>::get_grandparent(node *cur) {
	if ((cur != nullptr) && (cur->parent != nullptr))
		return cur->parent->parent;
	else
		return nullptr;
}
template<typename T>
typename RBTree<T>::node * RBTree<T>::get_sibling(node *current)
{
	if (current == current->parent->next_left)
		return current->parent->next_right;
	else
		return current->parent->next_left;
}
*/

/*
template<typename T>
void RBTree<T>::node::Del()
{
	if (this != nullptr) {
		this->next_left->Del();
		this->next_right->Del();
		free(this);
	}
}
*/
