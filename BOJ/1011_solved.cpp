// solved
// 문제에 대한 수학적 접근 자체는 어렵지 않았음
// 하지만 문제의 조건, 입력 범위를 바탕으로 2진 탐색을 적용해야 하는 부분이 포인트임.
#include<iostream>
#include <vector>

std::vector<unsigned int> result;

// binary search
// 차이가 n^2 보다 덜 나도록
unsigned int cal_warp_num(unsigned int distance)
{
	auto ok = [&](unsigned int n) -> bool {
		if (n * n <= distance)
		{
			return true;
		}
		else 
		{
			return false;
		}
	};

	unsigned int low = 0, high = 1 << 16;
	while (low != high) // high not included
	{
		unsigned int mid_value = (low + high + 1) >> 1;
		ok(mid_value) ? low = mid_value : high = mid_value - 1;
	}

	unsigned int left = distance - low * low;

	return 2 * low - 1 + left / low + (((left % low) == 0) ? 0 : 1);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	unsigned int num_of_test, start, end;
	std::cin >> num_of_test;
	result.resize(num_of_test);
	for (auto& elem : result)
	{
		std::cin >> start >> end;
		elem = cal_warp_num(end - start);
	}
	for (const auto& elem : result)
	{
		std::cout << elem << "\n";
	}
} 