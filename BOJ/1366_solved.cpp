// BOJ 1366.
// 23.12.22 기준, 실행 속도 3등. 20ms.
#include <iostream>
#include <memory.h>
#include <string>

int N, M;
int code[6];		// M
int guitar[6];		// N
int pret[6];
int code_cnt[6];

int get_pret(int c, int g);
int ctoi(const std::string& c);
int result = 2e9;

void search(int g_idx)	// recursively, overlap 'for' statememt
{
	if (g_idx == N)
	{
		int max_pret = -2e9, min_pret = 2e9;
		for (int i = 0; i < M; ++i)
		{
			if (code_cnt[i] == 0)
				return;
		}
		for (int i = 0; i < N; ++i)
		{
			if (pret[i] == 0)
				continue;
			max_pret = std::max(max_pret, pret[i]);
			min_pret = std::min(min_pret, pret[i]);
		}
		if (max_pret == -2e9 && min_pret == 2e9)
		{
			result = 0;
			return;
		}
		result = std::min(result, max_pret - min_pret + 1);
		return;
	}
	for (int c_idx = 0; c_idx < M; ++c_idx)
	{
		code_cnt[c_idx]++;
		// 기본 음계
		pret[g_idx] = get_pret(code[c_idx], guitar[g_idx]);
		search(g_idx + 1);
		// 다음 음계, 즉 12단계 위.
		pret[g_idx] = get_pret(code[c_idx], guitar[g_idx]) + 12;
		search(g_idx + 1);
		code_cnt[c_idx]--;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(code_cnt, 0, sizeof(code_cnt));

	std::string input;
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		guitar[i] = ctoi(input);
	}
	for (int i = 0; i < M; ++i)
	{
		std::cin >> input;
		code[i] = ctoi(input);
	}
	// find solution
	search(0);
	// print result
	std::cout << result;
}

int get_pret(int c, int g)
{
	if (c < g)
		c += 12;
	return c - g;
}

int ctoi(const std::string& c)
{
	if (c == "A")
		return 0;
	else if (c == "A#")
		return 1;
	else if (c == "B")
		return 2;
	else if (c == "C")
		return 3;
	else if (c == "C#")
		return 4;
	else if (c == "D")
		return 5;
	else if (c == "D#")
		return 6;
	else if (c == "E")
		return 7;
	else if (c == "F")
		return 8;
	else if (c == "F#")
		return 9;
	else if (c == "G")
		return 10;
	else if (c == "G#")
		return 11;
}

