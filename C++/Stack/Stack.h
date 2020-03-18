
template <class T>
struct Node
{
	T data;
	Node<T>* next;

	Node(T val, Node<T>* t)
		: data{ val }, next{ t } {}
};

template <class Item>
class Stack
{
public:
	
	Stack()
	{
		head = nullptr;
		_size = 0;
	}

	void push(const Item& item)
	{
		head = new Node<Item>{ item, head};
		_size++;
	}

	Item pop()
	{
		_size--;

		Item item = head->data;
		Node<Item>* tmp = head->next;

		delete head;
		head = tmp;

		return item;
	}

	bool empty() const
	{
		return head == nullptr;
	}

private:
	
	int _size;
	Node<Item>* head;

};
