
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <unordered_map>
#include <queue>
#include <array>

constexpr int MAX_RANGE = 1000000;
using entry = pair<char, int>;

struct cmp_entry
{
	bool operator()(const entry& e1, const entry& e2)
	{
		return e1.second < e2.second;
	}
};

inline void setChar(array<char, MAX_RANGE>& schedule, int start, int cnt, int interval, char c)
{
	for (int i = 0; i < cnt; ++i)
	{
		schedule[start + i * interval] = c;
	}
}

class Solution
{
public:
	int leastInterval(vector<char>& tasks, int n)
	{
		array<char, MAX_RANGE> *pschedule = new array<char, MAX_RANGE>;
		unordered_map<char, int> cntTable;
		priority_queue<entry, vector<entry>, cmp_entry> PQ;
		const int totalCnt = tasks.size();
		int i = 0;

		fill_n(pschedule->begin(), MAX_RANGE, '\0');
		for (const char& c : tasks)			// O(N), map setting
		{
			if (cntTable.find(c) == cntTable.end())
				cntTable.insert(make_pair(c, 1));
			else
				cntTable[c]++;
		}
		// set PQ
		for (const entry& e : cntTable)
		{
			PQ.push(make_pair(e.first, e.second));
		}
		cntTable.clear();
		while (!PQ.empty())		// O(N log N), scheduling
		{
			if ((*pschedule)[i] == '\0')
			{
				setChar((*pschedule), i, PQ.top().second, n + 1, PQ.top().first);
				PQ.pop();
			}
			i++;
		}
		// debug
		for (int j = 0; j < 20; ++j)
		{
			if ((*pschedule)[j] == '\0')
				cout << '0' << ' ';
			else
				cout << (*pschedule)[j] << ' ';
		}
		cout << '\n';
		// debug
		int result = 0;
		int cnt = 0;
		// ?????
		while (cnt < totalCnt)		// O(N) count result
		{
			if ((*pschedule)[result] != '\0')
			{
				cnt++;
			}
			result++;
		}
		delete pschedule;
		return result;
	}
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	vector<char> input = { 'A','A','A','B','B','B', 'C','C','C', 'D', 'D', 'E' };
	//vector<char> input = {'A', 'C', 'A', 'B', 'D', 'B'};
	//vector<char> input = {'A', 'A', 'A', 'B', 'B', 'B'};
	cout << test.leastInterval(input, 2);
}

