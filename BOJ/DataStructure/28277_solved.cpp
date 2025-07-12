/*
	BOJ 28277

	union-find�� union by rank�� ������ ������ ����.

	==================================================================

	 "Small-to-large merging" �Ǵ� "Union by size" �޸���ƽ(heuristic)

	 �� ȿ�����ΰ�? (Amortized Analysis)

	 "Union by size"�� ȿ������ ���� ��ȯ �м�(Amortized Analysis)�� ���� ������ �� �ֽ��ϴ�. �ٽ� ���̵���
	 ������ �����ϴ�.

	 "������ ���Ҵ� �� ���̳� �ٸ� �������� ����(�̵�)�Ǵ°�?"


	 1. � ���� x�� ���� ���� S�� �ٸ� ���� T�� �������ٰ� ������ ���ô�.
	 2. "Union by size" ������ ����, S�� ���ҵ��� T�� ����Ƿ��� size(S) <= size(T) ���� �մϴ�.
	 3. ���簡 ������, ���� x�� ���� ���ο� ���� S �� T�� ���ϰ� �˴ϴ�. �� ���ο� ������ ũ��� �ּ� 2 * size(S)
	 �Դϴ�. (���� S�� ũ�� + S���� ũ�ų� ���� T�� ũ��)
	 4. ��, ���Ұ� �� �� ����� ������, �� ���Ұ� ���� ������ ũ��� �ּ� 2�谡 �˴ϴ�.

	 �� ������ ������ N���� ��, Ư�� ���Ұ� ���� ������ ũ��� N�� �ʰ��� �� �����ϴ�.
	 ���� � ���Ұ� k�� ����Ǿ��ٸ�, �� ������ ũ��� �ּ� 2^k�� �˴ϴ�.

	 2^k <= N �̹Ƿ�, �纯�� �α׸� ���ϸ� k <= log��(N) �� �˴ϴ�.

	 ���������, ��� ���Ҵ� ��ü ���� ���� ���� �ִ� O(log N)���� ����˴ϴ�.

	 ���� ��� ���Ҹ� �� �������� ������ ���� ����� O(N log N)
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