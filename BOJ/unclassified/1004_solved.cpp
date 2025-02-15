// 어린왕자
// 기하학 문제, 점이 원에 포함되는가?
#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>

typedef std::pair<int, int> point;
typedef std::pair<point, int> circle;
std::vector<circle> planets;

bool isIncluded(const point p, const circle& c)
{
	float dist = std::sqrt(std::pow(p.first - c.first.first, 2) 
		+ std::pow(p.second - c.first.second, 2));
	return dist < c.second;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int result, T, N, sx, sy, ex, ey, x, y, r;
	std::cin >> T;
	for (int test = 0; test < T; ++test)
	{
		planets.clear();
		result = 0;

		std::cin >> sx >> sy >> ex >> ey 
			>> N;
		point startP(sx, sy);
		point endP(ex, ey);
		for (int i = 0; i < N; ++i)
		{
			std::cin >> x >> y >> r;
			planets.push_back(circle(point(x, y), r));
		}

		for (const auto& planet : planets)
		{
			bool isSInclude = isIncluded(startP, planet);
			bool isEInclude = isIncluded(endP, planet);

			if (isSInclude)
			{
				result++;
			}
			if (isEInclude)
			{
				result++;
			}
			if (isSInclude && isEInclude)
			{
				result -= 2;
			}
		}

		std::cout << result << "\n";
	}
}