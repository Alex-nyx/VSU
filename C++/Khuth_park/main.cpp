#include <iostream>
#include <string>
#include <vector>

using namespace std;
using Parking = vector<int>;

void count_successful_seq(Parking&, int&, int, int);
bool try_parking(Parking&, int, int);
void remove_car(Parking&, int);

void test(int);
void test_1(int);
void print(Parking);
void print(int, int);

int main()
{
	int parking_size, number_of_car, number_of_successful_sequences = 0;

	cout << "Parking size: "; cin >> parking_size; cout << "Number of car: "; cin >> number_of_car;
	print(parking_size, number_of_car);

	string choice;
	cout << endl << "Test (yes)? "; cin >> choice;
	if (choice == "yes")
	{
		int N = 0;
		cout << "N: "; cin >> N;
		test_1(N);
		test(N);
	}
}

int number_of_successful_parking_sequence(int parking_size, int number_of_car)
{
	int counter = 0;
	Parking parking(parking_size);

	count_successful_seq(parking, counter, 1, number_of_car);

	return counter;
}
void count_successful_seq(Parking& parking, int& counter, int car_seq_number, int number_of_not_parked_car)
{
	if (number_of_not_parked_car == 0)
	{
		return;
	}

	for (int position = 0; position < parking.size(); position++)
	{
		if (try_parking(parking, car_seq_number, position))
		{
			if (number_of_not_parked_car == 1)
			{
				counter++;
			}
			else
			{
				count_successful_seq(parking, counter, car_seq_number+1, number_of_not_parked_car-1);
			}
			remove_car(parking, car_seq_number);
		}
	}
}

bool try_parking(Parking& parking, int car, int position)
{
	for (int i = position; i < parking.size(); i++)
	{
		if (parking[i] == 0)
		{
			parking[i] = car;
			return true;
		}
	}

	return false;
}

void remove_car(Parking& parking, int car)
{
	for (int i = 0; i < parking.size(); i++)
	{
		if (parking[i] == car)
		{
			parking[i] = 0;
			return;
		}
	}
}

void print(Parking park)
{
	for (int x : park)
	{
		cout << x << " ";
	}
	cout << endl;
}
void print(int parking_size, int number_of_car)
{
	int num = number_of_successful_parking_sequence(parking_size, number_of_car);
	cout << endl << "Parking size: " << parking_size << endl << "Number of car: " << number_of_car << endl;
	cout << "Number of successful parking sequence: " << num << endl;

	if (number_of_car == parking_size)
	{
		int ex = static_cast<int>(pow(parking_size + 1, parking_size - 1));
		cout << "Expected number: " << to_string(ex) << endl;

		if (ex != num)
		{
			cout << "///////////////////////////////////////////////" << endl;
			cout << "//              ERROR OUTPUT                 //" << endl;
			cout << "///////////////////////////////////////////////" << endl;
		}
	}
	else
	{
		cout << "Expected number is unknown" << endl;
	}
}

void test(int N)
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			print(i, j);
		}
	}

	cout << endl;
	cout << "////////////////////////" << endl;
	cout << "////    TEST END    ////" << endl;
	cout << "////////////////////////" << endl;
}
void test_1(int N)
{
	for (int i = 1; i <= N; ++i)
	{
		print(i, i);
	}

	cout << endl;
	cout << "////////////////////////" << endl;
	cout << "////    TEST END    ////" << endl;
	cout << "////////////////////////" << endl;
}
