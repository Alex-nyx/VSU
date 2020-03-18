#pragma once
#include <iostream>

enum class Color { NotCol = 0, White = 1, Grey = 2 };


struct Node
{
	Color color;
	bool deleted;

	Node* next = nullptr;
	Node* prev = nullptr;

	Node(Node* next_ptr = nullptr, Node* prev_ptr = nullptr)
		: color{ Color::NotCol }, deleted{ false }, next{ next_ptr }, prev{ prev_ptr } {};
};

std::ostream& operator<<(std::ostream &out, Node node)
{
	switch (node.color)
	{
	case Color::Grey:
		out << "G ";
		break;
	case Color::White:
		out << "W ";
		break;
	case Color::NotCol:
		out << "WihoutColor ";
		break;
	default:
		out << "\n\tError with color\n";
		break;
	}
	return out;
}

Node* insert(Node* list)
{
	if (list == nullptr)
	{
		list = new Node;
		list->prev = list;
		list->next = list;

	}
	else
	{
		Node* node = new Node{list->next, list};
		node->next->prev = node;
		node->prev->next = node;
	}
	return list;
}

Node* create_list(unsigned int size)
{
	Node* list = nullptr;

	while (size--)
	{
		list = insert(list);
	}

	return list;
}

int list_size(Node* list)
{
	if (list == nullptr)
	{
		return 0;
	}
	else
	{
		Node* iter = list->next;
		int counter = 1;

		while (iter != list)
		{
			++counter;
			iter = iter->next;
		}

		return counter;
	}
}
int list_size_colored(Node* list)
{
	if (list == nullptr)
	{
		return 0;
	}
	else
	{
		Node* iter = list->next;
		int counter = 1;

		while (iter != list)
		{
			if (iter->deleted == false)
			{
				++counter;
			}
			iter = iter->next;
		}

		return counter;
	}
}
int list_number_grey(Node* list)
{
	if (list == nullptr)
	{
		return 0;
	}
	else
	{
		Node* iter = list;
		int counter = 0;

		do {
			if (iter->deleted == false && iter->color == Color::Grey)
			{
				++counter;
			}
			iter = iter->next;
		} while (iter != list);

		return counter;
	}
}
int list_number_white(Node* list)
{
	if (list == nullptr)
	{
		return 0;
	}
	else
	{
		Node* iter = list;
		int counter = 0;

		do {
			if (iter->deleted == false && iter->color == Color::White)
			{
				++counter;
			}
			iter = iter->next;
		} while (iter != list);

		return counter;
	}
}

void list_free(Node* list)
{
	while (list != nullptr)
	{
		if (list->next == list)
		{
			delete list;
			return;
		}
		else 
		{
			list->next->prev = list->prev;
			list->prev->next = list->next;

			Node* next = list->next;
			delete list;
			list = next;
		}
	}
}

void print_list(Node* list)
{
	if (list != nullptr)
	{
		Node* iter = list;

		std::cout << "<";
		do
		{
			if (iter->deleted == false)
			{
				std::cout << *iter;
			}
			iter = iter->next;
		} while (iter != list);

		std::cout << ">" << std::endl << std::endl;
	}
	else
	{
		std::cout << "\n\t PRINT: Null pointer\n\n";
	}
}

void cat_eat_mice(Node* list, int S, int N)
{
	/*
		S - шаг поедания
		N - Кол-во съеденных мышей
	*/
		
	Node* iter = list;
	
	while (N--)
	{
		int i = 1;
		while (i < S)
		{
			if (iter->deleted == false)
			{
				++i;
			}
			iter = iter->next;
		}
		while (iter->deleted)
		{
			iter = iter->next;
		}

		iter->deleted = true;
		iter = iter->next;
	}
}

bool set_color_for_survivors(Node* list, int grey_num, int white_num)
{
	if (list == nullptr)
	{
		return false;
	}

	Node* iter = list;

	if (list->deleted == false)
	{
		--grey_num;
	}

	while ( white_num != 0)
	{
		if (iter->deleted == false && iter->color == Color::NotCol)
		{
			iter->color = Color::White;
			--white_num;

			iter = iter->next;
		}
		else
		{
			iter = iter->next;
		}

	}

	while (grey_num != 0)
	{
		if (iter->deleted == false && iter->color == Color::NotCol)
		{
			iter->color = Color::Grey;
			--grey_num;

			iter = iter->next;
		}
		else
		{
			iter = iter->next;
		}
	}
	return true;
}
bool set_color_for_other(Node* list, int S, int grey_num, int white_num)
{
	if (list == nullptr)
	{
		return false;
	}
		
	int init_num = list_size(list);
	int curr_col = list_size_colored(list);
	int curr_not_col = init_num - curr_col;

	if (grey_num + white_num != curr_not_col)
	{
		return false;
	}

	Node* iter = list;
	while (white_num != 0)
	{
		if (iter->deleted == true && iter->color == Color::NotCol)
		{
			iter->deleted = false;
			iter->color = Color::White;
			--white_num;

			iter = iter->next;
		}
		else
		{
			iter = iter->next;
		}

	}

	while (grey_num != 0)
	{
		if (iter->deleted == true && iter->color == Color::NotCol)
		{
			iter->deleted = false;
			iter->color = Color::Grey;
			--grey_num;

			iter = iter->next;
		}
		else
		{
			iter = iter->next;
		}
	}
	return true;
}