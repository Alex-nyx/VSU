#include <iostream>
#include "List.h"

using namespace std;

template<class T>
void print(const List<T>&);

template <class T>
void reverse_print(const List<T>&);

int main()
{
	List<int> list;

	if (!list.empty())
	{
		cout << "front item: " << list.get_front() << endl << "back item: " << list.get_back() << endl << endl;
	}

	//test push_front
	cout << "push_front: 0-9 \n";
	for (int i = 0; i < 10; i++)
	{
		list.push_front(i);
	}
	print(list);
	
	if (!list.empty())
	{
		cout << "front item: " << list.get_front() << endl << "back item: " << list.get_back() << endl << endl;
	}

	//test push_back
	cout  << "push_back: 10-19 \n";
	for (int i = 10; i < 20; i++)
	{
		list.push_back(i);
	}
	print(list);

	if (!list.empty())
	{
		cout << "front item: " << list.get_front() << endl << "back item: " << list.get_back() << endl << endl;
	}

	//test pop_back and push_back
	while (list.get_back() != 15)
	{
		cout << "pop_back : \n";
		list.pop_back();
		print(list);
		
		if (list.get_back() != 0)
		{
			cout << "pop_front : \n";
			list.pop_front();
			print(list);
		}
	}

	cout << "\npush 500 after 0 :" << endl;
	list.push_after(500, 0);
	print(list);
	
	cout << "\npush 500 before 0 :" << endl;
	list.push_before(500, 0);
	print(list);

	cout << "\nremove 500 :" << endl;
	list.remove(500);
	print(list);

	cout << "\nremove 500 :" << endl;
	list.remove(500);
	print(list);

	cout << "\nremove 10 :" << endl;
	list.remove(10);
	print(list);

	cin.get();
}

template <class T>
void print(const List<T>& list)
{
	for (auto iter = list.begin(); iter != nullptr; iter = iter->next)
	{
		cout << iter->data << "; ";
	}
	cout << endl;
}

template <class T>
void reverse_print(const List<T>& list)
{
	for (auto iter = list.end(); iter; iter = iter->prev)
	{
		cout << iter->data << "; ";
	}
	cout << endl;
}
