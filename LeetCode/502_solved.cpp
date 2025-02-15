
/*
	Maximum k spanning tree

	�̴ϸ� ���д� Ʈ��, ���� �˰��򿡼� ������ �����.
	���� �˰����� ���� ������ ������, �� Ʈ������ �ּҺ���� ������ �����Ͽ� 
	Ʈ���� Ȯ���س����� �˰�����. 

	���⼭ �츮�� ���� �����ҿ��� �ִ� �̵��� ��带 �����ϴ� ������ �ٲ�.
	��, k���� ������.

	���� �׷����� ������ �ʿ�� ����. �̹� �־���.
	������ �׷������� ���� ������ �� �ϳ�, 
	Ʈ���� Ȯ���ϸ鼭 ����� w���� capital������ ũ�� �����.
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

		// ���� w���� ��ġ root ���ó�� ������.
		// ��ġ ��������
		sort(projects.begin(), projects.end(),
			[](const pii& p1, const pii& p2)->bool {return p1.first < p2.first; });

		int idx = 0;
		while (k > 0)
		{
			// ������ �������� �߰�
			while (idx < projects.size() && w >= projects[idx].first)
			{
				pq.push(projects[idx].second);
				idx++;
			}
			// ������ ��尡 ����, Ȯ�� �Ұ���.
			if (pq.empty())
				break;
			// Ʈ���� Ȯ��, w�� ����.
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

