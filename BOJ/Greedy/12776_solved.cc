
/*
	BOJ 12776

	n개의 드라이브와 그 용량이 주어짐.
	각 드라이브를 포맷해서 새로운 용량의 드라이브를 얻을 예정인데, 포맷을 위해서는 기존의 데이터를 옮겨둬야 함.
	이를 위해서, 추가적으로 메모리가 필요할 수 있는데, 추가 메모리의 최솟값은 얼마인가?

	포매팅을 수행해서 여분 용량을 얻으면, 이 얻어낸 여분 용량을 최대한 활용하는게 핵심임.

	N : 10^6, 목표는 O(N log N)

	==============================================================================

	최초 상태는 모든 드라이브의 데이터가 full 상태이므로, 어느 한 드라이브의 용량 째로 추가할 필요가 있음.

	즉, 첫 포맷 드라이브는 내용물을 몽땅 비워서 다른 곳으로 옮겨야 함.
	=============================================================================

	포맷 이후의 용량이 감소할 수도 있다. 이 부분을 고려하지 못했음.

	요점은 되도록 extra를 사용하지 않으면서, 최대한 포맷 후의 gain을 활용하여 문제를 해결하는 것.
	포맷 후에 가용 공간이 감소할 수도 있다.
	-> 가용 공간을 감소시키는 문제를 최대한 뒤로 미룬다. 감소량이 크면 클수록 뒤로 미룬다.
	-> 정렬을 두 번 수행한다? or 감소할 가용 공간의 크기를 계산하여 미리 준비한다ㅈ

	=============================================================================
	가용 공간이 늘어나는 formatting은 최초 데이터의 크기가 작은 녀석부터 수행하는게 반드시 이득이다.
	그 이유는 포매팅을 위해서 필요한 초기 문턱 비용이 조금 있을 수 있지만, 작업의 결과는 반드시 이득이기 때문.
	따라서 문턱 비용이 작은 녀석부터 차례로 수행하고, 그 차익 만큼 이익을 쌓아 나가면 최소한의 투자로 끝낼 수 있음.

	그렇다면, 순 이익이 아닌, 순 손실이 발생하는 경우는?

	어차피 모든 드라이브를 처리해야 함, 따라서 시작 값은 관련이 없음.
	중요한 것은 포매팅 이후의 값. 불필요하게 available 용량을 많이 남길 필요가 없음.
	따라서 포매팅 이후의 용량이 큰 값부터 처리하여, 마지막에 available 용량을 최소로 남긴다.

	==============================================================================
	문제를 약간 바꿀 수도 있겠음.

	옵션 트레이더인데, 반드시 수행해야 하는 일련의 거래가 존재함.
	각각의 거래는 특정 가격에서 구매하고, 특정 가격에서 팔도록 정해져 있음.
	각 거래는 이득을 볼 수도 있고, 손해를 볼 수도 있음.

	거래의 수행 순서는 마음대로 바꿀 수 있다고 할 때,
	일련의 모든 거래를 수행하기 위해서 필요한 최소의 초기 자금은 얼마인가?

	==============================================================================

	10
	2 2
	5 2
	8 2
	8 3
	9 6
	10 3
	10 4
	10 6
	15 13
	15 14
	ans: 39

	3
	9 3
	6 5
	4 1
	ans: 11
*/
#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;
using Drive = std::pair<ll, ll>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<Drive> drives(N);
	for (auto& d : drives)
		std::cin >> d.first >> d.second;

	// sort
	// 증가 드라이브와 감소 드라이브 분ㅓ
	auto itr = std::partition(drives.begin(), drives.end(), [](Drive const& d) {
		return (d.second - d.first) >= 0;
		});
	// 포맷 후 증가 드라이브 처리
	std::sort(drives.begin(), itr, [](Drive const& d1, Drive const& d2) {
		if (d1.first == d2.first)
		{
			return d1.second > d2.second;
		}
		return d1.first < d2.first;
		});
	// 포맷 후 감소 드라이브 처리
	std::sort(itr, drives.end(), [](Drive const& d1, Drive const& d2) {
		if (d1.second == d2.second)
		{
			return d1.first > d2.first;
		}
		return d1.second > d2.second;
		});

	// sweeping?
	ll extra_total_cap = 0;	// 추가 투입한 드라이브량
	ll avail_total_cap = 0;	// 현재 가용 가능한 드라이브량
	for (auto const [cur_cap, next_cap] : drives)
	{
		if (avail_total_cap < cur_cap)	// 포맷을 이전 용량 부족.
		{
			ll const  needed_cap = cur_cap - avail_total_cap;
			extra_total_cap += needed_cap;
			avail_total_cap += needed_cap;
		}

		ll const added_cap = next_cap - cur_cap;
		avail_total_cap += added_cap;

		if (avail_total_cap < 0)	// 포맷 후 용량이 부족함. 추가 드라이브 투입
		{
			extra_total_cap -= avail_total_cap;
			avail_total_cap = 0;
		}
	}

	std::cout << extra_total_cap;
}
