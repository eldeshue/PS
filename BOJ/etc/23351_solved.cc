/*
	BOJ 23351

	시뮬레이션, 다만 단순 구현을 갈기면 TLE

	문제의 목표는 결국 하방을 최대한 높게 유지하는것 -> 고르게 분배해야 함.

	한 그룹 내에서는 운명을 공유함. 따라서 N을 A로 나눌 수 있음(약수임이 조건으로 주어짐)
*/
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K, A, B;
	std::cin >> N >> K >> A >> B;
	N /= A;	// 그룹은 운명 공동체, A는 N의 약수이므로 그룹 당 하나만 고려
	int day = 0;
	while (true)
	{
		++day;
		int min = K + B * (day / N);


		if (min <= day)
		{
			break;
		}
	}
	std::cout << day;
}
