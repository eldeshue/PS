
/*

	�� ������, 
	�⺻������ start�� �̵���Ŵ, ��ġ�ϴ� ù ���ڸ� ã����, end�� �̵���Ŵ.
	��� ���ڸ� ã���� ���� �񱳸� ���ؼ� �ּҰ��� ������.

	< �ݷ� >
	s: "ababcc"
	t: "abc"
	result : "abc"

*/
#include <iostream>
#include <string>

using namespace std;

// solution class
#include <unordered_map>
#include <deque>

class Solution
{
private:
	unordered_map<char, pair<int, int>> table;
	void fillTable(const string& t)	// O(M)
	{
		for (const char& c : t)
		{
			if (table.find(c) == table.end())
				table.insert(make_pair(c, make_pair(1, 0)));
			else
				table[c].first++;
		}
	}
	void incTableCnt(char c, int& curCnt)
	{
		const int& curEntryMax = table[c].first;
		int& curEntryCnt = table[c].second;

		curEntryCnt++;
		if (curEntryCnt <= curEntryMax)
			curCnt++;
	}
	void decTableCnt(char c, int& curCnt)
	{
		const int& curEntryMax = table[c].first;
		int& curEntryCnt = table[c].second;

		curEntryCnt--;
		if (curEntryCnt < curEntryMax)
			curCnt--;
	}
	bool isTableFull(const int MaxCnt, const int curCnt) const
	{
		return (curCnt == MaxCnt);
	}
public:
	// solution method
	string minWindow(string s, string t)
	{
		int			curCnt = 0;
		const int	MaxCnt = t.size();
		int			rStart = 0, rEnd = s.size();
		deque<pair<char, int>> windowDeq;	// char, pos

		// from t, set the hash map, O(M)
		fillTable(t);

		// two pointer
		int idx = -1;
		while (++idx < s.size()) // O(N)
		{
			// before first find
			if (table.find(s[idx]) != table.end()) // after find
			{
				incTableCnt(s[idx], curCnt);
				windowDeq.push_back(make_pair(s[idx], idx));
				// found all
				if (isTableFull(MaxCnt, curCnt))
				{
					// update answer
					int start = windowDeq.front().second;
					int end = windowDeq.back().second;
					if ((end - start) < (rEnd - rStart))
					{
						rStart = start;
						rEnd = end;
					}
					// deque�� �տ������� pop front�غ��鼭 ���� �� �ִ��� �Ǵ�
					decTableCnt(windowDeq.front().first, curCnt);
					windowDeq.pop_front();
					while (!windowDeq.empty() && isTableFull(MaxCnt, curCnt))
					{
						start = windowDeq.front().second;
						if ((end - start) < (rEnd - rStart))
						{
							rStart = start;
							rEnd = end;
						}
						// pop
						decTableCnt(windowDeq.front().first, curCnt);
						windowDeq.pop_front();
					}
				}
			}
		}
		if ((rEnd - rStart) == s.size())	// never found
			return string();	// empty string
		else
			return s.substr(rStart, rEnd - rStart + 1);
	}
	//
};

// solution class

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Solution test;
	string s = "a", t = "aa";
	cout << test.minWindow(s, t);
}
