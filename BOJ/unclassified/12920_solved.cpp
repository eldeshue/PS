
/*
	boj 12920, 평범한 배낭 2

	위대한 발상을 옅본 문제. 과연 나는 이 세상 속에서 어떤 존재인가?

	문제에서는 기존의 01 배낭 문제와 다르게, 각 물체의 종류 별로 개수가 주어진다.
	즉 기존에는 가능했던 선택 여부로 dp를 수행하는 것이 불가능하다.

	문제 풀이의 발상은 바로 이 조건을 분해해서 문제를 01 배낭으로 환원하는 것.
	동일한 물체가 복수 등장하는 것으로 발생하는 문제는 바로 다수의 중복이 발생하여 시간 복잡도가 
	폭증하는 것.
	이러한 중복을 제거하기 위해서 n개의 물체를 묶음 상품으로 만든다.
	사실 물체 각각은 전혀 중요하지 않으며, 중요한 것은 몇 개가 선택되느냐의 문제이다.
	그렇기에 물체 각가에 대해서 탐색을 수행할 필요가 없다. 중요한 것은 n개의 물체로 인해서 발생하는
	조합의 가능성이다.

	이러한 조합을 구현하기 위해서 물체의 개수 n을 2진 으로 분해하여 묶음 상품을 만들어낸다. 

*/

/*
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory.h>

using item = std::pair<int, int>;
std::vector<item> items;
int cache[10001];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, -1, sizeof(cache));

	int N, MW, c, v, n;
	std::cin >> N >> MW;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> c >> v >> n;
		// 물체별 개수 조건을 파훼하여 01배낭으로 환원하는 방법.
		// 물체의 개수를 2진수의 합으로 분해하여 이들을 각각 하나의 물체로 묶어냄
		// 이를 통해서 동일한 가격의 물체가 복수 등장하여 발생하는 중복을 제거할 수 있음.
		// 개수 k를 2진수 조합으로 분해
		for (int b = 1; n > 0; b <<= 1)
		{
			const int ix = std::min(b, n);
			items.push_back(std::make_pair(c * ix, v * ix));
			n -= ix;
		}
	}
	cache[0] = 0;
	for (int inum = 0; inum < items.size(); ++inum)
	{
		const int& cost = items[inum].first;
		const int& val = items[inum].second;
		for (int cur_cost = MW; cur_cost >= cost; --cur_cost)
		{
			if (cache[cur_cost - cost] != -1)
			{
				cache[cur_cost] 
					= std::max(cache[cur_cost], cache[cur_cost - cost] + val);
			}
		}
	}
	int result = 0;
	for (int i = 0; i <= MW; ++i)
	{
		result = std::max(result, cache[i]);
	}
	std::cout << result;
}
*/