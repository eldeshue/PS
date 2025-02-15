
#include <iostream>
#include <deque>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::vector<int> input;
	std::deque<int> dq;

	int N, curNum = 1;
	std::cin >> N;
	input.resize(N);
	for (int i = 0; i < N; ++i)
		std::cin >> input[i];
	for (int idx = N - 1; idx >= 0; --idx)
	{
		int temp;
		const int &curOps = input[idx];
		switch (curOps)
		{
		case 1:
			dq.push_front(curNum);
			break;
		case 2:
			temp = dq.front();
			dq.front() = curNum;
			dq.push_front(temp);
			break;
		case 3:
			dq.push_back(curNum);
			break;
		}
		curNum++;
	}
	while (!dq.empty())
	{
		std::cout << dq.front() << ' ';
		dq.pop_front();
	}
}
