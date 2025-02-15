
#include <iostream>
#include <memory.h>
#include <string>

int A, B, C;
int count[10];
std::string str;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(count, 0, sizeof(count));

	std::cin >> A >> B >> C;
	str = std::to_string(A * B * C);
	for (const auto& num : str)
	{
		count[num - '0']++;
	}
	for (int i = 0; i < 10; ++i)
	{
		std::cout << count[i] << "\n";
	}
}