
/*
	일명 빗물 문제.

	벡터로 지형 정보가 들어오고, 여기에 비가 온다면 고인 물은 얼마인가 문제.

	sol1 : 각 높이마다 물이 얼마나 고였는지 계산함.
		-> 오답, 시간은 지형의 높이에 비례 O(H), 공간은 O(N * H).
	sol2 : 스택을 활용, 쌍을 맞춰서 계산. 마치 괄호 풀듯이...
		-> 정답, 벡터의 길이에 비례하는 시간 O(N), 공간 O(N) 풀이.

*/
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <stack>

using Block = std::pair<int, int>;

class Solution
{
public:
	int trap(vector<int>& height)
	{
		stack<Block> history;
		int result = 0;

		for (int x = 0; x < height.size(); ++x)
		{
			const int& y = height[x];
			if (!history.empty() && history.top().second < y)
			{
				while (!history.empty() && history.top().second < y)
				{
					int botX = history.top().first;
					int botY = history.top().second;
					history.pop();
					if (!history.empty())
					{
						int delX = x - botX;
						if (history.top().second <= y)
						{
							int delY = history.top().second - botY;
							result += delX * delY;
						}
						else if (history.top().second > y)
						{
							int delY = y - botY;
							result += delX * delY;
							history.push(make_pair(botX, y));
							break;
						}
					}
				}
				if (history.empty())
					history.push(make_pair(x, y));
			}
			else if (!history.empty() && history.top().second == y)
				continue;
			else
			{
				history.push(make_pair(x, y));
			}
		}
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
	//vector<int> h = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
	//vector<int> h = {4, 2, 0, 3, 2, 5};
	vector<int> h = {9, 2, 4, 0, 3, 4};
	std::cout << test.trap(h);
}

