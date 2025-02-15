
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <queue>

using wConf = pair<long long, long long>;
using rConf = pair<long long, long long>;

// first : start time 
// second : delta time
struct wPriority
{
	bool operator()(const wConf& w1, const wConf& w2)
	{
		return w1.first > w2.first;
	}
};

// first : end time
// second : room number
struct rPriority
{
	bool operator()(const rConf& w1, const rConf& w2)
	{
		if (w1.first == w2.first)
			return w1.second > w2.second;
		return w1.first > w2.first;
	}
};

class Solution
{
private:
	priority_queue<int, vector<int>, greater<int>> freeRoom;
	priority_queue<wConf, vector<wConf>, wPriority> waitQueue;
	priority_queue<rConf, vector<rConf>, rPriority> runQueue;
	vector<int> roomCnt;
	void setProperty(int numRoom, const vector<vector<int>>& meetings)
	{
		for (int i = 0; i < numRoom; ++i)
		{
			freeRoom.push(i);
		}
		for (int i = 0; i < meetings.size(); ++i)
		{
			waitQueue.push(make_pair(meetings[i][0], meetings[i][1] - meetings[i][0] ));
		}
		roomCnt = vector<int>(numRoom, 0);
	}
public:
	Solution()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}
	// solution method
	int mostBooked(int n, vector<vector<int>>& meetings)
	{
		long long curTime = 0;
		 setProperty(n, meetings);
		 // scheduling
		 while (!waitQueue.empty())
		 {
			 // free room first
			 curTime = max(curTime, waitQueue.top().first);
			 while (!runQueue.empty()
				 && runQueue.top().first <= curTime)
			 {
				 // free room
				 freeRoom.push(runQueue.top().second);
				 runQueue.pop();
			 }

			 // schedule room
			 // delay handling
			 if (freeRoom.empty()) // no free room, detact delay
			 {
				 // update curTime
				 curTime = runQueue.top().first;

				 // free room
				 freeRoom.push(runQueue.top().second);
				 runQueue.pop();
			 }
			 // schedule
			 runQueue.push(make_pair(curTime + waitQueue.top().second, freeRoom.top()));
			 // increase room count
			 roomCnt[freeRoom.top()]++;
			 freeRoom.pop();
			 waitQueue.pop();
		 }
		 // get max value
		 int maxRoom = -1, maxCnt = -1;
		 for (int i = 0; i < n; ++i)
		 {
			 if (maxCnt < roomCnt[i])
			 {
				 maxCnt = roomCnt[i];
				 maxRoom = i;
			 }
		 }
		 return maxRoom;
	}
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	// case 1, 0
	int n1 = 2;
	vector<vector<int>> m1 = { {0, 10}, {1, 5}, {2, 7}, {3, 4} };
	std::cout << test.mostBooked(n1, m1) << '\n';
	// case 2, 1
	int n2 = 3;
	vector<vector<int>> m2 = { {1, 20}, {2, 10}, {3, 5}, {4, 9}, {6, 8} };
	std::cout << test.mostBooked(n2, m2) << '\n';
	// case 3, 0
	int n3 = 3;
	vector<vector<int>> m3 = { {39,49} ,{28,39},{9,29},{10,36},{22,47},{2,3},{4,49},{46,50},{45,50},{17,33} };
	std::cout << test.mostBooked(n3, m3) << '\n';
}

