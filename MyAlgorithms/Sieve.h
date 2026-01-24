
#pragma once

#include <vector>

// solver of finding prime number table
// Sieve of Eratosthenes with Wheeling.
class Sieve {
private:
	Sieve() = delete;
	Sieve(Sieve const&) = delete;
	Sieve& operator=(Sieve const&) = delete;

	std::vector<bool> prime;

	inline void sparse_init(
		size_t start,
		size_t stride,
		bool val) {
		for (size_t i = start; i < prime.size(); i += stride) {
			prime[i] = val;
		}
	}

public:
	// Sieve of Erastosthenes with Wheeling 
	explicit Sieve(size_t N) : prime(N + 1, false) {
		if (N < 2) return;
		if (N >= 2) prime[2] = true;
		if (N >= 3) prime[3] = true;
		if (N < 5) return;

		// 5이하의 두 소수 2,3 check
		prime[2] = prime[3] = true;

		// 5이상의 모든 소수는 6K +- 1의 형태를 가짐.
		// 이들에 대해서만 sieve를 수행
		sparse_init(5, 6, true);
		sparse_init(7, 6, true);
		for (size_t p = 5, p_sq = 25; p_sq <= N;) {
			// 6k +- 1의 꼴을 갖는, 다음 소수 후보를 구하는 gap
			size_t gap = (p + 3) % 6; // 6k - 1이면 +2, 6k + 1이면 +4 해줘야 함

			// if p is prime, erase mult of p
			if (prime[p] == true) {
				// 6k +- 1인 값들만 지워야 함
				// 6의 배수가 아닌 p의 배수는 이미 지워짐
				// 따라서 stride에 6을 곱해서 6배 빠르게 계산하기
				size_t stride = p * 6;
				sparse_init(p_sq, stride, false);

				// 만약 p가 6k + 1의 꼴이었다면 위에서는 6k+1만 지웠음
				// p의 배수 중에서 6k - 1의 꼴도 지워줘야 함
				// stride를 6배 크게 잡았기 때문
				// p * (p + gap) = p^2 + p * gap
				if (p_sq + gap * p <= N)
					sparse_init(p_sq + gap * p, stride, false);
			}
			p += gap;
			p_sq = p * p;	// p squared
		}
	}
	Sieve(Sieve&& other) noexcept : prime(std::move(other.prime)) {}
	Sieve& operator=(Sieve&& other) noexcept {
		if (this != &other) {
			prime = std::move(other.prime);
		}
		return *this;
	}

	bool is_prime(uint32_t n) const {
		return n < prime.size() && prime[n];
	}

	std::vector<bool> const& data() const { return prime; }
};

