
#include <iostream>
#include <vector>

using namespace std;

#include <unordered_map>
#include <set>
class Solution
{
private:
	using Table = unordered_map<int, set<int>>;
	static constexpr int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; // from north, clock wise

public:
	// solution method,
	// N : num command, M : num obstacle
	// O(N * M * log M)
	int robotSim(vector<int>& commands, vector<vector<int>>& obstacles)
	{
		Table xyObs, yxObs;
		int curX = 0, curY = 0, d = 0, maxDist = 0;

		// set table
		for (const auto& vec : obstacles)
		{
			int x = vec[0];
			int y = vec[1];
			xyObs[x].insert(y);
			yxObs[y].insert(x);
		}

		// simulate
		for (const int cmd : commands)
		{
			if (cmd < 0) // change direction
			{
				if (cmd == -1)
					d = (d + 1) % 4;
				else
					d = (d - 1 + 4) % 4;
			}
			else // move
			{
				int nextX = curX + dir[d][0] * cmd;
				int nextY = curY + dir[d][1] * cmd;
				// detact obstacle, using upper bound and lower bound
				if (curX == nextX && xyObs.find(curX) != xyObs.end()) // obstacle in x
				{
					const set<int>& curCol = xyObs[curX];
					if (d == 0) // curY < nextY
					{
						auto nearObsY = curCol.upper_bound(curY);
						if (nearObsY != curCol.end())
						{
							nextY = min(nextY, *nearObsY - 1);
						}
					}
					else if (d == 2) // curY > nextY
					{
						auto nearObsY = curCol.lower_bound(curY);
						if (nearObsY != curCol.begin())
						{
							nearObsY--;
							nextY = max(nextY, *nearObsY + 1);
						}
					}
				}
				else if (curY == nextY && yxObs.find(curY) != yxObs.end()) // obstacle in y
				{
					const set<int>& curRow = yxObs[curY];
					if (d == 1) // curX < nextX
					{
						auto nearObsX = curRow.upper_bound(curX);
						if (nearObsX != curRow.end())
						{
							nextX = min(nextX, *nearObsX - 1);
						}
					}
					else if (d == 3) // curX > nextX
					{
						auto nearObsX = curRow.lower_bound(curX);
						if (nearObsX != curRow.begin())
						{
							nearObsX--;
							nextX = max(nextX, *nearObsX + 1);
						}
					}
				}
				// move position
				curX = nextX;
				curY = nextY;
				maxDist = max(maxDist, curX * curX + curY * curY);
			}
			// debug print
			//std::cout << cmd << ' ' << curX << ' ' << curY << ' ' << maxDist << '\n';
		}
		return maxDist;
	}
};

auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
//

int main()
{
	Solution test;
	vector<int> cmd{2, -1, -1, -1, -2, 1, 7, -2, 9, 2, 3, -1, 4, 9, 7, 7, 2, 4, 2, -2, 1, 5, 8, -2, -2, 4, 2, 9, 7, 5, 5, -2, 2, 2, 1, -1, -1, 1, 6, 6, -1, 7, -1, 7, 1, 8, 2, -1, 8, 7, -1, 2, -2, 2, 2, 4, 9, -1, 4, -1, -2, 8, -1, 3, 6, -2, 7, -2, 6, 7, 9, 6, -2, -1, 3, 6, 2, 8, 6, 6, -2, -2, 4, 2, 4, 1, 2, 2, 2, 8, 6, 4, 6, 7, -1, 1, -2, -1, -1, 7};
	vector<vector<int>> obs {
		{75, 61}, {-27, -13}, {-85, 77}, {-40, -30}, 
		{-71, -34}, {41, -39}, {73, -54}, {-19, 16}, 
		{76, 50}, {-12, -9}, {-25, -100}, {45, -86}, 
		{-43, -88}, {50, -23}, {-46, -89}, {-66, 91}, 
		{-57, -46}, {-82, 51}, {78, 98}, {65, -61}, 
		{83, -14}, {24, -17}, {28, 77}, {-63, -3}, 
		{77, -39}, {18, -63}, {10, -91}, {-11, -15}, 
		{-75, -80}, {68, 92}, {21, -70}, {91, -53}, 
		{-68, -64}, {9, -68}, {1, 40}, {-73, 20}, {56, 15}, 
		{-90, -43}, {-100, 99}, {-19, 7}, {14, 76}, {-80, -2}, 
		{24, -34}, {47, 7}, {25, 73}, {-99, -39}, {-55, -9}, 
		{85, 31}, {14, 0}, {-68, 94}, {-25, 25}, {44, -77}, 
		{-94, 59}, {92, -47}, {40, 5}, {-68, -58}, {87, 39}, 
		{-43, 93}, {-83, -77}, {-95, 81}, {82, 37}, {66, 21}, 
		{-5, 73}, {-75, 32}, {30, 70}, {22, -68}, {-27, 31}, 
		{-91, 80}, {82, -58}, {-95, -24}, {15, 22}, {-10, 38}, 
		{85, 96}, {68, 26}, {81, -18}, {23, -47}, {-80, -78}, 
		{30, 18}, {-56, 4}, {1, 33}, {-21, 2}, {-69, 85}, {41, 92}, 
		{-72, 79}, {-48, -34}, {-34, 63}, {48, -78}, {17, 73}, {16, 28}, 
		{-13, -14}, {16, 24}, {11, -27}, {44, 52}, {-78, 67}, {93, 65}, 
		{-32, -33}, {6, -2}, {67, -100}, {95, 77}, {-6, 28}, {10, 81}, 
		{-45, 48}, {80, -34}, {-49, 46}, {-38, 17}, {7, -81}, {-29, 52}, 
		{46, -82}, {5, -71}, {79, -87}, {39, -82}, {-78, -82}, {-85, 19}, 
		{74, -55}, {22, 45}, {-40, -24}, {44, 97}, {41, -21}, {-17, -92}, 
		{17, 49}, {-1, -33}, {39, -36}, {37, -38}, {41, -29}, {72, -88},
		{-100, 57}, {-95, 74}, {-27, -16}, {57, -34}, {74, -85}, {62, 92},
		{44, 0}, {83, 57}, {90, 96}, {-65, 70}, {-58, 99}, {-70, -86},
		{75, -74}, {-63, 11}, {-64, 20}, {-35, -40}, {-86, -71},
		{-77, -62}, {4, -95}, {97, 76}, {36, -62}, {-1, 90}, {99, 91},
		{55, 89}, {80, 77}, {40, 54}, {79, -11}, {44, -36}, {-35, 21},
		{-13, -86}, {-55, 84}, {27, 94}, {74, 91}, {-77, -45}, {-90, 44},
		{-80, -35}, {-38, 80}, {34, -28}, {45, -77}, {1, 28}, {-88, -50},
		{-100, 87}, {19, 93}, {-26, -39}, {-83, -100}, {-6, 43}, {89, 42},
		{-35, -95}, {-67, -96}, {14, 22}, {-25, 8}, {-31, -9}, {-94, 48},
		{82, -3}, {39, 95}, {44, 47}, {-62, -71}, {73, -30}, {92, -11} , 
		{2, 85}, {-91, 97}, {99, -18}, {-57, -17}, {57, 73}, {-41, 9},
		{44, 9}, {17, -96}, {-95, -16}, {40, -3}, {-48, -41}, {95, 18},
		{-34, -94}, {15, -90}, {42, 11}, {-65, -57}};
	std::cout << test.robotSim(cmd, obs);
}