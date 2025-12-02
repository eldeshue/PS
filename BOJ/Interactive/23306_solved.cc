
/*
	BOJ 23306

	값이 0과 1밖에 존재하지 않는 관계로, 대부분의 경우 상승하면 하강이 동반됨.

	시작과 끝만 물어보면 되는구나?

	0시작인데 1로 끝나면 상승이 더 많고

	1시작인데 0으로 끝나면 하강이 더 많고

	둘이 같으면 동일하구나?
*/
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, start, end;
	std::cin >> N;
	std::cout << "? 1" << std::endl;
	std::cin >> start;
	std::cout << "? " << N << std::endl;
	std::cin >> end;
	std::cout << "! " << end - start << std::endl;
}
