
/*
	boj 8111, 0과 1

	대단히 좋은 문제. ycn 같이 풀었음.
	ycn이 풀이를 알려줘서 풀었음. 발사잉 잘 이해가 안되었는데...
	ycn이는 dp로 풀었고, 나는 그래프로 풀음.

	10의 거듭제곱의 합의 n으로 나눈 나머지가 0이 되도록 하는 순간을 찾기.
	나머지가 0이란 것은 곧 배수를 의미함.
	따라서 나머지를 기록해둘 필요가 있음.
	결과 여부 체크도 있지만, 노드의 성질이 나머지로 구성된다는 점에 의하면
	한 번 경험한 나머지를 갖는 노드는 다시 방문할 필요가 없음.
*/

#include <iostream>
#include <bitset>
#include <tuple>
#include <queue>
#include <string>

using gooNum = std::bitset<1000>;
using node = std::tuple<gooNum, int, int>; // goosaga number, remainder, digit

void printExceptZero(const gooNum &num) // 결과 출력용, 비트셋의 상위 연속된 0비트를 제거해줘야 함.
{
	int idx = 99;
	while (num[idx] == 0) // 0은 무시함
		idx--;
	while (idx >= 0) // 처음으로 0이 아닌 순간 부터 출력함
		std::cout << num[idx--];
	std::cout << '\n';
	return;
}

void bfs(int N)
{
	std::queue<node> Q;
	std::bitset<20000> visited(0); // 방문 여부 체크 비트셋
	gooNum nextNum;
	int nextRemain;

	if (N == 1)
	{
		std::cout << "1\n";
		return;
	}
	Q.push(std::make_tuple(gooNum(1), 1, 0));
	while (!Q.empty())
	{
		const gooNum &curNum = std::get<0>(Q.front());
		const int &curRemain = std::get<1>(Q.front());
		const int &curDigit = std::get<2>(Q.front());

		// depth limit
		if (curDigit == 100)
			break;
		// * 10
		nextNum = curNum << 1;
		nextRemain = (curRemain * 10) % N;
		if (nextRemain == 0) // 찾았다면
		{
			printExceptZero(nextNum);
			return;
		}
		if (visited[nextRemain] == 0) // 미방문이면 추가
		{
			visited[nextRemain] = 1;
			Q.push(std::make_tuple(nextNum, nextRemain, curDigit + 1));
		}
		// * 10 + 1
		nextNum = curNum << 1;
		nextNum[0] = 1;
		nextRemain = (curRemain * 10 + 1) % N;
		if (nextRemain == 0)
		{
			printExceptZero(nextNum);
			return;
		}
		if (visited[nextRemain] == 0)
		{
			visited[nextRemain] = 1;
			Q.push(std::make_tuple(nextNum, nextRemain, curDigit + 1));
		}
		Q.pop();
	}
	// 탐색 실패, ycn에 따르면 BRAK는 발생할 수 없음이 수학적으로 증명되어 있는듯
	// 즉 똑바로 풀기만 했다면 볼 일 없는 메시지임.
	std::cout << "BRAK\n";
	return;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int testNum, n;
	std::cin >> testNum;
	for (int i = 0; i < testNum; ++i)
	{
		std::cin >> n;
		bfs(n);
	}
}
