/*
	BOJ 1015

	역변환을 구성하는 흥미로운 문제.

	B[P[i]] = A[i] 관계에 있을 때,
	A가 주어지고, B가 느슨한 오름차순( <= )이 되는 p를 구하기

	이 때 p는 사전 순으로 가장 앞에 오는 p

	====

	처음에는 A와 B의 관계에서 많이 해매었다.
	그러나 원하는 p를 얻기 위해서는 B의 역변환을 A에 가해야 함을 확인

	A를 정렬해서 B를 만들고, B를 역변환 시켜야 하므로, 인덱스를 붙여줬다.
	이후 A를 순회하면서 B를 참조하여 인덱스를 p로 삼는데, 만약 같은 값을 가리키는 경우
	그 중 가장 작은 것 부터 취한다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <numeric>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;	// N이 50밖에 안됨 
	std::cin >> N;
	std::vector<int> a(N);
	std::vector<std::pair<int, int>> b;
	for (auto& n : a) {
		std::cin >> n;
		b.push_back({ n, -1 });
	}

	std::sort(b.begin(), b.end());
	for (int i = 0; i < N; ++i) {
		b[i].second = i;
	}

	// print
	for (auto& n : a) {
		int result = -1;
		for (int i = 0; i < N; ++i) {
			if (b[i].first == n && b[i].second != -1) {
				result = b[i].second;
				b[i].second = -1;
				break;
			}
		}
		std::cout << result << ' ';
	}
}
