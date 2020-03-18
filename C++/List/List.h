#pragma once
#include <iostream>

template<class T>
struct Node
{
	T data = {};
	Node<T>* next = nullptr;
	Node<T>* prev = nullptr;

	Node(T value, Node<T>* next_ptr = nullptr, Node<T>* prev_ptr = nullptr)
		: data{ value }, next{ next_ptr }, prev{ prev_ptr } {};
};

template <class Item>
class List
{
public:
	
	List() {};
	
	void push_front(Item item)
	{
		head = new Node<Item>{ item, head, nullptr };
		if (!back)
		{
			back = head;
		}
		else
		{
			head->next->prev = head;
		}
	}
	void push_back(Item item) 
	{
		back = new Node<Item>{ item, nullptr, back };
		back->prev->next = back;
		if (!head)
		{
			head = back;
		}
	}

	void push_after(const Item& item, const Item& value)
	{
		if (Node<Item>* iter = find(value))
		{
			auto t = new Node<Item>{ item, iter->next, iter };
			
			iter->next = t;
			t->next->prev = t;
		}
	}
	void push_before(const Item& item, const Item& value)
	{
		if (Node<Item>* iter = find(value))
		{
			auto t = new Node<Item>{item, iter, iter->prev};

			iter->prev = t;
			t->prev->next = t;
		}
	}

	void pop_front()
	{
		if (head)
		{
			Node<Item> *t = head;
			
			if (head == back)
			{
				back = nullptr;
			}
			else
			{
				head = head->next;
				head->prev = nullptr;
			}
			
			delete	t;
		}
	}
	void pop_back()
	{
		if (back)
		{
			Node<Item> *t = back;

			if (head == back)
			{
				head = nullptr;
			}
			else
			{
				back = back->prev;
				back->next = nullptr;
			}

			delete t;
		}
	}
	void remove(const Item& item)
	{
		if (Node<Item>* t = find(item))
		{
			if (t->next)
			{
				t->next->prev = t->prev;
			}

			if (t->prev)
			{
				t->prev->next = t->next;
			}

			delete t;
		}
	}

	Item get_front() const
	{
		return head->data;
	}
	Item get_back() const
	{
		return back->data;
	}

	int empty() const
	{
		return head == nullptr;
	}
	
	Node<Item>* find(const Item& item)
	{
		for (Node<Item>* iter = head; iter; iter = iter->next)
		{
			if (iter->data == item)
			{
				return iter;
			}
		}
		
		return nullptr;
	}
	Node<Item>* begin() const
	{
		return head;
	}
	Node<Item>* end() const 
	{
		return back;
	}

private:

	Node<Item>* head = nullptr;
	Node<Item>* back = nullptr;
};