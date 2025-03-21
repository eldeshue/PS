
#include <iostream>
#include <memory.h>

using node = std::pair<long long, long long>;	// first : node id, second : delta weight

int parent[100001];	// for root, save rank in negative / else, root in positive
long long weight[100001];	// subjective, delta weight

node find(int tNode)
{
	if (parent[tNode] < 0)	// root found
	{
		// value update
		weight[tNode] = 0;
		return std::make_pair(tNode, 0);
	}
	else
	{
		// path compression
		node rootOfTarget = find(parent[tNode]);	// return result has to be root
		parent[tNode] = rootOfTarget.first;
		weight[tNode] += rootOfTarget.second;		// value compression
		return std::make_pair(rootOfTarget.first, weight[tNode]);
	}
}

// keep the root 0
// dw is always positive
// if the weight is negative,
// if the weight is positive,
void Union(int light, int heavy, int dw)
{
	node rootL = find(light);
	node rootH = find(heavy);	// root, with path comression

	if (rootL.first == rootH.first)	// do nothing, not gonna occur
		return;

	if (parent[rootL.first] < parent[rootH.first])	// union by rank
	{
		// union, heavy tree goes to child
		parent[rootL.first] += parent[rootH.first];
		parent[rootH.first] = rootL.first;
		//
		weight[rootH.first] = rootL.second + dw - weight[heavy];
	}
	else	// union, light tree goes to parent
	{
		parent[rootH.first] += parent[rootL.first];
		parent[rootL.first] = rootH.first;
		weight[rootL.first] = rootH.second - dw - weight[light];
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	char opType;
	int numSample, numTest, a, b, w;
	while (true)
	{
		std::cin >> numSample >> numTest;
		if (numSample == 0 && numTest == 0)
			break;

		memset(parent, -1, sizeof(parent));
		memset(weight, -1, sizeof(weight));
		while (numTest--)
		{
			std::cin >> opType >> a >> b;
			if (opType == '!')
			{
				std::cin >> w;
				// union
				// light a, heavy b
				Union(a, b, w);
			}
			else if (opType == '?')
			{
				// find, path compression
				node aNode = find(a);
				node bNode = find(b);
				if ((aNode.first != bNode.first))	// different tree, not union yet
				{
					std::cout << "UNKNOWN\n";
				}
				else
				{
					std::cout << bNode.second - aNode.second << '\n';
				}
			}
		}
	}
}
