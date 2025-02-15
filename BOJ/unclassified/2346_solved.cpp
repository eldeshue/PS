
#include <iostream>
#include <deque>

int N;
std::deque<std::pair<int,int>> roundQ;

void movCCW()
{
	roundQ.push_back(roundQ.front());
	roundQ.pop_front();
}

void movCW()
{
	roundQ.push_front(roundQ.back());
	roundQ.pop_back();
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int temp;
	std::cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> temp;
		roundQ.push_back(std::make_pair(i, temp));
	}

	while (true)
	{
		int curBalloon = roundQ.front().first;
		int movCnt = roundQ.front().second;
		roundQ.pop_front();
		std::cout << curBalloon << " ";
		if (roundQ.empty())
		{
			break;
		}
		else if (movCnt > 0) 
		{
			for (int i = 1; i < movCnt; ++i)
			{
				movCCW();
			}
		}
		else
		{
			for (int i = 0; i < -movCnt; ++i)
			{
				movCW();
			}
		}
	}
}