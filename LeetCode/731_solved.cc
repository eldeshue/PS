

#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <map>
#include <vector>
class MyCalendarTwo
{
private:
	using Entry = pair<int, pair<int, int>>;
	map<int, pair<int, int>> schedules;
	bool isOverlap(const int s1, const int e1, const int s2, const int e2)
	{
		return (s1 < e2) && (e1 > s2);
	}
	bool isDoubleBooked(int s, int e)
	{
		for (const auto &[curStart, pair] : schedules)
		{
			const auto &[curEnd, count] = pair;
			if (count >= 2 && isOverlap(s, e, curStart, curEnd))
			{
				std::cout << s << ' ' << e << ':' << curStart << ' ' << curEnd << '\n';
				return true;
			}
		}
		return false;
	}

public:
	MyCalendarTwo() {}

	bool book(int start, int end)
	{
		if (isDoubleBooked(start, end))
			return false;
		// add
		vector<Entry> addBuffer;
		vector<int> deleteBuffer;
		for (auto &[curStart, pair] : schedules)
		{
			auto &[curEnd, count] = pair;
			if (isOverlap(start, end, curStart, curEnd))
			{
				if (start == curStart && end == curEnd)
				{
					count++;
				}
				else
				{
					deleteBuffer.push_back(curStart);
					if (start < curStart)
					{
						addBuffer.push_back(make_pair(start, make_pair(curStart, 1)));
						start = curStart;
					}
					else if (curStart < start)
					{
						addBuffer.push_back(make_pair(curStart, make_pair(start, count)));
					}
					// commont part
					if (end < curEnd)
					{
						addBuffer.push_back(make_pair(start, make_pair(end, count + 1)));
						addBuffer.push_back(make_pair(end, make_pair(curEnd, count)));
						start = end;
					}
					else if (end >= curEnd)
					{
						addBuffer.push_back(make_pair(start, make_pair(curEnd, count + 1)));
						start = curEnd;
					}
				}
				if (start == end)
					break;
			}
		}

		// after overlapping
		if (start < end)
			schedules.insert(make_pair(start, make_pair(end, 1)));
		// add all
		for (const int s : deleteBuffer)
		{
			schedules.erase(s);
		}
		for (const auto &e : addBuffer)
		{
			schedules.insert(e);
		}
		return true;
	}
};
