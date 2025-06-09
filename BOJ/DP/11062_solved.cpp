#include <iostream>
#include <vector>

using pii = std::pair<int, int>;
using Veci32 = std::vector<int>;
using Cache = std::vector<std::vector<pii>>;

int update_by_cnt(Cache& c, int l, int r, int cnt, int val)
{
	if (cnt & 1)
	{
		// 근우, first
		return c[l][r].first = val;
	}
	else
	{
		// 명우, second
		return c[l][r].second = val;
	}
}

int get_by_cnt(Cache& c, int l, int r, int cnt)
{
	if (cnt & 1)
	{
		// 근우, first
		return c[l][r].first;
	}
	else
	{
		// 명우, second
		return c[l][r].second;
	}
}

// cnt는 현재 뽑는 횟수를 의미, 근우부터 뽑기에 odd면 근우, event이면 명우
int memoize(Cache& c, Veci32 const& cards, int l, int r, int cnt)
{
	// base case
	if (l == r)
	{
		c[l][r] = { 0, 0 };
		return update_by_cnt(c, l, r, cnt, cards[l]);
	}
	else if (get_by_cnt(c, l, r, cnt) != -1)
	{
		return get_by_cnt(c, l, r, cnt);
	}
	memoize(c, cards, l + 1, r, cnt + 1);
	memoize(c, cards, l, r - 1, cnt + 1);
	int left = cards[l] + get_by_cnt(c, l + 1, r, cnt);	// 왼 쪽 카드를 취했을 때 값
	int right = cards[r] + get_by_cnt(c, l, r - 1, cnt);// 오른 쪽 카드를 취했을 때 값
	if (left > right)	// 어느 쪽을 취했건, 더 큰 값을 얻을 때를 최적의 부분해로 삼는다.
	{
		c[l][r] = c[l + 1][r];
		update_by_cnt(c, l, r, cnt, left);
	}
	else
	{
		c[l][r] = c[l][r - 1];
		update_by_cnt(c, l, r, cnt, right);
	}
	return get_by_cnt(c, l, r, cnt + 1);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--)
	{
		int n;
		std::cin >> n;
		Cache c(n, std::vector<pii>(n, { -1,-1 }));
		Veci32 cards(n, 0);
		for (int i = 0; i < n; ++i)
			std::cin >> cards[i];

		memoize(c, cards, 0, n - 1, 1);

		std::cout << c[0][n - 1].first << '\n';
	}
}