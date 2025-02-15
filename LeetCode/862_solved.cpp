
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
/*
    ������ �λ����� ����.

    ������ �������� �� ������ �������� �� �ϳ��� �������� ������ �ٲ�� �����.

    ���� k�̻��� sub array�� ��, �� ������ �ּڰ��� ã�� ����.

    ������ ������ ���� ���� �迭�̾��ٸ�, �ش� ������ �׳� ������ �迭��.
    ���� ������ �������͸� �����ϱ� ���� ������ ������������ ������ �������Ͱ� �Ұ�����.

    �ַ���� ũ�� �ΰ�. �ϳ��� �������͸� ����, left���� �켱����ť�� �־ ������� Ž��.

    ///////

    �ٸ� �ϳ��� ����� ��.
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
