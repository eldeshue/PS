
/*

#include <iostream>
#include <vector>

using namespace std;

*/

// solution class
/*
	플로이드의 거북이와 토끼 문제.

	그래프 내에서 사이클을 식별하는 문제.
	주어진 벡터를 그래프라고 생각해보자.
	각 인덱스에 저장된 값을 인덱스 노드에서 값 노드로 향하는 에지를 표현한다고 하자.
	
	nums[노드1] == 노드2
	즉 node 1이 node 2를 가리킴을 의미함

	이러한 그래프로 바라보면 주어진 문제는 특정한 그래프를 식별하는 문제가 됨. 
	순수한 사이클이 아닌, 일명 꼭지가 달린 사이클을 찾는 문제임.
	문제의 답은 이 사이클의 꼭짓점.

	왜냐? 순수한 사이클은 서로가 서로를 가리키며 하나의 사이클을 그림. 에지가 하나.
	꼭지가 달린 사이클만 복수의 에지를 갖는 노드가 등장함.

	문제는 시작 노드의 선정임.
	주어진 벡터는 사이즈가 N + 1, 벡터에 들어있는 원소는 1~N만 존재함.
	이 말은 0번 노드는 그 어떤 노드도 가리키지 않는다. 즉 0번노드는 항상 꼭지의 끝.
*/

/*

class Solution
{
public:
	// solution method
	int findDuplicate(vector<int>& nums)
	{
		int fast = nums[nums[0]], slow = nums[0];

		while (fast != slow)
		{
			fast = nums[nums[fast]];
			slow = nums[slow];
		}
		slow = 0;
		while (fast != slow)
		{
			fast = nums[fast];
			slow = nums[slow];
		}
		return fast;
	}
	//
};

*/
