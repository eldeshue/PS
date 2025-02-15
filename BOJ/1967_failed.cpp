
/*
#include <iostream>
#include <stack>
#include <vector>

int numNode, in_parent, in_child, in_edge, MaxLength = 0;
int RtoC = 0, RtoP = 0, RtoN = 0; // P : previous leaf, R : Root, N : New leaf
std::vector<std::pair<int,int>> tree[10001]; // first : parent, second : edge length
bool visited[10001];
std::stack<std::pair<int,int>> curNode;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	// build tree
	std::cin >> numNode;
	for (int i = 1; i < numNode; ++i)
	{
		std::cin >> in_parent >> in_child >> in_edge; // orders are give
		tree[in_parent].push_back(std::make_pair(in_child, in_edge));
	}

	// DFS, search the Maximum length.
	curNode.push(std::make_pair(1,0));
	while (!curNode.empty())
	{
		// arrive
		bool isEnd = true;
		visited[curNode.top().first] = true;
		// move
		// go down
		for (const auto& child : tree[curNode.top().first])
		{
			if (!visited[child.first])
			{
				// go down
				isEnd = false;
				RtoN += child.second;
				curNode.push(child);
				break;
			}
		}

		if (isEnd) 
		{
			if (tree[curNode.top().first].size() == 0) // if node is leaf
			{
				int CtoP = RtoP - RtoC;
				int CtoN = RtoN - RtoC;
				int NtoP = CtoN + CtoP;
				// find max
				if(RtoN > RtoP) // RtoN > RtoP, higher leaf
				{
					RtoP = RtoN;
					RtoC = RtoN;
				}
				else
				{
					RtoC += CtoN;
				}
				// compare Max & RtoP
				MaxLength = ( MaxLength > RtoP )? MaxLength: RtoP;
				// compare Max & NtoP
				MaxLength = ( MaxLength > NtoP )? MaxLength: NtoP;
			}
			// go up
			RtoC -= curNode.top().second;
			RtoN -= curNode.top().second;
			curNode.pop();
		}
	}

	// print result
	std::cout << MaxLength;
}
*/
