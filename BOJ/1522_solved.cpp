
/*

	boj 1522, 문자열 교환

	a,b의 두 문자로 이루어진 문자열을 연속된 a로 만들기 위한 swap의 최소횟수
	슬라이딩 윈도우 기법으로 풀이가 가능함.

	슬라이딩 윈도우는 투 포인터의 일종, 단 두 포인터의 거리가 일정하다는 차이가 있음.

	해당 문제의 최소횟수를 구하려면 일단 가장 많이 뭉친 덩어리(문자 상관 없음)을 찾고,
	해당 덩어리에 몰아줘야 함. 단.어느 문자로 모아줘야 하는지는 문자열 상태에 따라 다름.
	
	따라서 문자 종류별로 가장 큰 덩어리를 찾아서, 해당 덩어리와 그 덩어리 최대 크기의 차를 구하면 됨.

	추가적으로 문자열이 round buffer의 형태라는 조건이 있으므로, 이를 위해서 슬라이딩 윈도우를 
	조금 변형해줘야 함.

*/

#include <iostream>
#include <string>

int sliding_window(const std::string& str, char c, int window_size)
{
	int end, max_cnt = 0, cnt = 0;
	for (int i = 0; i < window_size; ++i)
	{
		if (str[i] == c)
			cnt++;
	}
	max_cnt = cnt;
	for (int start = 1; start < str.size(); ++start)
	{
		end = (start + window_size - 1) % str.size();	// round-buffer.
		if (str[start - 1] == c)
			cnt--;
		if (str[end] == c)
			cnt++;
		max_cnt = std::max(max_cnt, cnt);
	}
	return window_size - max_cnt;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int max_a = 0, max_b = 0;
	std::string str;
	std::cin >> str;
	for (char c : str)
	{
		if (c == 'a')
			max_a++;
		else
			max_b++;
	}
	// sliding window, X2
	// O(2N)
	std::cout << std::min(sliding_window(str, 'a', max_a), sliding_window(str, 'b', max_b));
}