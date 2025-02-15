// meet in the middle
#include <iostream>
#include <cmath>
#include <map>

long long result = 0;
int N, S;
int num[40];
std::map<int, int> count;

void fillNumHalf(int index, int val) // O( 2 ^ n )
{
	if (index == N/2)
	{
		if (count.find(val) == count.end())
		{
			count.insert(std::make_pair(val, 1));
		}
		else
		{
			count[val]++;
		}
		return;
	}
	int nextVal = val + num[index];
	fillNumHalf(index + 1, val);
	fillNumHalf(index + 1, nextVal);
}

void meetInMiddle(int index, int val)
{
	if (index == N)
	{
		int rest = S - val;
		if (count.find(rest) != count.end())
		{
			result += count[rest];
		}
		return;
	}
	int nextVal = val + num[index];
	meetInMiddle(index + 1, val);
	meetInMiddle(index + 1, nextVal);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> S;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> num[i];
	}

	fillNumHalf(0, 0);

	// meet in the middle
	meetInMiddle(N / 2, 0);

	if (S == 0)
	{
		result--;
	}

	std::cout << result;
}