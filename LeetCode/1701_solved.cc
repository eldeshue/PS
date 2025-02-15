
#include <iostream>
#include <vector>

using namespace std;

// solution
class Solution
{
public:
	// solution method
	double averageWaitingTime(vector<vector<int>> &customers)
	{
		int curTime = 0;
		double sum = 0;
		for (const auto &customer : customers)
		{
			int startTime = customer[0];
			int endTime = std::max(curTime, startTime) + customer[1];
			sum += endTime - startTime;
			curTime = endTime;
		}
		return sum / customers.size();
	}
};

//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
