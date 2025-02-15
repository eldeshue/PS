
/*

#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>
#include <stack>
#include <tuple>

using Point = std::pair<int, int>;
using Regist = std::tuple<int, bool, int>;	// parent pos, is car 2 moved, min total dist

static int getDist(const Point &p1, const Point &p2)
{
	return std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, W;
	std::cin >> N >> W;
	W += 2;
	std::vector<Point> points(W);
	std::vector<std::vector<Regist>> cache(W, std::vector<Regist>(W, {-1, 0, 2e9}));
	points[0] = { 1, 1 };	// car1 initial pos
	points[1] = { N, N };	// car2 initial pos
	for (int i = 2; i < W; ++i)
		std::cin >> points[i].first >> points[i].second;
	// set initial state, index 0
	// car 1 move to the next point, idx 1 means keeping car2
	cache[2][1] = {-1, 0, getDist(points[0], points[2])};
	// car 2 move to the next point
	cache[2][0] = {-1, 1, getDist(points[1], points[2])};
	// tabulation
	for (int curPos = 3; curPos < W; ++curPos)
	{
		const int lastPos = curPos - 1;
		const auto& curPoint = points[curPos];
		const auto& lastPoint = points[lastPos];
		for (int prevPos = 0; prevPos < lastPos; ++prevPos)
		{
			const auto& prevPoint = points[prevPos];
			const auto& [___, prev2Moved, prevDist]
				= cache[lastPos][prevPos];
			{
				// move last one
				auto& [parentNum, is2Moved, curDist]
					= cache[curPos][prevPos];
				parentNum = prevPos;
				is2Moved = prev2Moved;
				curDist = prevDist + getDist(lastPoint, curPoint);
			}
			{
				// move another previous one, update cache[curPos][lastPos]
				auto& [parentNum, is2Moved, curDist]
					= cache[curPos][lastPos];
				const int tempDist = prevDist + getDist(prevPoint, curPoint);
				if (tempDist < curDist)
				{
					parentNum = prevPos;
					is2Moved = !prev2Moved;
					curDist = tempDist;
				}
			}
		}
	}
	// find min value
//	std::cout << std::accumulate(cache[W - 1].begin(), cache[W - 1].end(), 2e9, 
//		[](const int acc, const Regist &r) -> int {
//			return std::min(acc, std::get<2>(r));
//		});
	int curPos = 0, minVal = 2e9;
	for (int i = 0; i < W; ++i)
	{
		const auto& [parentNum, is2Moved, curDist]
				= cache[W - 1][i];
		if (curDist < minVal)
		{
			curPos = i;
			minVal = curDist;
		}
	}
	// find path, use stack???
	std::stack<int> st;
	for (int row = W - 1; row >= 2; --row)
	{
		const auto& [parentNum, is2Moved, curDist]
				= cache[row][curPos];
		st.push(1 + is2Moved);
		curPos = parentNum;
	}
	// print
	std::cout << minVal << '\n';
	while (!st.empty())
	{
		std::cout << st.top() << '\n';
		st.pop();
	}
}

*/
