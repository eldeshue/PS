

/*
	범위를 고려하면 dp는 아님.
	딱히 정렬을 해야 할 이유도 없어보임. -> 그리디도 아닌듯.

	원소의 개수가 a,b의 두 개라서 투 포인터를 고려할 수 있음.
	근데 왜 되는지를 알 수 없음.

	naive하게 풀면 n ^ 2이겠다.

	====================================================

	n의 범위가 2 ^ 31 - 1, 따라서 제곱수는 대략 2 ^ 16개에 좀 못미침.
	대략 64000개 정도...

	투 포인터가 가능한 이유는 제곱수가 갖는 다음의 성질 때문임.
		-> 인접한 두 제곱수의 차이는 갈수록 커지기만 함.

	따라서 큰 쪽 제곱수를 가리키는 포인터가 왼 쪽으로 움직여도
	이미 경험해본 왼 쪽 포인터를 다시 앞으로 돌릴 필요가 없음.
	기존의 오른 쪽 포인터 보다 작아졌으므로 보나마나 미달이기때문임.
*/
#include <vector>

using namespace std;

class Solution
{
	using ll = long long;

public:
	bool judgeSquareSum(int c)
	{
		vector<ll> squareNums;
		ll C = c;

		for (ll i = 0; i <= 46340; ++i)
		{
			ll num = i * i;
			if (num <= C)
				squareNums.push_back(num);
			else
				break;
		}
		int lIdx = 0, rIdx = squareNums.size() - 1;
		while (squareNums[rIdx] > c)
		{
			rIdx--;
		}
		while (lIdx <= rIdx) // two Pointer
		{
			while (lIdx <= rIdx)
			{
				ll sum = squareNums[lIdx] + squareNums[rIdx];
				if (sum == c)
					return true;
				else if (sum > c)
					break;
				lIdx++;
			}
			rIdx--;
		}
		return false;
	}
};
