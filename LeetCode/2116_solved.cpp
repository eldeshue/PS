
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")

class Solution
{
public:
	// solution method
	bool canBeValid(string s, string locked)
	{
		const int N = s.size();

		if (N & 1)
			return false;
		// lock 한 position의 value를 제외하곤 모두 다 바꿀 수 있음
		// 바꾸는 횟수가 중요한 조건이 아니라서 lock 이외의 값은 의미가 없음
		// 오직 lock된 위치의 값만 중요함

		// 요점은 lock된 위치의 괄호의 개수로 balance 여부를 확인하는 것임
		// 확정된 괄호의 값들을 기준으로 balance하게 바꿀 수 있느냐 여부를 확인
		int lCnt = 0, rCnt = 0;
		for (int i = 0; i < N; ++i)
		{
			if (locked[i] == '1' && s[i] == ')')
			{
				// 예를 들어서 left to right하게 ')'를 count
				// ')'가 현재 위치를 기준으로 절반 이상이라면
				// 남은 모두를 '('로 바꿔도 balance를 찾을 수 없음
				rCnt++;
				if (rCnt > (i + 1) / 2)
					return false;
			}
		}
		for (int i = N - 1; i >= 0; --i)
		{
			// 마찬가지로 변경을 시도해도 unbalance해서 풀이가 불가능함
			if (locked[i] == '1' && s[i] == '(')
			{
				lCnt++;
				if (lCnt > (N - i) / 2)
					return false;
			}
		}
		return true;
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


