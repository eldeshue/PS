
#include <iostream>
#include <vector>

int N;
std::vector<int> buffer;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int input;
	std::cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= i; ++j)
		{
			std::cin >> input;
			buffer.push_back(input);
		}
	}

	int pos = buffer.size() - 2;
	for (int level = N; level >= 2; --level) // O(n ^ 2), O( sizeof(buffer) )
	{
		for (int i = 0; i < level - 1; ++i)
		{
			int l = buffer[pos];
			int r = buffer[pos + 1];
			buffer[pos - level + 1] += (r > l) ? r : l;
			pos--;
		}
		pos--;
	}

	std::cout << buffer[0];
}