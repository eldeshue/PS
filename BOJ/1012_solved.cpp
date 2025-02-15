
#include <iostream>
#include <queue>

class field
{
private:
	bool isCrop[50][50];
	int numCrop;
	int numGraph;
public:
	field() : numCrop(0), numGraph(0) {}; // 초기화 안해도 0일까??
	~field() {};

	void clear()
	{
		for (int i = 0; i < 50; ++i)
		{
			for (int j = 0; j < 50; ++j)
			{
				isCrop[i][j] = false;
			}
		}
		numGraph = 0;
	}
	void setCrop(int x, int y);
	bool findCrop(int x, int y); 
	void BFS(int startX, int startY);
	int result() { return numGraph; }
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int numTest,x, y, c;
	std::cin >> numTest;
	field f;
	for (int i = 0; i < numTest; ++i)
	{
		f.clear();
		std::cin >> x >> y >> c;
		int xLength = x, yLength = y;
		for (int i = 0; i < c; ++i)
		{
			std::cin >> x >> y;
			f.setCrop(x, y);
		}

		for (int i = 0; i < xLength; ++i)
		{
			for (int j = 0; j < yLength; ++j)
			{
				if (f.findCrop(i, j))
				{
					f.BFS(i, j);
				}
			}
		}
		std::cout << f.result() << "\n";
	}
}

void field::setCrop(int x, int y)
{
	isCrop[x][y] = true;
}

bool field::findCrop(int x, int y)
{
	if (x < 0 || x > 49 || y < 0 || y > 49)
	{
		return false;
	}
	return isCrop[x][y];
}

void field::BFS(int startX, int startY)
{
	// graph found
	numGraph++;
	// clear the crops from the field using BFS.
	std::queue<std::pair<int, int>> nextNode;
	nextNode.push(std::make_pair(startX, startY));
	isCrop[startX][startY] = false;	// 큐에 대한 중복 적재를 막기 위해서 진입 전 방문표시하기.
	while (!nextNode.empty())
	{
		// clear
		startX = nextNode.front().first;
		startY = nextNode.front().second;
		nextNode.pop();

		// find adjacent node
		// up , down, left, right
		int up = startY - 1, down = startY + 1, 
			left = startX - 1, right = startX + 1;
		// range check
		if (findCrop(left, startY))
		{	// left
			isCrop[left][startY] = false;
			nextNode.push(std::make_pair(left, startY));
		}
		if (findCrop(right, startY))
		{	// right
			isCrop[right][startY] = false;
			nextNode.push(std::make_pair(right, startY));
		}
		if (findCrop(startX, up))
		{	// up
			isCrop[startX][up] = false;
			nextNode.push(std::make_pair(startX, up));
		}
		if (findCrop(startX, down))
		{	// down
			isCrop[startX][down] = false;
			nextNode.push(std::make_pair(startX, down));
		}
	}
}
