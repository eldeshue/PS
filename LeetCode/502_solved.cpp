
/*
	Maximum k spanning tree

	미니멈 스패닝 트리, 프림 알고리즘에서 영감을 얻었음.
	프림 알고리즘은 현재 구성한 연결요소, 즉 트리에서 최소비용의 에지를 선택하여 
	트리를 확장해나가는 알고리즘임. 

	여기서 우리는 현재 연결요소에서 최대 이득의 노드를 선택하는 것으로 바꿈.
	단, k개를 선택함.

	먼저 그래프를 구성할 필요는 없음. 이미 주어짐.
	가상의 그래프에서 연결 원리는 단 하나, 
	트리를 확장하면서 상승한 w값이 capital값보다 크면 연결됨.
*/
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <queue>
#include <algorithm>

class Solution
{
private:
	using pii = std::pair<int, int>;	// first : capital, second : profit 
public:
	// solution method
	int findMaximizedCapital(int k, int w, vector<int>& profits,
			vector<int>& capital) 
	{
		priority_queue <int, vector<int>, less<int>> pq;
		std::vector<pii> projects;

		for (int i = 0; i < profits.size(); ++i)
			projects.push_back(make_pair(capital[i], profits[i]));

		// 최초 w값은 마치 root 노드처럼 동작함.
		// 마치 위상정렬
		sort(projects.begin(), projects.end(),
			[](const pii& p1, const pii& p2)->bool {return p1.first < p2.first; });

		int idx = 0;
		while (k > 0)
		{
			// 인접한 연결요소의 추가
			while (idx < projects.size() && w >= projects[idx].first)
			{
				pq.push(projects[idx].second);
				idx++;
			}
			// 인접한 노드가 없다, 확장 불가능.
			if (pq.empty())
				break;
			// 트리의 확장, w값 증가.
			w += pq.top();
			pq.pop();
			k--;
		}
		return w;
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

