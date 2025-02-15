
/*
	응용 배낭문제

	개인적으로는 쓰레기같다고 생각함.
	일단 dp, 01 배낭문제로 쉽게 환원할 수 있었음.
	하지만 시간 복잡도를 분석하면 N^2, 즉 10억회가 나오면서 시간초과함(2초).

	결국 배낭으로 접근하는데, 여기서 갖은 야료를 부려야 풀이가 가능함. 이하의 코드 상당은
	https://sdy-study.tistory.com/238 에서 획득한 부분임.

	정답 코드의 경우 최작의 상황에서는 거의 동일한 시간 복잡도가 나올 것으로 생각하는데,
	대체 왜 이하의 코드는 성공하고 내 코드는 실패하는지에 대한 명확한 분석을 못하겠음.

	문제에 설정된 시간복잡도, 시간제한의 설정 기준이 모호한 문제, 쓰레기라고 생각함.

*/

/*
// 정해
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
// 오답, 시간초과
// 중복 접근을 회피하기 위해서 cache배열을 int로 설정, 색칠하는 방식으로 접근함
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