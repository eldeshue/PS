
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <functional>
class Solution
{
private:
	using Dir = pair<int, int>;
	static constexpr Dir dirs[4]
		= {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
public:
	// solution method
	int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls)
	{
		vector<vector<char>> board(m, vector<char>(n, 'o'));
		int result = m * n;
		auto inRange = [&](const int r, const int c) -> bool
			{
				return (0 <= r && r < m) && (0 <= c && c < n);
			};
		auto eraseWithDir = [&](const int sR, const int sC, const Dir d)
			{
				for (int r = sR + d.first, c = sC + d.second;
					inRange(r, c);
					r += d.first, c += d.second)
				{
					if (board[r][c] == 'w' || board[r][c] == 'g')
					{
						break;
					}
					else if (board[r][c] == 'o')
					{
						--result;
						board[r][c] = 'x';
					}
				}
			};
		auto eraseUp = bind(eraseWithDir, placeholders::_1, placeholders::_2, dirs[0]);
		auto eraseDw = bind(eraseWithDir, placeholders::_1, placeholders::_2, dirs[1]);
		auto eraseR = bind(eraseWithDir, placeholders::_1, placeholders::_2, dirs[2]);
		auto eraseL = bind(eraseWithDir, placeholders::_1, placeholders::_2, dirs[3]);

		for (const auto &wall : walls)
		{
			board[wall[0]][wall[1]] = 'w';
			result--;
		}
		for (const auto& guard : guards)
		{
			board[guard[0]][guard[1]] = 'g';
			result--;
		}
		for (const auto &guard : guards)
		{
			eraseUp(guard[0], guard[1]);
			eraseDw(guard[0], guard[1]);
			eraseR(guard[0], guard[1]);
			eraseL(guard[0], guard[1]);
		}
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


