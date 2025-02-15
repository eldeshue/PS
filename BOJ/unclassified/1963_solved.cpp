
/*
	���� �賶����

	���������δ� �����ⰰ�ٰ� ������.
	�ϴ� dp, 01 �賶������ ���� ȯ���� �� �־���.
	������ �ð� ���⵵�� �м��ϸ� N^2, �� 10��ȸ�� �����鼭 �ð��ʰ���(2��).

	�ᱹ �賶���� �����ϴµ�, ���⼭ ���� �߷Ḧ �η��� Ǯ�̰� ������. ������ �ڵ� �����
	https://sdy-study.tistory.com/238 ���� ȹ���� �κ���.

	���� �ڵ��� ��� ������ ��Ȳ������ ���� ������ �ð� ���⵵�� ���� ������ �����ϴµ�,
	��ü �� ������ �ڵ�� �����ϰ� �� �ڵ�� �����ϴ����� ���� ��Ȯ�� �м��� ���ϰ���.

	������ ������ �ð����⵵, �ð������� ���� ������ ��ȣ�� ����, �������� ������.

*/

/*
// ����
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory.h>

bool cache[50001];
std::vector<std::pair<int, int>> input;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, val, cnt, target_val;
	for (int test = 0; test < 3; ++test)
	{
		memset(cache, 0, sizeof(cache));
		input.clear();
		target_val = 0;
		std::cin >> N;
		// input
		for (int i = 0; i < N; ++i)
		{
			std::cin >> val >> cnt;
			target_val += val * cnt;
			input.push_back(std::make_pair(val, cnt));
		}
		if (target_val & 1)
		{
			std::cout << "0\n";
			continue;
		}
		// DP, tabulation
		std::sort(input.begin(), input.end());
		target_val /= 2;
		cache[0] = true;
		for (int i = 0; i < input.size(); ++i)
		{
			for (int start = target_val; start >= input[i].first; --start)
			{
				if (cache[start - input[i].first] == true)
				{
					for (int j = 0; j < input[i].second; ++j)
					{
						if (start + j * input[i].first > target_val) break;
						cache[start + j * input[i].first] = true;
					}
				}
			}
		}
		// result
		if (cache[target_val / 2] > 0)
			std::cout << "1\n";
		else
			std::cout << "0\n";
	}
}
*/

/*
// ����, �ð��ʰ�
// �ߺ� ������ ȸ���ϱ� ���ؼ� cache�迭�� int�� ����, ��ĥ�ϴ� ������� ������
#include <iostream>
#include <vector>
#include <memory.h>

int  cache[50001];
std::vector<int> input;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, val, cnt, total_val;
	for (int test = 0; test < 3; ++test)
	{
		memset(cache, 0, sizeof(cache));
		input.clear();
		total_val = 0;
		std::cin >> N;
		// input
		for (int i = 0; i < N; ++i)
		{
			std::cin >> val >> cnt;
			total_val += val * cnt;
			for (int j = 0; j < cnt; ++j)
				input.push_back(val);
		}
		if (total_val % 2 == 1)
		{
			std::cout << "0\n";
			continue;
		}
		// DP, tabulation
		cache[0] = 2;
		for (int i = 0; i < input.size(); ++i)
		{
			for (int cur_val = 0; cur_val <= total_val / 2; ++cur_val)
			{
				int prev_val = cur_val - input[i];
				if (cache[cur_val] == 1)
					cache[cur_val] = 2;
				else if (prev_val >= 0 && cache[cur_val] == 0 && cache[prev_val] == 2)
				{
					cache[cur_val] = 1;
				}
			}
		}
		// result
		if (cache[total_val / 2] > 0)
			std::cout << "1\n";
		else
			std::cout << "0\n";
	}
}


*/