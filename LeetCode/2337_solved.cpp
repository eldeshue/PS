
#include <iostream>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
/*
	'L'은 왼 쪽에 빈칸이 있으면 왼쪽으로 갈 수 있음.
	'R'은 오른 쪽에 빈칸이 있으면 오른 쪽으로 갈 수 있음.

	따라서 L과 R은 그 어떤 이동에 의해서도 순서가 바뀌질 않음.
	절대로 교차할 수 없기 때문임.
	즉 sub sequence임.

	또한 부분 수열 조건을 만족한 후, start에서 target으로 진행할 수 있느냐의 여부도 있음
	따라서 start의 L은 target의 L보다 오른 쪽에 있어야 함.
	마찬가지로 start의 R은 target의 R보다 왼 쪽에 있어야 함.
*/
#include <numeric>
class Solution
{
public:
	// solution method
	bool canChange(string start, string target)
	{
		int sIdx = 0, tIdx = 0;
		auto addIsAlpha = [](const int acc, const char c)
			{
				return acc + isalpha(c);
			};
		if (accumulate(start.begin(), start.end(), 0, addIsAlpha)
			!= accumulate(target.begin(), target.end(), 0, addIsAlpha))
			return false;
		while (sIdx < start.size() && tIdx < target.size())
		{
			while (sIdx <start.size() && start[sIdx] == '_')
				sIdx++;
			while (tIdx < target.size() && target[tIdx] == '_')
				tIdx++;

			if (start[sIdx] != target[tIdx]
				|| (start[sIdx] == 'L' && sIdx < tIdx)
				|| (start[sIdx] == 'R' && tIdx < sIdx)) // not sub-seq
			{
				return false;
			}
			sIdx++; tIdx++;
		}
		return true;
	}
	//
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}


