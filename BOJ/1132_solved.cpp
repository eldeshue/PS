
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <memory.h>

int N;
unsigned long long priority[10];
bool is_first[10];
std::vector<int> idx_arr;

bool cmp_idx(int idx1, int idx2)
{
	return (priority[idx1] < priority[idx2]);	// all same
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(priority, 0, sizeof(priority));
	memset(is_first, 0, sizeof(is_first));
	for (int i = 0; i < 10; ++i)
		idx_arr.push_back(i);

	std::string input;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		unsigned long long radix = 1;
		for (int j = input.size() - 1; j >= 0; --j)
		{
			int cur_alpha = input[j] - 'A';
			priority[cur_alpha] += radix;
			radix *= 10;
			if (j == 0)
				is_first[cur_alpha] = true;
		}
	}
	// sorting
	std::sort(idx_arr.begin(), idx_arr.end(), cmp_idx);
	// exception handling
	if (is_first[idx_arr[0]])
	{
		int target = 0;
		for (int i = 1; i < 10; ++i)
		{
			if (!is_first[idx_arr[i]])
			{
				target = idx_arr[i];
				for (int j = i; j >= 1; --j)
					idx_arr[j] = idx_arr[j - 1];
				idx_arr[0] = target;
				break;
			}
		}
	}
	// calculating total value
	unsigned long long result = 0;
	for (int cur_digit = 1; cur_digit < 10; ++cur_digit)
		result += cur_digit * priority[idx_arr[cur_digit]];
	std::cout << result;
}