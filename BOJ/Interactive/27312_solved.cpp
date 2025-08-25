/*
	BOJ 27312

	N개의 속성 중, 어느 하나만 다르면 겹치지 않는다.

	M명의 사람, Q번의 질문인데, M <= Q이다.

	적어도 모든 사람에게 하나씩은 물어볼 수 있다.

	속성의 종류 N은 Q <= N이다.

	=================================================

	모두에게 각자 1개씩 서로 다른 항목을 물어본다.

	이렇게 구성된 각 항목의 점수에 대하여 모두 다른 조합을 만든다(더하기1 혹은 빼기 1)

	물어보지 못한 항목은 1로 통일한다.

	이렇게 구성하면 모두와 적어도 하나는 다른 항목을 가진다.
*/
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int M, N, Q; // people, attribute, query
	std::cin >> M >> N >> Q;
	std::vector<int> limits(N);
	for (auto& l : limits)
		std::cin >> l;

	// query
	std::vector<int> result(N, 1);
	for (int i = 0; i < M; ++i)
	{
		std::cout << "? " << i + 1 << ' ' << i + 1 << std::endl;
		std::cin >> result[i];
		result[i] = result[i] % limits[i] + 1;
	}

	// result
	std::cout << "! ";
	for (auto const& r : result)
	{
		std::cout << r << ' ';
	}
	std::cout << std::endl;
}