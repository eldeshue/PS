

#include <iostream>
#include <vector>

using namespace std;
/*

 정렬되기 위해서는 chunk가 커버하는 범위가 내 현재 위치는 물론,
 내가 정렬된 위치도 커버해줘야 함.
 혹은 자신이 속한 chunk가 내가 갈 자리를 잡고 있어야 함.

 * solution 1. greedy 색칠하기
 curPos, limitPos 두 개의 값을 들고 색칠을 시작함.
 curPos가 limitPos에 이르기 까지는 같은 색임.
 limitPos가 넘어서는 순간, 색이 바뀌고, limitPos도 초기화
 기본적으로 두 값은 같아서 1 칸을 칠하도록
 단, 우선순위큐가 개입한다면....
 우선순위 큐에 {정렬된 위치, 원래 위치}의 페어를 저장
 정렬된 위치가 본래의 위치보다 왼 쪽에 있는 노드만 우선수위큐에 넣음
 min heap, n log n
 top의 노드와 현재 위치가 일치하는 경우 pop, limitPos를 max로 확장
 이후에도 정렬된 위치가 오른쪽으로 가는 노드에 대하여 limitPos를 갱신

 * solution 2. 스위핑, O(n log n)
 위에 생각해낸 풀이는 오토마타적인, 잘 정련되지 않은 풀이임.
 이 풀이를 좀 더 깔끔하게 다듬으면 문제가 스위핑이라는 것을 알 수 있음.

 위 풀이에서 우리는 왜 우선순위 큐를 도입하였는가? 이는 왼쪽으로 정렬되는 경우를 위함임.
 즉, 정렬 전 위치와 정렬 후의 위치가 하나의 range를 구성하는 것을 확인할 수 있음.

 이후에는 겹치는 range를 뭉쳐서 하나의 chunk로 만들면 됨. range를 우선순위 큐에 집어넣고, sweeping을 수행하면 됨.

 * solution 3. 최적화, O(n)
 놀랍게도 O(n)이 존재한다. 메모리도 O(1)이다.
 먼저 주어진 배열은 permutation이라 값의 범위가 고정되어 있다.
 정렬 결과, 어떤 값이 왼 쪽으로 온다는 것은, 그 반대로 오른 쪽으로 가는 값이 반드시 존재함을 의미한다.
 따라서, 우리는 미래에 만날, 왼 쪽으로 점프할 어떠 미지의 값을 두려워 할 필요가 없다.
 왼쪽에서 출발하여 오른 쪽으로 진행할 경우, 왼쪽으로 이동하는 그 값, 혹은 그 이상의 값으로 이동할 값을 반드시 만난다.
 따라서 오직 최댓값만 추적해도 문제가 없다.

 최댓값만을 추적하다가 그 최댓값에 도달하는 그 순간 count를 1 올려주면 된다.

 어떻게 보면 solution 2는 보다 일반적인 상황(permutation이 아닌 경우)에 대한 풀이였다고 할 수 있다.
*/
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <queue>
class Solution
{
private:
public:
	// solution method
	using pii = pair<int, int>;
	int maxChunksToSorted(vector<int> &arr)
	{
		// sweeping
		const int N = arr.size();
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		for (int i = 0; i < N; ++i)
		{
			pq.push(make_pair(min(i, arr[i]), max(i, arr[i])));
		}
		// while overlapped, cout increase
		int result = 0;
		pii curRange = {0, 0};
		auto isOverlap = [&](pii const newRange)
		{
			return (newRange.first <= curRange.second);
		};
		while (!pq.empty())
		{
			pii const newRange = pq.top();
			pq.pop();
			if (isOverlap(newRange))
			{
				// update
				curRange.second = max(curRange.second, newRange.second);
			}
			else
			{
				result++;			 // increase count
				curRange = newRange; // update
			}
		}
		return result;
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
