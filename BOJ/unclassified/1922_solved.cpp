// Minimum Spanning Tree
// Prim's algorithm
#include <iostream>
#include <memory.h>
#include <queue>
#include <set>
#include <vector>

typedef struct edge
{
	int node1;
	int node2;
	int weight;
	edge(int n1, int n2, int w) : node1(n1), node2(n2), weight(w) {};
}edge ;
std::vector<edge> edgeData;

struct comp
{
	bool operator() (int index1, int index2)
	{
		return edgeData[index1].weight > edgeData[index2].weight;
	}
};

std::priority_queue <int, std::vector<int>, comp> nearSTreeEdgeIndex;
std::queue<int> adjEdges[1001];
std::set<int> STree, nSTree;
int numNode, numEdge, result = 0;

int opponent(int edgeIndex) 
{ 
	edge& curNode = edgeData[edgeIndex];
	return ((STree.find(curNode.node1) != STree.end()) ? curNode.node2 : curNode.node1); 
};
int findNextNode()
{
	while (STree.find(edgeData[nearSTreeEdgeIndex.top()].node1) != STree.end() && STree.find(edgeData[nearSTreeEdgeIndex.top()].node2) != STree.end())
	{
		nearSTreeEdgeIndex.pop();
	}
	result += edgeData[nearSTreeEdgeIndex.top()].weight;
	return opponent(nearSTreeEdgeIndex.top());
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	// filling graph
	int node1, node2, edgeCost, pos = 0;
	std::cin >> numNode >> numEdge;
	for(int i = 0; i < numEdge; ++i)
	{
		std::cin >> node1 >> node2 >> edgeCost;
		edgeData.push_back(edge(node1, node2, edgeCost));
		adjEdges[node1].push(pos);
		adjEdges[node2].push(pos);
		pos++;
	}
	for (int i = 2; i <= numNode; ++i)
	{
		nSTree.insert(i);
	}
	STree.insert(1);
	
	while (!adjEdges[1].empty())
	{
		nearSTreeEdgeIndex.push(adjEdges[1].front());
		adjEdges[1].pop();
	}
	while (!nSTree.empty())
	{
		int nextNode = findNextNode();

		while (!adjEdges[nextNode].empty())
		{
			nearSTreeEdgeIndex.push(adjEdges[nextNode].front());
			adjEdges[nextNode].pop();
		}
		// spanning tree	
		STree.insert(nextNode);
		nSTree.erase(nextNode);
	}

	std::cout << result;
}
