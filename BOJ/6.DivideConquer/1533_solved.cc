
#include <iostream>
#include <vector>

#define MOD 1000003

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

void insertGhostNode(Matrix &m, const int n, int start, int end, int len)
{
	const int offset = n + 4 * start;
	m[start][offset] = 1;
	m[offset + len - 2][end] = 1;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, start, end, time;
	std::cin >> n >> start >> end >> time;
	Matrix graph(n * 5, std::vector<long long>(n * 5, 0));
	for (int i = 0; i < n; ++i)
	{
		const int offset = n + 4 * i;
		graph[offset][offset + 1] = 1;
		graph[offset + 1][offset + 2] = 1;
		graph[offset + 2][offset + 3] = 1;
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			char cost;
			std::cin >> cost;
			cost -= '0';
			if (cost <= 1)
				graph[i][j] = cost;
			else
				insertGhostNode(graph, n, i, j, cost);
		}
	}
	std::cout << pow_div_conq(graph, time)[start - 1][end - 1];
}
