#include <iostream>
#include <vector>

using pii = std::pair<int, int>;
using Veci32 = std::vector<int>;
using Cache = std::vector<std::vector<pii>>;

int update_by_cnt(Cache& c, int l, int r, int cnt, int val)
{
	if (cnt & 1)
	{
		// �ٿ�, first
		return c[l][r].first = val;
	}
	else
	{
		// ���, second
		return c[l][r].second = val;
	}
}

int get_by_cnt(Cache& c, int l, int r, int cnt)
{
	if (cnt & 1)
	{
		// �ٿ�, first
		return c[l][r].first;
	}
	else
	{
		// ���, second
		return c[l][r].second;
	}
}

// cnt�� ���� �̴� Ƚ���� �ǹ�, �ٿ���� �̱⿡ odd�� �ٿ�, event�̸� ���
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
	int left = cards[l] + get_by_cnt(c, l + 1, r, cnt);	// �� �� ī�带 ������ �� ��
	int right = cards[r] + get_by_cnt(c, l, r - 1, cnt);// ���� �� ī�带 ������ �� ��
	if (left > right)	// ��� ���� ���߰�, �� ū ���� ���� ���� ������ �κ��ط� ��´�.
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