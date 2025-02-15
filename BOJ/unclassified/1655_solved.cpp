
#include <iostream>
#include <vector>
#include <queue>

struct ascend
{
	bool operator()(int a, int b)
	{
		return a > b;
	}
};

struct descend
{
	bool operator()(int a, int b)
	{
		return a < b;
	}
};

std::priority_queue<int, std::vector<int>, descend> lpq;
std::priority_queue<int, std::vector<int>, ascend> rpq;

void balancingLR()
{
	// L -> R, size balancing
	if (lpq.size() > rpq.size() + 1)
	{
		rpq.push(lpq.top());
		lpq.pop();
	}
	// R -> L, exchange top
	if (lpq.size() > 0 && rpq.size() > 0 && lpq.top() > rpq.top())
	{	// exchange
		int ltop = lpq.top(), rtop = rpq.top();
		lpq.pop();
		rpq.pop();
		std::swap(ltop, rtop);
		lpq.push(ltop);
		rpq.push(rtop);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int N, input;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		lpq.push(input);
		balancingLR();
		std::cout << lpq.top() << "\n";
	}
}
