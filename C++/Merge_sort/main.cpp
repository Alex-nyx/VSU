#include <iostream>
#include <vector>

using namespace std;

namespace impl
{

void merge_sort_impl(string& str, int left, int right);
void merge_sort_impl(vector<pair<string, string>>& vec, int left, int right, bool (*cmp) (pair<string, string>, pair<string, string>));

void merge(string& str, int left, int mid, int right);
void merge(vector<pair<string, string>>& vec, int left, int mid, int right, bool (*cmp) (pair<string, string>, pair<string, string>));

};

void merge_sort(string& str);
void merge_sort(vector<pair<string, string>>& vec, bool (*cmp) (pair<string, string>, pair<string, string>));

bool cmp(pair<string, string>, pair<string, string>);

int main()
{
	vector<string> dict = {"letters", "evil", "vile", "angered", "enraged", "pat", "tap",
		"a gentleman", "formed", "rearranging", "elegant man", "phase", "eleven plus two", "phrase", "twelve plus one", "placebo",
		"obecalp", "restful", "fluster", "original", "funeral", "typically", "real fun", "adultery", "true lady",
		"customers","using", "all", "the", "store scum", "forty five", "over fifty", "word"
	};
	
	cout << "Dictionary: ";
	for (int i = 0; i < dict.size(); i++)
	{
		if(i%6 == 0)
		{
			cout << endl << " ";
		}
		cout << "< " << dict[i] << " > : ";
	}
	cout << endl << endl;

	vector<pair<string, string>> sort_dict;

	for (string s : dict)
	{
		pair<string, string> orig_sort;
		orig_sort.first = s;
		merge_sort(s);
		orig_sort.second = s;
		sort_dict.push_back(orig_sort);
	}

	merge_sort(sort_dict, cmp);

	for (auto p : sort_dict)
	{
		cout << p.first << " : " << p.second << endl;
	}
	
	cout << "\nAnagrams\n";

	for (int i = 0; i < sort_dict.size(); i++)
	{
		for (int j = i + 1; j < sort_dict.size() && sort_dict[i].second == sort_dict[j].second; j++)
		{
			if (sort_dict[i].second == sort_dict[j].second)
			{
				cout << "< " << sort_dict[i].first << " : " << sort_dict[j].first << " >" << endl;
			}
		}
	}

	cin.get();
}

//template<typename T>
//void merge_sort(T array[], std::size_t size)
//{
//	if (size > 1)
//	{
//		std::size_t const left_size = size / 2;
//		std::size_t const right_size = size - left_size;
//
//		merge_sort(&array[0], left_size);
//		merge_sort(&array[left_size], right_size);
//
//		std::size_t lidx = 0, ridx = left_size, idx = 0;
//		std::unique_ptr<T[]> tmp_array(new T[size]);
//
//		while (lidx < left_size || ridx < size)
//		{
//			if (array[lidx] < array[ridx])
//			{
//				tmp_array[idx++] = std::move(array[lidx]);
//				lidx++;
//			}
//			else
//			{
//				tmp_array[idx++] = std::move(array[ridx]);
//				ridx++;
//			}
//
//			if (lidx == left_size)
//			{
//				std::copy(std::make_move_iterator(&array[ridx]),
//					std::make_move_iterator(&array[size]),
//					&tmp_array[idx]);
//				break;
//			}
//			if (ridx == size)
//			{
//				std::copy(std::make_move_iterator(&array[lidx]),
//					std::make_move_iterator(&array[left_size]),
//					&tmp_array[idx]);
//				break;
//			}
//		}
//
//		std::copy(std::make_move_iterator(tmp_array),
//			std::make_move_iterator(&tmp_array[size]),
//			array);
//	}
//}
//
//int* merge_sort(int* up, int* down, unsigned int left, unsigned int right)
//{
//	if (left == right)
//	{
//		down[left] = up[left];
//		return down;
//	}
//
//	unsigned int middle = (left + right) / 2;
//
//	// раздел€й и сортируй
//	int* l_buff = merge_sort(up, down, left, middle);
//	int* r_buff = merge_sort(up, down, middle + 1, right);
//
//	// сли€ние двух отсортированных половин
//	int* target = l_buff == up ? down : up;
//
//	unsigned int l_cur = left, r_cur = middle + 1;
//	for (unsigned int i = left; i <= right; i++)
//	{
//		if (l_cur <= middle && r_cur <= right)
//		{
//			if (l_buff[l_cur] < r_buff[r_cur])
//			{
//				target[i] = l_buff[l_cur];
//				l_cur++;
//			}
//			else
//			{
//				target[i] = r_buff[r_cur];
//				r_cur++;
//			}
//		}
//		else if (l_cur <= middle)
//		{
//			target[i] = l_buff[l_cur];
//			l_cur++;
//		}
//		else
//		{
//			target[i] = r_buff[r_cur];
//			r_cur++;
//		}
//	}
//	return target;
//}

void merge_sort(string& str)
{
	impl::merge_sort_impl(str, 0, str.size() - 1);
}
void merge_sort(vector<pair<string, string>>& vec, bool (*cmp) (pair<string, string>, pair<string, string>))
{
	impl::merge_sort_impl(vec, 0, vec.size() - 1, cmp);
}

void impl::merge_sort_impl(string& str, int left, int right)
{
	if(right <= left)
	{
		return;
	}

	int mid = (right + left) / 2;
	impl::merge_sort_impl(str, left, mid);
	impl::merge_sort_impl(str, mid + 1, right);
	impl::merge(str, left, mid, right);
}
void impl::merge(string& str, int left, int mid, int right)
{
	int i, j;
	static string aux;
	aux.resize(str.size());

	for (i = mid + 1; i > left; --i)
	{
		aux[i - 1] = str[i - 1];
	}
	for (j = mid; j < right; ++j)
	{
		aux[right + mid - j] = str[j + 1];
	}
	for (int k = left; k <= right; k++)
	{
		if (aux[j] < aux[i])
		{
			str[k] = aux[j--];
		}
		else
		{
			str[k] = aux[i++];
		}
	}
}

void impl::merge_sort_impl(vector<pair<string, string>>& vec, int left, int right, bool (*cmp) (pair<string, string>, pair<string, string>))
{
	if (right <= left)
	{
		return;
	}

	int mid = (right + left) / 2;
	impl::merge_sort_impl(vec, left, mid, cmp);
	impl::merge_sort_impl(vec, mid + 1, right, cmp);
	impl::merge(vec, left, mid, right, cmp);
}
void impl::merge(vector<pair<string, string>>& vec, int left, int mid, int right, bool (*cmp) (pair<string, string>, pair<string, string>))
{
	int i, j;
	static vector<pair<string, string>> aux;
	aux.resize(vec.size());

	for (i = mid + 1; i > left; --i)
	{
		aux[i - 1] = vec[i - 1];
	}
	for (j = mid; j < right; ++j)
	{
		aux[right + mid - j] = vec[j + 1];
	}
	for (int k = left; k <= right; k++)
	{
		if (cmp(aux[i], aux[j]))
		{
			vec[k] = aux[j--];
		}
		else
		{
			vec[k] = aux[i++];
		}
	}
}

bool cmp(pair<string, string> p1, pair<string, string> p2)
{
	return p1.second > p2.second ? true : false;
}