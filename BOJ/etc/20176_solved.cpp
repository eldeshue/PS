
#include <functional>
#include <iostream>

#include <algorithm>
#include <cmath>
#include <complex>
#include <numbers>
#include <numeric>
#include <vector>

using base = std::complex<double>;

/*
	Fast Fourier Transform

	non recursive Cooley-Tukey algorithm.
	using bit reversing.
*/
void fft(std::vector<base>& a, const bool isInverse)
{
	const int n = a.size();

	// re-ordering values for cooley-tukey algorithm
	// bit reversing
	for (int i = 1, j = 0; i < n; i++)
	{
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap(a[i], a[j]);
	}

	// divide and conquer, non recursive
	for (int len = 2; len <= n; len <<= 1)
	{
		const double ang = 2 * std::numbers::pi / len * (isInverse ? -1 : 1);
		const base wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len)
		{
			base w(1);	// initial, cos w + 0 * i sin w
			for (int j = 0; j < len / 2; j++)
			{
				// butterfly operation
				base u = a[i + j];	// even
				base v = a[i + j + len / 2] * w;	// odd
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;	// rotation
			}
		}
	}
	if (isInverse)	// for inverse fft
	{
		for (int i = 0; i < n; i++) a[i] /= n;
	}
}

/*
	calculating convolution of two array

	in Math.
	{a1, a2, ..., an-1, an} * {b1, b2, ..., bn-1, bn}
		=> {a1 * bn, a2 * bn-1, ... an * b1}
		-> ex) multiplying two polynomial

	but in Computer Science, order is reversed. like inner product.
	{a1, a2, ..., an-1, an} * {b1, b2, ..., bn-1, bn}
		=> {a1 * b1, a2 * b2, ... an * bn}
		-> ex) image blur

	to use CS style, need to reverse the order
*/
template <typename T>
std::vector<T> convolution(const std::vector<T>& a, const std::vector<T>& b,
	const bool isCS = false)
{
	std::vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	const int M = a.size() + b.size() - 1;
	const int N = [M]() { int n = 1; while (n < M) { n <<= 1; } return n; }();

	if (isCS)
		std::reverse(fb.begin(), fb.end());
	fa.resize(N);	// zero bite padding, power of 2
	fb.resize(N);
	fft(fa, false);	// DFT, Cooley-Tukey algorithm
	fft(fb, false);
	for (int i = 0; i < N; i++)	// point wise multiplication
		fa[i] *= fb[i];
	fft(fa, true);	// inverse DFT 
	std::vector<T> ret(M);
	for (int i = 0; i < M; i++)	// rounding
		ret[i] = static_cast<T>(fa[i].real() + (fa[i].real() > 0 ? 0.5 : -0.5));
	return ret;
}

/*
	Neelde, FFT 연습문제

	3개의 층을 넘어야 함. 각각의 층에는 구멍이 존재하고,
	각 층의 구멍이 1자로 정렬되어야 통과할 수 있음.
	입력으로 층마다 존재하는 구멍의 좌표가 주어짐.

	1렬로 정렬 가능한 구멍의 조합은 몇 개 있을까?

	a, b, c의 3개의 층이 순서대로 있다고 하면, 세 벽은 평행하고,
	a와 b 그리고 b와 c 벽 사이의 거리는 일정하다.

	따라서, 각 벽의 세 구멍이 일직선 상에 존재한다면, Xa + Xc == 2 * Xb 가 성립할 것이다.

	그러므로, a와 c의 x좌표에 따른 구멍의 개수가 1이므로,

	구멍의 좌표값 Xa Xc를 차수로 삼고, 구멍이 하나 있으므로
	그 계수를 1로 삼는 다항식을 구성하고,

	이를 서로 convolution하면 Xa + Xc 차수에 따른 계수를 통해서
	좌표를 통과하는 조합의 수를 얻을 수 있겠다.

	좌표의 범위가 -30000에서 +30000이므로,
	이를 보정하기 위해서 offset으로 30000 을 주어서 계산해야 하겠다.
*/

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	const constexpr int OFFSET = 30000;
	const constexpr size_t SIZE = 60001;
	int Nu, Nm, Nl, temp;

	std::cin >> Nu;
	std::vector<int> front_layer(SIZE, 0);
	for (int i = 0; i < Nu; ++i) {
		std::cin >> temp;
		front_layer[temp + OFFSET] = 1;
	}

	std::cin >> Nm;
	std::vector<int> mid_layer(Nm);
	for (int i = 0; i < Nm; ++i) {
		std::cin >> mid_layer[i];
		mid_layer[i] += OFFSET;
	}

	std::cin >> Nl;
	std::vector<int> back_layer(SIZE, 0);
	for (int i = 0; i < Nl; ++i) {
		std::cin >> temp;
		back_layer[temp + OFFSET] = 1;
	}

	// fft
	std::vector<int> doubled_mid = convolution(front_layer, back_layer);

	// count result;
	int result = 0;
	for (int const n : mid_layer) {
		result += doubled_mid[2 * n];
	}
	std::cout << result << std::endl;
}