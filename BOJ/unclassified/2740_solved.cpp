
#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
	const int l1 = m1.size();
	const int l2 = m2.size();
	const int l3 = m2[0].size();
	Matrix result(l1, std::vector<int>(l3, 0));
	for (int r = 0; r < l1; ++r)
	{
		for (int c = 0; c < l3; ++c)
		{
			for (int i = 0; i < l2; ++i)
			{
				result[r][c] += m1[r][i] * m2[i][c];
			}
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& o, const Matrix& m)
{
	for (const auto& v : m)
	{
		for (const int& n : v)
		{
			o << n << ' ';
		}
		o << '\n';
	}
	return o;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, K;
	std::cin >> N >> M;
	Matrix A(N, std::vector<int>(M));
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			std::cin >> A[i][j];
		}
	}
	std::cin >> M >> K;
	Matrix B(M, std::vector<int>(K));
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < K; ++j)
		{
			std::cin >> B[i][j];
		}
	}
	std::cout << A * B;
}