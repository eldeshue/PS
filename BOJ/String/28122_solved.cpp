/*
	BOJ 28122

	문제의 insight, 바로 한 원소를 고를 때 마다, lsb가 고정된다.
	만약 첫 원소로 3을 고르면, 그 이후에 고르는 모든 원소는 홀수여야 한다.
	만약 두 번째 고른 원소가 5라면, 그 이후에 고르는 모든 원소는 4로 나눈 나머지가 1이다.

	즉 원소를 하나 고를 때 마다 lsb부터 하나씩 고정된다.

	===================================================

	binary trie를 만든 다음, 이 binary trie를 순회하면서 가능한 많은 개수를 count

	dfs할 때, depth가 증가하면 lsb부터 bit를 결정하는 행위
	실제 선택할 원소는 leaf에 있고, 중간 노드에는 해당 bit까지 일치하는 총 원소의 개수만 있음

	따라서, 선택한 셈 치고, 대출을 감행함.
	이후 depth를 더해가면서 해당 대출을 해소해나가면 됨.
	즉, 진짜 고르면 됨.

	이 때 실제로 고르는 인원을 몰라도 되는데, 그 이유는
	지금까지 선택한 bit까지만 일치하면 되기 때문임.
*/
#include <iostream>
#include <array>
#include <vector>

using ll = long long;

class Solver
{
private:
	Solver() = delete;
	Solver(Solver const&) = delete;
	Solver& operator=(Solver const&) = delete;

	using Node = std::array<int, 2>;
	std::vector<int> freq;
	std::vector<Node> trie;

	int last_used_idx;

public:
	Solver(size_t const size) :
		freq(size, 0),
		trie(size, { -1, -1 }),
		last_used_idx(0) {
	};
	~Solver() {};

	// 실제 원소 x가 leaf에 가도록 trie에 node 추가하기
	void add_node(ll const x)
	{
		int cur_node = 0;
		++freq[0];
		for (int pos = 0; pos < 64; ++pos)
		{
			int i = !!(x & (1LL << pos));
			int& next_node = trie[cur_node][i];
			if (next_node == -1)	// add node to trie
			{
				next_node = ++last_used_idx;
			}
			++freq[next_node];	// frequency count
			cur_node = next_node;
		}
	}

	/*
		trie의 leaf에 실물 x를 둘 예정임.
		따라서, x를 하나 고른 셈 치고, 다음 depth로 이동한다고 봄
		그렇게 고른 셈 치는 아이템을 debt라 하겠음

		debt는 curnode를 root로 하는 trie에서 반드시 찾아야 하는
		x의 개수
	*/
	int solve(int const cur_node, int const debt)
	{
		int result = 0;

		if (trie[cur_node][0] == -1 && trie[cur_node][1] == -1)
		{
			// base case
			// leaf_node
			return std::max(freq[cur_node] - debt, 0);
		}
		for (int next = 0; next < 2; ++next)
		{
			int const next_node = trie[cur_node][next];
			int const opposite_node = trie[cur_node][(next + 1) & 1];
			if (next_node != -1)
			{
				// 빚을 청산해야 함
				// 빚의 청산은 반대편에서 할 수 있음
				int  pick_count = 0;
				if (opposite_node != -1)
					pick_count = std::min(debt, freq[opposite_node]);
				int const new_debt = debt + 1 - pick_count;
				if (new_debt <= freq[next_node])
				{
					result = std::max(result,
						1 + solve(next_node, new_debt));
				}
			}
		}

		return result;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	ll x;
	std::cin >> N;
	Solver s(64 * N);
	while (N--)
	{
		std::cin >> x;
		s.add_node(x);
	}
	std::cout << s.solve(0, 0);
}