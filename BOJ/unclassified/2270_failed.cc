// 2270. 하노이 탑
// 시작부터 옮기는 하노이 탑과는 다르게, 중간부터 옮기게 된다.
// 1. 모아야 하는 탑의 위치 -> 현재 가장 큰 값이 위치한 탑.
// 2. 이동 횟수 계산
/*
		1. 현재 최 상단 3개 중, 두 번째로 작은 탑에 나머지를 모음.
		2. 1을 반복.

		n개의 디스크를 옮긴다 -> 2 ^ n - 1회.
*/
#include <iostream>

using uint = unsigned int;
uint pow_of_2[100001];

class tower
{
public:
	uint top_idx;
	uint val[100001];

	tower() : top_idx(0) { val[0] = -1; };
	uint top() const { return val[top_idx]; };
	void push(uint n) {val[++top_idx] = n;};
	void pop() {top_idx--;};
	uint mov_tower_to_me(tower& from)
	{
		// top of the tower 'from' is always 1.
		uint my_top = this->top();
		from.top_idx -= my_top - 1;
		top_idx += my_top - 1;
		val[top_idx] = 1;
		return pow_of_2[my_top - 1] - 1;
	}
};

tower towers[3];

void find_from_to(int &from, int &to, int &rest)
{
	int t[3] = {0, 1, 2};
	if (towers[t[0]].top() > towers[t[1]].top())
		std::swap(t[0], t[1]);
	if (towers[t[1]].top() > towers[t[2]].top())
		std::swap(t[1], t[2]);
	if (towers[t[0]].top() > towers[t[1]].top())
		std::swap(t[0], t[1]);
	from = t[0];
	to = t[1];
	rest = t[2];
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	pow_of_2[0] = 1;
	for (int i = 1; i <= 100000; ++i)
	{
		pow_of_2[i] = (pow_of_2[i - 1] << 1) % 1000000;
	}

	int N, target_tower = 0, cnt = 0;
	std::cin >> N;
	for (int i = 0; i < 3; ++i)
		std::cin >> towers[i].top_idx;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 1; j <= towers[i].top_idx; ++j)
		{
			std::cin >> towers[i].val[j];
		}
		if (towers[i].val[1] == N)
			target_tower = i;
	}
	int from_idx, to_idx, rest_idx;
	find_from_to(from_idx, to_idx, rest_idx);
	while (towers[target_tower].top_idx != N)
	{
		if (towers[rest_idx].top() == towers[to_idx].top() + 1)
		{
			towers[rest_idx].push(towers[to_idx].top());
			towers[to_idx].pop();
			cnt++;
			std::swap(rest_idx, to_idx);
			continue;
		}
		cnt += towers[to_idx].mov_tower_to_me(towers[from_idx]);
		std::swap(to_idx, from_idx);
		// to or rest
		if (towers[to_idx].top() > towers[rest_idx].top())
			std::swap(to_idx, rest_idx);
	}
	// print
	std::cout << target_tower + 1 << '\n' << cnt << '\n';
}
