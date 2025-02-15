#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

typedef struct jewel
{
	int mass;
	int price;
	jewel(int m, int p) : mass(m), price(p) {};
} jewel;

typedef struct cmp // true일때 정렬을 수행함, 일반적인 comparator랑은 반대로 동작함.
{
	bool operator() (const jewel& j1, const jewel& j2) const
	{
		if (j1.price == j2.price)
		{
			return j1.mass > j2.mass; // 무게, 오름차순, 반대
		}
		else
		{
			return j1.price < j2.price; // 가격, 내림차순, 반대
		}
	}
} cmp;

struct cmp2
{
	bool operator()(const jewel& j1, const jewel& j2) const // 정렬을 위한 comparator
	{
		return j1.mass < j2.mass; // 크기 기준으로 오름차순 
	}
};
int N, K;
std::priority_queue<jewel, std::vector<jewel>, cmp> PQ;
std::multiset<jewel, cmp2> bag;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int m, p;
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> m >> p;
		PQ.push(jewel(m, p));
	}
	for (int i = 0; i < K; ++i)
	{
		std::cin >> m;
		bag.insert(jewel(m, 0));
	}
	//
	int count = 0;
	long long int totalPrice = 0;
	while (count != N && !PQ.empty() && !bag.empty()) // O( N * K )
	{
		const jewel& tgt = PQ.top();
		// std::lower_bound함수는 시간 복잡도가 O(N)임.
		auto itr = bag.lower_bound(tgt);
		if (itr != bag.end())
		{
			totalPrice += tgt.price;
			count++;
			bag.erase(itr);
		}
		PQ.pop();
	}
	
	std::cout << totalPrice;
}