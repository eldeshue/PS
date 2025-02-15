
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	int L, N;
	std::cin >> L;
	std::vector<int> s(L);
	for (int i = 0; i < L; ++i)
		std::cin >> s[i];
	std::cin >> N;
	std::sort(s.begin(), s.end());
	auto rItr = std::upper_bound(s.begin(), s.end(), N);
	if (rItr == s.end() || *(rItr - 1) == N)
		rItr--;
	const int M = *rItr;
	auto lItr = std::lower_bound(s.begin(), s.end(), N);
	if (*lItr > N)
		lItr--;
	const int m = *lItr;
	std::cout << std::max((M - N) * (N - m) - 1, 0);
}