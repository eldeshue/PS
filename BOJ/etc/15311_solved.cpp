#include <iostream>

/*
	boj 15311 약 팔기

	문제는 배열을 만드는 것인데, 이 배열은 다음의 조건을 충족해야 함

	"해당 배열의 연속된 부분의 합을 모으면 100만 이하의 모든 정수가 나와야 함."
	"단, 배열의 크기는 2000이 최대임."

	========================================================
	문제 자체가 약팔이였음.

	"1"을 1천개, "1000"을 1천개....
*/
int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;
	std::string result;
	for (int i = 0; i < 1000; ++i)
		result.append("1 ");
	for (int i = 0; i < 1000; ++i)
		result.append("1000 ");
	std::cout << "2000\n" << result;
}