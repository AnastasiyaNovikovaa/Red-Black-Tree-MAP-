#pragma once
#include <iostream>
#include "Iterator.h"

using namespace std;


template <class item> class queue
{
	item* Queue; int head, tail, size_, Max;
public:
	queue(int maxQ) : head(0), tail(0), Max(maxQ), size_(0), Queue(new item[maxQ + 1]) {}
	~queue();
	bool empty() const { return (head % Max) == tail; }
	int size() const { return size_; }
	void push(item& item) { Queue[tail++] = item; tail %= Max; ++size_; }
	item front() const { return Queue[head % Max]; }
	void pop() { head++; head %= Max; --size_; }
};

template <class item>
queue<item>::~queue()
{
	free(Queue);
}

template <typename T, typename T2 >
class Map
{
	private:

	class node
	{

	public:
		node(T key, T2 data, node * left = nullptr, node * right = nullptr) {
			this->data = data;
			this->left = left;
			this->right = right;
			this->key = key;
			this->parent = nullptr;
			this->color = 'r';

		};
		char color;
		T key, data;
		node * right;
		node *left;
		node *parent;
	};

	node * root;
	size_t size;
	
  public:
		Map();
		~Map();
	
	class TreeIterator : public Iterator<T, T2> {
	protected:
		node *current;
		TreeIterator(node* root) : current(root) { }

	public:
		bool operator==(const nullptr_t) const override { return current == nullptr; }
		bool operator!=(const nullptr_t) const override { return !operator==(nullptr); }
		T2 operator*() const override { return current->data; }
		T current_key() { return current->key; }
		T2 current_value() { return current->data; }
		char current_color() { return current->color; }

	};

	class BftIterator : public TreeIterator {
	private:
		queue<node*> nodes;
	public:
		BftIterator(node *root, size_t size) : TreeIterator(root), nodes(size) {}
		void operator++(T) override;
	};
private:
	void insertfix(node *t);      //supporting function for insert
	void leftrotate(node *);
	void rightrotate(node *);
	void reset_list();
	node *get_leaf(node *);       //supporting function for remove
	void add_first(node*);        //adding the first element to the tree
	void delfix(node*);           //supporting function for remove, balance
    
  public:
	void get_keys();
	void get_value();
	void clear();                 //clearing the tree
	void insert(T, T2);           //insert element in the tree
	void remove(T);               //removing element by key
	int get_size();               //getting size of the tree
	int find(T);                 //finding element by key
	bool Find(T key, T2*& value);
	BftIterator create_bft_iterator() { return BftIterator(root, size); }
	
	
};


template<typename T, typename T2>
void Map<T, T2>::BftIterator::operator++(T)
{
	if (this->current->left != nullptr)
		nodes.push(this->current->left);
	if (this->current->right != nullptr)
		nodes.push(this->current->right);
	if (nodes.size() > 0) {
		this->current = nodes.front();
		nodes.pop();
	}
	else
		this->current = nullptr;
}
