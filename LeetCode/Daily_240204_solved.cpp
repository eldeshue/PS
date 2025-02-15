
/*

	투 포인터, 
	기본적으로 start를 이동시킴, 일치하는 첫 문자를 찾으면, end를 이동시킴.
	모든 문자를 찾으면 길이 비교를 통해서 최소값을 갱신함.

	< 반례 >
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
					// deque의 앞에서부터 pop front해보면서 줄일 수 있는지 판단
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
