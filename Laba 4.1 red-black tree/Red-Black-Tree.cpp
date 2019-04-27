#include "Red-Black-Tree.h"
#include <stdexcept>


template <typename T >
map<T>::map()
{
	reset_list();
	size = 0;
}

template <typename T>
map<T>::~map()
{
	clear();
}
template <typename T >
void map<T>::add_first(T key)
{

	root = new node(key);
	root->parent = nullptr;
	size++;
}
template <typename T>
void map<T>::remove(T key)
{
	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}

	node *current;
	current = root;
	node *successor = nullptr;
	node *temp = nullptr;
	int found = 0;
	while (current != nullptr && found == 0)
	{
		if (current->key == key)
			found = 1;
		if (found == 0)
		{
			if (current->key < key)
				current = current->next_right;
			else
				current = current->next_left;
		}
	}
	if (found == 0)
	{
		throw out_of_range("no this element");
	}
	else
	{
		if (current->next_left == nullptr || current->next_right == nullptr)
			successor = current;
		else
			successor = get_successor(current);
		if (successor->next_left != nullptr)
			temp = successor->next_left;
		else
		{
			if (successor->next_right != nullptr)
				temp = successor->next_right;
			else
				temp = nullptr;
		}
		if (temp != nullptr)
			temp->parent = successor->parent;
		if (successor->parent == nullptr)
			root = temp;
		else
		{
			if (successor == successor->parent->next_left)
				successor->parent->next_left = temp;
			else
				successor->parent->next_right = temp;
		}
		if (successor != current)
		{
			current->color = successor->color;
			current->key = successor->key;
			current->frequancy = successor->frequancy;
		}
		if (temp != nullptr)
			if (successor->color == 0)
				delfix(temp);
	}
	size--;
}
template <typename T >
void map<T>::delfix(node *fixable)
{
	node *sibling;
	while (fixable != root && fixable->color == 0)
	{
		if (fixable->parent->next_left == fixable)
		{
			sibling = fixable->parent->next_right;
			if (sibling->color == 1)
			{
				sibling->color = 0;
				fixable->parent->color = 1;
				leftrotate(fixable->parent);
				sibling = fixable->parent->next_right;
			}
			if (sibling->next_right->color == 0 && sibling->next_left->color == 0)
			{
				sibling->color = 1;
				fixable = fixable->parent;
			}
			else
			{
				if (sibling->next_right->color == 0)
				{
					sibling->next_left->color == 0;
					sibling->color = 1;
					rightrotate(sibling);
					sibling = fixable->parent->next_right;
				}
				sibling->color = fixable->parent->color;
				fixable->parent->color = 0;
				sibling->next_right->color = 0;
				leftrotate(fixable->parent);
				fixable = root;
			}
		}
		else
		{
			sibling = fixable->parent->next_left;
			if (sibling->color == 1)
			{
				sibling->color = 0;
				fixable->parent->color = 1;
				rightrotate(fixable->parent);
				sibling = fixable->parent->next_left;
			}
			if (sibling->next_left->color == 0 && sibling->next_right->color == 0)
			{
				sibling->color = 1;
				fixable = fixable->parent;
			}
			else
			{
				if (sibling->next_left->color == 0)
				{
					sibling->next_right->color = 0;
					sibling->color = 1;
					leftrotate(sibling);
					sibling = fixable->parent->next_left;
				}
				sibling->color = fixable->parent->color;
				fixable->parent->color = 0;
				sibling->next_left->color = 0;
				rightrotate(fixable->parent);
				fixable = root;
			}
		}
		fixable->color = 0;
		root->color = 0;
	}
}
template<typename T>
typename map<T>::node * map<T>::find(T key)
{
	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}

	auto it = create_bft_iterator();
	for (; it != nullptr; it++)
		if (it.current_key() == key) return it.get_cur();
	throw out_of_range("error");
}

template<typename T>
List<T> map<T>::get_keys()
{
	List <T> list;
	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}
	auto it = create_bft_iterator();
	for (; it != nullptr; it++)
		list.push_back(it.current_key(), *it);
	return list;
}

template <typename T >
void map<T>::get_value()
{
	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}
	auto it = create_bft_iterator();
	for (; it != nullptr; it++)
		cout << *it << '-' << it.current_key() << ' ' << it.current_color() << ' ';
	cout << '\n';


}

template <typename T>
void map<T>::clear()
{
	while (size > 0)
		remove(root->key);
}

template <typename T>
void map<T>::reset_list()
{
	//	cur = nullptr;
	root = nullptr;
}

template <typename T>
typename map<T>::node * map<T>::get_successor(node *current) //получение наследника
{
	node *successor = nullptr;
	if (current->next_left != nullptr)
	{
		successor = current->next_left;
		while (successor->next_right != nullptr)
			successor = successor->next_right;
	}
	else
	{
		successor = current->next_right;
		while (successor->next_left != nullptr)
			successor = successor->next_left;
	}
	return successor;
}

template <typename T>
void map<T>::insert(T key)
{

	node* temp, *prev;
	node* current = new node(key);
	temp = root;
	prev = nullptr;
	if (root == nullptr)
	{
		root = current;
		current->parent = nullptr;
		current->frequancy++;
	}
	else
	{
		while (temp != nullptr)
		{
			if (temp->key == current->key) break;
			prev = temp;
			if (temp->key < current->key)
				temp = temp->next_right;
			else
				temp = temp->next_left;
		}

		if ((temp != nullptr) && (temp->key == current->key)) {
			temp->frequancy++;
			return;
		}
		else
		{
			current->parent = prev;
			if (prev->key < current->key)
				prev->next_right = current;
			else
				prev->next_left = current;
			current->frequancy++;
		}
	}

	insertfix(current);
	size++;
}

template <typename T >
void map<T>::insertfix(node *&current) {
	
	node* parent = nullptr;
	node* grandparent = nullptr;
	while (current != root && current->color == 1 && current->parent->color == 1) {
		parent = current->parent;
		grandparent = parent->parent;
		if (parent == grandparent->next_left) {
			node* uncle = grandparent->next_right;
			if (uncle != nullptr && uncle->color == 1) {
				uncle->color = 0;
				parent->color = 0;
				grandparent->color = 1;
				current = grandparent;
			}
			else {
				if (current == parent->next_right) {
					leftrotate(parent);
					current = parent;
					parent = current->parent;
				}
				rightrotate(grandparent);
				swap(parent->color, grandparent->color);
				current = parent;
			}
		}
		else {
			node* uncle = grandparent->next_left;
			if (uncle != nullptr && uncle->color == 1) {
				uncle->color = 0;
				parent->color = 0;
				grandparent->color = 1;
				current = grandparent;
			}
			else {
				if (current == parent->next_left) {
					rightrotate(parent);
					current = parent;
					parent = current->parent;
				}
				leftrotate(grandparent);
				swap(parent->color, grandparent->color);
				current = parent;
			}
		}
	}
	root->color = 0;
}

template <typename T >
void map<T>::leftrotate(node *current)
{
	node* right_child = current->next_right;
	current->next_right = right_child->next_left;

	if (current->next_right != nullptr)
		current->next_right->parent = current;

	right_child->parent = current->parent;

	if (current->parent == nullptr)
		root = right_child;
	else if (current == current->parent->next_left)
		current->parent->next_left = right_child;
	else
		current->parent->next_right = right_child;

	right_child->next_left = current;
	current->parent = right_child;
}

template <typename T >
void map<T>::rightrotate(node * current)
{
	node* left_child = current->next_left;
	current->next_left = left_child->next_right;

	if (current->next_left != nullptr)
		current->next_left->parent = current;

	left_child->parent = current->parent;

	if (current->parent == nullptr)
		root = left_child;
	else if (current == current->parent->next_left)
		current->parent->next_left = left_child;
	else
		current->parent->next_right = left_child;

	left_child->next_right = current;
	current->parent = left_child;
}

