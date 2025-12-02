
/*
	BOJ 25672

	N이 홀수면, 입력으로 들어온 combination의 flip한 combination을 주면 됨.
	이러면 홀수개 입력에는 짝수개가 반환되고, 짝수개 입력에는 홀수개가 반환되는 상호 1대1 대응이 가능함.
	그렇다면, N이 짝수라면??? 짝수일 때에는 어떻게 해야 할까?

	====================================================================== n이 짝수인 경우

	n을 포함하는 경우와 n을 포함하지 않는 경우로 구분하자.

	만약 입력으로 들어온 case에 대하여 n이 포함되지 않다면
	마치 n이 n-1까지인것 처럼 동작한다. 그러면 홀수 짝수 1대1 대응이 성립한다.

	만약 입력으로 들어온 case에 대하여 n이 포함된다면?
	반드시 상대방도 n을 포함하도록 한다.

	즉, n이 없으면 없는대로 matching하고, n이 있다면 있는 대로 matching한다.
	이렇게 하는 것으로 홀-짝 매칭이 성립한다.

	굳이 분류하자면 해구축하기
*/
#include <iostream>
#include <array>
#include <string>
#include <deque>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::array<bool, 51> freq;
	std::deque<int> buffer;
	int t, n, k, a;
	std::cin >> t;
	while (t--)
	{
		std::fill(freq.begin(), freq.end(), false);
		std::cin >> n >> k;
		for (int i = 0; i < k; ++i)
		{
			std::cin >> a;
			freq[a] = true;
		}

		for (int i = 1; i < n; ++i)
		{
			if (!freq[i])
			{
				buffer.push_back(i);
			}
		}

		if ((n & 1) ^ freq[n])
		{
			buffer.push_back(n);
		}

		// print
		std::cout << n << ' ' << buffer.size() << '\n';
		for (auto const ai : buffer)
			std::cout << ai << ' ';
		std::cout << '\n';
		buffer.clear();
	}
}
