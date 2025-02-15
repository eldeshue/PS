
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
/*
    굉장히 인상적인 문제.

    기존의 전형적인 투 포인터 문제에서 단 하나의 조건으로 문제가 바뀌는 경우임.

    합이 k이상인 sub array들 중, 그 길이의 최솟값을 찾는 문제.

    기존의 문제가 양의 정수 배열이었다면, 해당 문제는 그냥 정수의 배열임.
    따라서 기존의 투포인터를 적용하기 위한 조건인 단조증가성이 깨져서 투포인터가 불가능함.

    솔루션은 크게 두개. 하나는 투포인터를 개조, left들을 우선순위큐에 넣어서 순서대로 탐색.

    ///////

    다른 하나는 모노톤 덱.
*/
#include <queue>
class Solution
{
public:
	// solution method
    using ll = long long;
    using plli = pair<ll, int>;
    int shortestSubarray(vector<int>& nums, int k) {
        priority_queue<plli, vector<plli>, greater<plli>> pq;
        int result = 2e9;
        ll sum = 0;
        pq.push(make_pair(0, -1));
        for (int r = 0; r < nums.size(); ++r)
        {
            sum += nums[r];
            while (!pq.empty() && sum - pq.top().first >= k)
            {
                result = min(result, r - pq.top().second);
                pq.pop();
            }
            pq.push(make_pair(sum, r));
        }
        if (result == 2e9)
            return -1;
        return result;
    }

	//
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
	// solution class

	int main()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);

		Solution test;
	}
