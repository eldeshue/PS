
#include <iostream>
#include <algorithm>
#include <queue>
#include <tuple>

typedef std::tuple<int, int, int> seg;

struct comp
{
	bool operator() (const seg& s1, const seg& s2)
	{
		long long int l1 = std::get<2>(s1) + 1;
		long long int l2 = std::get<2>(s2) + 1;
		long long int r1 = std::get<1>(s1) - std::get<0>(s1) -l1 + 2;
		long long int r2 = std::get<1>(s2) - std::get<0>(s2) -l2 + 2;
		if ((l1 * r1) == (l2 * r2))
		{
			return std::get<0>(s1) > std::get<0>(s2);
		}
		return (l1 * r1) > (l2 * r2);
	}
};

int L, N;
std::vector<int> S;
std::priority_queue<seg, std::vector<seg>, comp> PQ;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::queue<int> result;

	std::cin >> L;
	S.resize(L + 1);
	S[0] = 0;
	for (int i = 1; i <= L; ++i)
	{
		std::cin >> S[i];
	}
	std::cin >> N;

	std::sort(S.begin(), S.end());
	int maxS = S[L];

	// build priority queue
	for (int i = 1; i <= L; ++i)
	{
		PQ.push(std::make_tuple(S[i], S[i], 0));
		if (S[i - 1] + 1 <= S[i] - 1)
		{
			PQ.push(std::make_tuple(S[i - 1] + 1, S[i] - 1, 0));
		}
	}

	int cnt = 0;
	while(!PQ.empty())
	{
		int curR = std::get<2>(PQ.top());
		int curS = std::get<0>(PQ.top());
		int curE = std::get<1>(PQ.top());
		PQ.pop();
		int s = curS + curR;
		int e = curE - curR;
		if (cnt <= N && cnt <= maxS)
		{
			result.push(s);
			++cnt;
		}
		else
		{
			break;
		}
		if (s == e)
		{
			continue;
		}
		if (cnt <= N && cnt <= maxS)
		{
			result.push(e);
			++cnt;
		}
		else
		{
			break;
		}

		if ((s + 1) <= (e - 1))
		{
			PQ.push(std::make_tuple(curS, curE, curR + 1));
		}
	}

	for (cnt = maxS + 1; cnt <= N; ++cnt)	// 출력해야 하는 개수 N이 범위 바깥, maxS 보다 큰 값들
	{
		result.push(cnt);
	}

	for (int i = 0; i < N; ++i)
	{
		std::cout << result.front() << " ";
		result.pop();
	}
}