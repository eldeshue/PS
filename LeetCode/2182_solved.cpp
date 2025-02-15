

#include <iostream>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <unordered_map>
#include <queue>
class Solution
{
public:
	// solution method
	using pci = pair<char, int>;
	string repeatLimitedString(string s, int repeatLimit)
	{
		unordered_map<char, int> freq;
		for (const char c : s)
			freq[c]++;
		priority_queue<pci, vector<pci>, less<pci>> pq;
		for (const auto entry : freq)
			pq.push(entry);
		pci tmp;
		char prevChar = '\0';
		string result;
		while (!pq.empty())
		{
			const bool isTmp = (pq.top().first == prevChar);
			if (isTmp)	// ���� Ƚ�� ���ѿ� �ɸ��� ���, ���� �켱���� ���� �ϳ� ��������.
			{
				tmp = pq.top();
				pq.pop();
				if (pq.empty())
					break;
				auto [curChar, curCnt] = pq.top();
				pq.pop();
				result.push_back(curChar);
				curCnt--;
				if (curCnt > 0)
					pq.push(make_pair(curChar, curCnt));
				pq.push(tmp);
			}
			else // ���� ���ѿ� �ɸ��� ����.
			{
				auto [curChar, curCnt] = pq.top();
				pq.pop();
				const int curLimit = min(curCnt, repeatLimit);
				for (int i = 0; i < curLimit; ++i)
				{
					result.push_back(curChar);
					curCnt--;
				}
				if (curCnt > 0)
				{
					pq.push(make_pair(curChar, curCnt));
				}
			}
			prevChar = result.back();
		}
		return result;
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
