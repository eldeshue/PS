

#include <iostream>
#include <vector>

#define MOD 1000000007

using Matrix = std::vector<std::vector<long long>>;

Matrix operator*(const Matrix &m1, const Matrix &m2)
{
	Matrix result(m1.size(), std::vector<long long>(m2[0].size(), 0));
	for (int r = 0; r < result.size(); ++r)
	{
		for (int c = 0; c < result[0].size(); ++c)
		{
			for (int i = 0; i < m2.size(); ++i)
			{
				result[r][c] = (result[r][c] + (m1[r][i] * m2[i][c]) % MOD) % MOD;
			}
		}
	}
	return result;
}

// divide and conquer
Matrix pow_div_conq(const Matrix &a, long long b)
{
	if (b == 1)
		return a;
	Matrix result = pow_div_conq(a, b / 2);
	result = result * result;
	if (b & 1)
		result = result * a;
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	const Matrix graph({{0, 1, 1, 0, 0, 0, 0, 0},
						{1, 0, 1, 1, 0, 0, 0, 0},
						{1, 1, 0, 1, 1, 0, 0, 0},
						{0, 1, 1, 0, 1, 1, 0, 0},
						{0, 0, 1, 1, 0, 1, 1, 0},
						{0, 0, 0, 1, 1, 0, 0, 1},
						{0, 0, 0, 0, 1, 0, 0, 1},
						{0, 0, 0, 0, 0, 1, 1, 0}});

	int D;
	std::cin >> D;
	std::cout << pow_div_conq(graph, D)[0][0];
}
