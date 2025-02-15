
#include <iostream>
#include <map>


int prime[] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 
	31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
	73, 79, 83, 89, 97,	101, 103, 107, 109, 113, 
	127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 
	179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
	233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
	283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
	353, 359, 367, 373, 379, 383, 389, 397, 401
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int numTest, N, idx;
	std::cin >> numTest;
	for (int i = 0; i < numTest; ++i)
	{
		std::map<int, int> result;
		std::cin >> N;
		idx = 0;
		while (N != 1)
		{
			while (N % prime[idx] == 0)
			{
				result[prime[idx]]++;
				N /= prime[idx];
			}
			idx++;
			if (idx >= 78)
				break;
		}

		for (const auto& entry : result)
		{
			std::cout << entry.first << ' ' << entry.second << '\n';
		}
	}
}