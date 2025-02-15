
/*
	fft를 활용한 큰 수 곱셈

	fft를 활용했기에 O(n log n)이라고 생각하지만, 사실은 O(n^2)임.
	그 이유는 carry를 처리하는 과정에서 덧셈이 발생하는데, 이 부분을
	큰 수로 처리해야 되는 수준이 되면 큰 수의 덧셈이 O(n)이라서
	전체적으로 O(n^2)가 되어버림.

	FFT의 위대함이여....
*/
#include <iostream>

//=================================================

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


//=================================================

#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string s1, s2;
	std::cin >> s1 >> s2;

	if (s1 == "0" || s2 == "0")
	{
		std::cout << "0";
		return 0;
	}
	else
	{
		// reverse
		std::reverse(s1.begin(), s1.end());
		std::reverse(s2.begin(), s2.end());

		// transform to the vector
		std::vector<int> num1(s1.size()), num2(s2.size());
		std::transform(s1.begin(), s1.end(), num1.begin(), [](const char c) {return c - '0'; });
		std::transform(s2.begin(), s2.end(), num2.begin(), [](const char c) {return c - '0'; });

		// convolution
		std::vector<int> result = convolution(num1, num2);

		// handling carry
		int carry = 0;
		for (int i = 0; i < result.size(); ++i)
		{
			carry += result[i];
			result[i] = carry % 10;
			carry /= 10;
		}
		while (carry)
		{
			result.push_back(carry % 10);
			carry /= 10;
		}

		// print reverse order
		std::for_each(result.rbegin(), result.rend(), [](const int n) { std::cout << n; });
	}
}