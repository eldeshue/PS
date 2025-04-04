
#include <vector>

/*
	k개의 배낭과 N개의 구슬이 주어짐.
	각 구슬의 무게가 주어짐

	k개의 배낭에 구슬을 나눠서 넣는데
	각 가방은 적어도 하나의 구슬이 들어가야 함
	각 가방에는 연속된 번호의 구슬이 들어가야 함
	즉 구슬 무더기의 분할은 연속적이어야 함

	해당 가방의  cost는 시작 가방과 끝 가방 무게의 합이어야 함.  wow!

	분배를 수행한 후, 각 가방의 cost의 총 합을 구한 다음
	분배 결과 cost의 최댓값과 최솟값의 차이를 구하시오

	n <= 10^5

	split을 하게 된다면, 끊어지는 경계를 기준으로 좌 우의 두 값이 모두 cost에 들어감
	split하는 가상의 선을 기준으로 좌,우의 두 값으로 이루어진 pair를 k - 1개 생성됨
	비용을 순서로 정렬하고 k - 1개를 구해보자

	-> 정렬한다면 n log n
	-> quick selection으로 k - 1개를 구하기만 한다면 n
*/

using namespace std;

#include <algorithm>
class Solution {
public:
	long long putMarbles(vector<int>& weights, int k) {
		int const N = weights.size();

		std::vector<long long> delimBuffer;
		for (int i = 1; i < N; ++i)
			delimBuffer.push_back(weights[i] + weights[i - 1]);

		sort(delimBuffer.begin(), delimBuffer.end());

		long long result = 0;
		for (int i = 0; i < k - 1; ++i)
			result += delimBuffer[N - 2 - i] - delimBuffer[i];
		return result;
	}
};
