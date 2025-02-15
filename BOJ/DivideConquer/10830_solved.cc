
#include <iostream>
#include <vector>

#define MOD 1000

using Matrix = std::vector<std::vector<int>>;

Matrix operator*(const Matrix &m1, const Matrix &m2)
{
	const int len = m1.size();
	Matrix result(len, std::vector<int>(len, 0));
	for (int r = 0; r < len; ++r)
	{
		for (int c = 0; c < len; ++c)
		{
			for (int i = 0; i < len; ++i)
			{
				result[r][c] += m1[r][i] * m2[i][c];
			}
			result[r][c] %= MOD;
		}
	}
	return result;
}

std::ostream &operator<<(std::ostream &o, const Matrix &m)
{
	for (const auto &v : m)
	{
		for (const int &n : v)
		{
			o << n % MOD << ' ';
		}
		o << '\n';
	}
	return o;
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

	int N;
	long long B;
	std::cin >> N >> B;
	Matrix A(N, std::vector<int>(N));
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < N; ++c)
		{
			std::cin >> A[r][c];
		}
	}
	std::cout << pow_div_conq(A, B);
}
