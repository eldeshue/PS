
#include <iostream>
#include <vector>

using namespace std;

// solution
/*
	주어진 배열에서 두 번 등장하는 원소를 모두 구하라.

	시간 복잡도 : O(n)
	공간 복잡도 : O(1), 원소를 저장하는 벡터 이외의 메모리는 사용하지 말것.

	벡터의 길이는 n
	주어진 원소는 모두 1~n 사이의 값
	모든 원소는 하나 혹은 두 번 나옴
		-> 원소의 범위와, 그 개수를 고려하면 특정 원소가 두 번 등장하면, 어떤 원소는 등장하지 않게 됨.

	등장하지 않는 원소의 개수가 곧 두 번 등장하는 원소의 개수임.

	그래프로 모델링하면 우리가 원하는 노드는 사이클과 비사이클(꼬리)가 만나는 노드임.
	===================================================================

	방문 여부를 기록하기 위해서 nums의 원소를 지운다.
	단, 벡터는 0부터이므로 인덱스에 -1해서 접근할 수 있도록 한다.

	시작 노드는 -1로 칠해서 구분함. 이는 해당 연결요소의 탐색 여부를 확인하기 위함임.

	0으로 칠하면서 그래프를 탐색한다. 탐색 과정 중 다음의 가능성이 존재함.

	1. 해당 노드가 이미 방문한 노드
		1-1. 해당 노드의 색이 -1
			색이 -1이라는 점은 두 가지 가능성 중 하나임
				1. 이전에 색칠한 연결요소의 시작 노드
					-> 이전에 색칠한 연결요소의 꼬리의 일부, 의미 없음. 새로운 시작노드가 이를 대신할 것임.
				2. 현재 색칠하던 연결요소의 시작 노드
					-> 해당 시작 노드가 꼬리의 일부가 아님, 즉 사이클의 일부.
			어느 쪽도 시작 노드로서의 의미를 상실함, 따라서 0으로 칠하고 색칠을 멈춤.

		1-2. 해당 노드의 색이 0
			색이 0이라는 사실은 사이클의 일부(꼬리가 무조건 아님), 즉 색칠하는 과정에서 사이클의 존재를 식별했음.
			또한 꼬리가 사이클과 접하는 지점을 의미하기에 그래프에서 2회 이상 pointed된 노드임. get

	2. 미방문 노드
		-> 계속 탐색함.
*/
#pragma GCC optimize("03")
#pragma GCC target ("avx")

inline void paintConnectionElement(vector<int>& nums, vector<int>& result, int start)
{
	int curNode;

    curNode = nums[start - 1];
    nums[start - 1] = -1;   // paint part node, can be start of tail or part of cycle
	while (true)
	{
		if (nums[curNode - 1] == -1)
		{
            // if start is part of already visited tail,
			//	-> new start node will replace the previous one
            // else start is part of cycle
			//	-> so not a part of tail
            nums[curNode - 1] = 0;
			break;
		}
		else if (nums[curNode - 1] == 0)
		{
            // meet already painted node, part of cycle
            // which means double visit
			result.push_back(curNode);
			break;
		}
		int prevNode = curNode;
		curNode = nums[curNode - 1];
		nums[prevNode - 1] = 0; // paint visited node
	}
	return ;
}

class Solution
{
public:
	vector<int> findDuplicates(vector<int>& nums)
	{
		vector<int> result;

		for (int n = 1; n <= nums.size(); ++n)
		{
			if (nums[n - 1] != 0 && nums[n - 1] != -1)
				paintConnectionElement(nums, result, n);
		}
		return result;
	}
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}
