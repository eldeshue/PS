
#include <iostream>
#include <vector>
#include <string>

using Board = std::vector<std::vector<bool>>;

// 0 ~ 15, convert to string
std::string divide_conquer(const Board& b, int sy, int sx, int len)
{
	int status = 0;
	if (len == 1)	// base case, 0 or 1
	{
		if (b[sy][sx])
			return "1";
		else
			return "0";
	}
	std::string result = "("
		+ divide_conquer(b, sy, sx, len / 2)
		+ divide_conquer(b, sy, sx + len / 2, len / 2)
		+ divide_conquer(b, sy + len / 2, sx, len / 2)
		+ divide_conquer(b, sy + len / 2, sx + len / 2, len / 2)
		+ ")";
	if (result == "(1111)")
		return "1";
	if (result == "(0000)")
		return "0";
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	char c;
	int N;
	std::cin >> N;
	Board b(N, std::vector<bool>(N, false));
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cin >> c;
			b[i][j] = c - '0';
		}
	}
	std::cout << divide_conquer(b, 0, 0, N);
}
