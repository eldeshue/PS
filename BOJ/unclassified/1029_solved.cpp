
#include <iostream>
#include <memory.h>

int N;
int price[15][15];	// graph with adjacent node, price[prev owner][new owner]
int cache[10][15][1 << 15];	// curPrice, curOwner, possible record.

int DP(int curPrice, int owner, int record)
{
	int& tgt = cache[curPrice][owner][record];
	// base case, no where to go, 
	// cache hit
	if (tgt != -1)
	{
		return tgt;
	}
	// cache miss
	else
	{
		tgt = 0;
		for (int next = 0; next < N; ++next)
		{
			// selling price has to be more expensive than current price, not visited
			if ( curPrice <= price[owner][next] && (record & (1 << next)) == 0 )	// verify
			{	
				tgt = std::max(tgt, DP(price[owner][next], next, record | (1 << next)));
			}
		}
		return ++tgt;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	for (int i = 0; i < 10; ++i)
	{
		memset(cache[i], -1, sizeof(cache[i]));
	}

	std::string temp;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> temp;
		for (int j = 0; j < N; ++j)
		{
			price[i][j] = temp[j] - '0';
		}
	}

	std::cout << DP(0, 0, 1); // 모든 순회는 1번 노드에서 시작하므로, bit는 1에서 시작
}