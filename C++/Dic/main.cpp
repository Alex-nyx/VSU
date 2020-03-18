#include "BSTDict.hpp"
#include <iostream>
#include <utility>

using namespace std;

int distance(string, string);
int distance(string, int, string, int);
int minimum(int, int, int);
pair<string, int> find_nearest(string, bs_tree*, pair<string, int>);


int main()
{
	string file_path = "E:\dictionary.txt";
	cout << "File : "; 
	cin >> file_path;
	cout << endl;
	bs_tree* dictionary = create_from_file(file_path);

	bst_traverse(dictionary, [](string s) {cout << s << endl; }); cout << endl;

	bool exit = false;
	do
	{
		string word;
		cout << "\nEnter word : ";
		cin >> word; cout << endl;

		if (bst_at(word, dictionary))
		{
			cout << word <<  " in dictionary" << endl;
		}
		else
		{
			pair<string, int> nearest_word = find_nearest(word, dictionary, { "", 1000 });
			double diff = 1 - nearest_word.second/static_cast<double>(nearest_word.first.length());

			if (diff > 0.40 || abs(diff - 0.40) < 0.01)
			{
				cout << "Correcct word : "<< nearest_word.first;
				cout << " % " << diff * 100 << endl;
			}
			else
			{
				cout << word << " not in dictionary" << endl;
				cout << "Nearest word to " << word << " : " << nearest_word.first;
				cout << " % " << diff * 100 << endl;
			}
		}

		cout << endl << "Do you want to exit(yes)? : ";
		cin >> word;
		if (word == "yes")
		{
			exit = true;
		}
	} while (!exit);

	bst_free(dictionary);
}

int distance(string s1, string s2)
{
	return distance(s1, s1.length(), s2, s2.length());
}

int distance(string s, int len_s, string t, int len_t)
{
	int cost;

	
	if (len_s == 0) return len_t;
	if (len_t == 0) return len_s;

	
	if (s[len_s - 1] == t[len_t - 1])
	{
		cost = 0;
	}
	else
	{
		cost = 1;
	}

	
	return minimum(
		distance(s, len_s - 1, t, len_t) + 1,
		distance(s, len_s, t, len_t - 1) + 1,
		distance(s, len_s - 1, t, len_t - 1) + cost
		);
}

int minimum(int a, int b, int c)
{
	if (a > b)
	{
		swap(a, b);
	}
	if (a > c)
	{
		swap(a, c);
	}
	return a;
}

pair<string, int> find_nearest(string word, bs_tree* tree, pair<string, int> word_dist)
{
	if (tree == nullptr)
	{
		return word_dist;
	}

	int dist = distance(word, tree->str);

	if (dist < word_dist.second)
	{
		word_dist.first = tree->str;
		word_dist.second = dist;
	}

	pair<string, int> left = find_nearest(word, tree->left, word_dist);
	pair<string, int> right = find_nearest(word, tree->right, word_dist);
	
	if (left.second < word_dist.second)
	{
		swap(left, word_dist);
	}
	if (right.second < word_dist.second)
	{
		swap(right, word_dist);
	}

	return word_dist;
}
