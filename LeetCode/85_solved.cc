
/*
	matrix[r][c] == 1

	matrix[r - 1][c - 1] ==
	matrix[r - 1][c] ==
	matrix[r][c - 1] ==

	-> matrix[r][c] = ;
*/
#include <iostream>
#include <vector>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")

#include <stack>
using HG = std::pair<int, int>;

using pii = pair<int, int>;	// first : accumulated col, second : accumulated row

class Solution
{
public:
	int maximalRectangle(vector<vector<char>>& matrix)
	{
		const int N = matrix.size();
		const int M = matrix[0].size();
		std::vector<int> histogram(M + 1, 0);
		int result = 0;

		for (int r = 0; r < N; ++r)
		{
			for (int c = 0; c < M; ++c)
			{
				if (matrix[r][c] == '1')
					histogram[c]++;
				else
					histogram[c] = 0;
			}

			stack<HG> st;
			st.push(make_pair(-1, 0));
			for (int i = 0; i <= M; ++i)
			{
				while (st.size() > 1 && st.top().second >= histogram[i])
				{
					HG curBlock = st.top();
					st.pop();
					result = max(result, curBlock.second * (i - st.top().first - 1));
				}
				st.push(make_pair(i, histogram[i]));
			}
		}
		return result;
    }
};
// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}
