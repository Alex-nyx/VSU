#include <iostream>
#include "Mouse_list.h"

using namespace std;

bool check_initial_conditions(int, int, int, int, int);

int main()
{
	int N, M, S, K, L;
	
	cout << "Test input? (y/n): ";

	if (cin.get() == 'y')
	{
		N = 5; M = 4; S = 3; K = 2; L = 1;
		cout << "N: " << N << " ";
		cout << "M: " << M << " ";
		cout << "S: " << S << " ";
		cout << "K: " << K << " ";
		cout << "L: " << L << endl;
		cout << endl;
	}
	else
	{
		cout << "N: "; cin >> N;
		cout << "M: "; cin >> M;
		cout << "S: "; cin >> S;
		cout << "K: "; cin >> K;
		cout << "L: "; cin >> L;
		cout << endl;

	}

	if (!check_initial_conditions(N, M, S, K, L))
	{
		cout << "Initial conditions is not correct!\nPress any key...";
		cin.get();
		cin.get();
		return 0;
	}

	/*
		Cчет с серой мыши => wlog первая.цвет = серая
	*/	

	int diff = N+M-K-L;
	
	Node* mice = nullptr;
	mice = create_list(M + N);
	print_list(mice);
		
	mice->color = Color::Grey;
	print_list(mice);
	
	cout << "mice after cat: \n";
	cat_eat_mice(mice, S, diff);
	print_list(mice);
	
	cout << "mice after cat (colored): \n";
	set_color_for_survivors(mice, K, L);
	print_list(mice);

	cout << "mice before cat: \n";
	if (!set_color_for_other(mice, S, N - K, M - L))
	{
		cout << "Initial conditions is not correct!\nPress any key...";
		cin.get();
		cin.get();
		list_free(mice);
		return 0;
	}
	print_list(mice);

	cout << "Check: \n";
	cat_eat_mice(mice, S, diff);
	print_list(mice);
	
	cout << "number of grey: " << list_number_grey(mice) << endl;
	cout << "number of white: " << list_number_white(mice) << endl;

	cin.get();
	cin.get();

	list_free(mice);
}

bool check_initial_conditions(int N, int M, int S, int K, int L)
{
	bool all_positive;
	bool correct_number_of_mice;

	if (N > 0 && M > 0 && S > 0 && K > 0 && L > 0)
	{
		all_positive = true;
	}
	else
	{
		all_positive = false;
	}

	if (N >= K && M >= L)
	{
		correct_number_of_mice = true;
	}
	else
	{
		correct_number_of_mice = false;
	}

	if (all_positive &&  correct_number_of_mice)
	{
		return true;
	}
	else
	{
		cout << "all_positive: " << all_positive << endl;
		cout << "correct_number_of_mice: " << correct_number_of_mice << endl;
		
		return false;
	}
}