
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// solution class
#include <unordered_set>
#include <queue>

class Solution
{
public:
	// solution method
	int openLock(vector<string>& deadends, string target)
	{
		unordered_set<string> visited;
		deque<pair<string, int>> dq;
		int result = -1;

		for (const string& str : deadends)
			visited.insert(str);
		if (visited.find("0000") == visited.end())
			dq.push_back(make_pair("0000", 0));
		while (!dq.empty())
		{
			if (dq.front().first == target)
			{
				result = dq.front().second;
				break;
			}
			// increase
			for (int i = 0; i < 4; ++i)
			{
				string next = dq.front().first;
				if (++next[i] > '9')
				{
					next[i] = '0';
				}
				if (visited.find(next) == visited.end())
				{
					visited.insert(next);
					dq.push_back(make_pair(next, dq.front().second + 1));
				}
			}
			// decrease
			for (int i = 0; i < 4; ++i)
			{
				string next = dq.front().first;
				if (--next[i] < '0')
				{
					next[i] = '9';
				}
				if (visited.find(next) == visited.end())
				{
					visited.insert(next);
					dq.push_back(make_pair(next, dq.front().second + 1));
				}
			}
			dq.pop_front();
		}
		return result;
	}
	//
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}

