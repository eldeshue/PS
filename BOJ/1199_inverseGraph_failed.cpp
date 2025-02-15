// Euler circuit
// using Inversed graph
// treat node as an edge, and edge as a node.
// which maeans, we travel the edge, DFS

/*
#include <iostream>
#include <memory.h>
#include <deque>

struct iNode
{
	int prevEdge;
	int curEdge;
	iNode(int p, int c) : prevEdge(p), curEdge(c) {}
};

int iTotalNodeNum, iEdgeNum;
int iNodes[1001][1001]; // inverted nodes, iNodes[prevEdge][NextEdge]
std::deque<iNode> eulerCourse;

void DFS(int curEdge)
{

}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(iNodes, 0, sizeof(iNodes));

	iTotalNodeNum = 0;
	std::cin >> iEdgeNum;
	for (int i = 1; i <= iEdgeNum; ++i)
	{
		for (int j = 1; j <= iEdgeNum; ++j)
		{
			std::cin >> iNodes[i][j];
			iNodes[i][0] += iNodes[i][j];
		}
		iTotalNodeNum += iNodes[i][0];
	}
	iTotalNodeNum /= 2;
	// check availability
	if (iTotalNodeNum % 2 == 1)
	{
		std::cout << -1;
		return 0;
	}
	else // travel start, no matter where to start
	{
		eulerCourse.push_back(iNode(0, 1));
		DFS(1);
	}

	while (!eulerCourse.empty())
	{
		// print
		std::cout << eulerCourse.front().curEdge << " ";
		// pop
		eulerCourse.pop_front();
	}
}
*/
