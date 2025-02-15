
#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string s;
	std::cin >> s;
	int const N = s.size();
	int q;
	std::cin >> q;
	// pre processing
	std::vector<std::vector<int>> prefixSum(N, std::vector<int>(26, 0));
	prefixSum[0][s[0] - 'a'] = 1;
	for (int i = 1; i < N; ++i)
	{
		for (int j = 0; j < 26; ++j)
		{
			prefixSum[i][j] = prefixSum[i - 1][j];
		}
		++prefixSum[i][s[i] - 'a'];
	}


	for (int i = 0; i < q; ++i)
	{
		char c;
		int l, r;
		std::cin >> c >> l >> r;
		if (l == 0)
			std::cout << prefixSum[r][c - 'a'] - 0 << '\n';
		else
			std::cout << prefixSum[r][c - 'a'] - prefixSum[l - 1][c - 'a'] << '\n';
	}

}