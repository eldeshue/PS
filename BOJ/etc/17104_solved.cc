
#include <iostream>

// ==================================

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
void fft(std::vector<base> &a, const bool isInverse)
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
			base w(1); // initial, cos w + 0 * i sin w
			for (int j = 0; j < len / 2; j++)
			{
				// butterfly operation
				base u = a[i + j];				 // even
				base v = a[i + j + len / 2] * w; // odd
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen; // rotation
			}
		}
	}
	if (isInverse) // for inverse fft
	{
		for (int i = 0; i < n; i++)
			a[i] /= n;
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
std::vector<T> convolution(const std::vector<T> &a, const std::vector<T> &b,
						   const bool isCS = false)
{
	std::vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	const int M = a.size() + b.size() - 1;
	const int N = [M]()
	{ int n = 1; while (n < M) { n <<= 1; } return n; }();

	if (isCS)
		std::reverse(fb.begin(), fb.end());
	fa.resize(N); // zero bite padding, power of 2
	fb.resize(N);
	fft(fa, false); // DFT, Cooley-Tukey algorithm
	fft(fb, false);
	for (int i = 0; i < N; i++) // point wise multiplication
		fa[i] *= fb[i];
	fft(fa, true); // inverse DFT
	std::vector<T> ret(M);
	for (int i = 0; i < M; i++) // rounding
		ret[i] = static_cast<T>(fa[i].real() + (fa[i].real() > 0 ? 0.5 : -0.5));
	return ret;
}

// ====================================================

using ll = long long;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// preprocessing
	constexpr int MAX_VAL = 1000000;
	std::vector<ll> prime(MAX_VAL + 1, 0), evenSemiPrime(MAX_VAL + 1, 0);

	// get prime numbers using erastosthenes
	auto flip_with_stride = [&](const int start, const int stride, const int val)
	{
		for (int i = start; i < MAX_VAL; i += stride)
			prime[i] = val;
	};
	// eratosthenes
	prime[2] = 1;
	prime[3] = 1;
	flip_with_stride(5, 6, 1);
	flip_with_stride(7, 6, 1);
	for (int i = 5, j = 25; j < MAX_VAL;)
	{
		int nxt = (i - 3) % 6;
		if (prime[i] == 1)
		{
			int addi = i * 6;
			flip_with_stride(j, addi, 0);
			flip_with_stride(nxt * i + j, addi, 0);
		}
		i += nxt;
		j = i * i;
	}

	// convolution
	std::vector<ll> result = convolution(prime, prime);

	// handling query
	int T, query;
	std::cin >> T;
	while (T--)
	{
		std::cin >> query;
		std::cout << result[query] / 2 + (result[query] % 2) << '\n';
	}
}
