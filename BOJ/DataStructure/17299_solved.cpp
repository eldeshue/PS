
#include <iostream>

#include <array>
#include <stack>
#include <vector>

std::array<int, 1000001> freq{ 0 };

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<int> nums(N);
	for (int& n : nums)
		std::cin >> n;

	// count freq
	for (int const n : nums)
		++freq[n];

	// monoton increasing stack
	std::stack<int> st;
	std::vector<int> result(N);
	for (int i = N - 1; i >= 0; --i)
	{
		while (!st.empty() && freq[st.top()] <= freq[nums[i]])
			st.pop();
		if (st.empty())
			result[i] = -1;
		else
			result[i] = st.top();
		st.push(nums[i]);
	}

	// print
	for (int const n : result)
		std::cout << n << ' ';
}