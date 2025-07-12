/*
	BOJ 28277

	union-find의 union by rank와 유사한 개념의 문제.

	==================================================================

	 "Small-to-large merging" 또는 "Union by size" 휴리스틱(heuristic)

	 왜 효율적인가? (Amortized Analysis)

	 "Union by size"의 효율성은 분할 상환 분석(Amortized Analysis)을 통해 증명할 수 있습니다. 핵심 아이디어는
	 다음과 같습니다.

	 "각각의 원소는 몇 번이나 다른 집합으로 복사(이동)되는가?"


	 1. 어떤 원소 x가 속한 집합 S가 다른 집합 T로 합쳐진다고 가정해 봅시다.
	 2. "Union by size" 전략에 따라, S의 원소들이 T로 복사되려면 size(S) <= size(T) 여야 합니다.
	 3. 복사가 끝나면, 원소 x는 이제 새로운 집합 S ∪ T에 속하게 됩니다. 이 새로운 집합의 크기는 최소 2 * size(S)
	 입니다. (원래 S의 크기 + S보다 크거나 같은 T의 크기)
	 4. 즉, 원소가 한 번 복사될 때마다, 그 원소가 속한 집합의 크기는 최소 2배가 됩니다.

	 총 원소의 개수가 N개일 때, 특정 원소가 속한 집합의 크기는 N을 초과할 수 없습니다.
	 따라서 어떤 원소가 k번 복사되었다면, 그 집합의 크기는 최소 2^k가 됩니다.

	 2^k <= N 이므로, 양변에 로그를 취하면 k <= log₂(N) 이 됩니다.

	 결론적으로, 모든 원소는 전체 병합 과정 동안 최대 O(log N)번만 복사됩니다.

	 따라서 모든 원소를 한 집합으로 모으는 최종 비용은 O(N log N)
*/
#include <iostream>
#include <unordered_set>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, Q;
	std::cin >> N >> Q;
	// init data structure
	// init set
	std::vector<std::unordered_set<int>*> sets(N + 1, nullptr);
	for (int i = 1; i <= N; ++i)
	{
		sets[i] = new std::unordered_set<int>();
		int n, s;
		std::cin >> n;
		for (int j = 0; j < n; ++j)
		{
			std::cin >> s;
			sets[i]->insert(s);
		}
	}

	// handle queries
	int q, a, b;
	for (int _ = 0; _ < Q; ++_)
	{
		std::cin >> q;
		if (q == 1)
		{
			std::cin >> a >> b;
			// merge a and b
			// move small one to big one
			if (sets[b]->size() > sets[a]->size())
			{
				// move a to b
				sets[b]->insert(sets[a]->begin(), sets[a]->end());
				sets[a]->clear();

				// swap
				std::swap(sets[a], sets[b]);
			}
			else
			{
				sets[a]->insert(sets[b]->begin(), sets[b]->end());
				sets[b]->clear();
			}
		}
		else {
			std::cin >> a;
			std::cout << sets[a]->size() << '\n';
		}
	}
}