
#include <iostream>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
/*
	'L'�� �� �ʿ� ��ĭ�� ������ �������� �� �� ����.
	'R'�� ���� �ʿ� ��ĭ�� ������ ���� ������ �� �� ����.

	���� L�� R�� �� � �̵��� ���ؼ��� ������ �ٲ��� ����.
	����� ������ �� ���� ������.
	�� sub sequence��.

	���� �κ� ���� ������ ������ ��, start���� target���� ������ �� �ִ����� ���ε� ����
	���� start�� L�� target�� L���� ���� �ʿ� �־�� ��.
	���������� start�� R�� target�� R���� �� �ʿ� �־�� ��.
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


