
/*
	kmp 응용

	문자열 s와 양의 정수 k가 주어짐.
	목표는 s가 부분문자열로 적어도 k회 등장하는 문자열을 만드는데, 그 최소 길이를 구하는 것.

	주어진 조건을 바탕으로 정답의 upper-bound는 s.size() * k임. 단순반복이면 무조건 성립하므로...
	문제는 여기서 어떻게 더 줄일 수 있느냐이다.

	s가 앞뒤로 겹치는 부분이 있어서 중첩이 가능하다면 축소가 가능해짐.
	따라서 kmp의 failure function을 사용하여 중첩가능성을 판단하고, 최대 중첩 길이를 구하면 됨.
*/
#include <iostream>
#include <string>
#include <vector>

int failureFunction(std::string_view sv)
{
	std::vector<int> jmpTable(sv.size() + 1, -1);

	int pos = 1, cnd = 0;
	while (pos < sv.size())
	{
		// match
		if (sv[pos] == sv[cnd])
		{
			jmpTable[pos] = jmpTable[cnd];
		}
		else
		{
			// mismatch, find last candidate
			jmpTable[pos] = cnd;
			while (cnd >= 0 && sv[pos] != sv[cnd])
			{
				cnd = jmpTable[cnd];
			}
		}
		pos++;
		cnd++;
	}
	return cnd;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	long long k;
	std::string s;
	std::cin >> s >> k;
	long long overlap = failureFunction(s);
	std::cout << k * s.size() - (k - 1) * overlap;
}
