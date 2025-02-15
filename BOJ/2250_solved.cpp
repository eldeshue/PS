
#include <iostream>
#include <memory.h>

int N;
bool isRoot[10001];
int tree[10001][2]; // 0 : left, 1 : right
int width[10001][2]; // 0 : last node pos, 1 : width 

void updateWidth(int level, int pos)
{
	if (width[level][0] == -1)	// first time
	{
		width[level][0] = pos;
		width[level][1] = 1;
	}
	else if (width[level][0] < pos) // update
	{
		width[level][1] = pos - width[level][0] + 1;
	}
}

int DFS_sizeSubTree(int curNode, int curLevel, int startPos)
{
	// left
	int LSize = 0;
	if (tree[curNode][0] != -1)
	{
		LSize = DFS_sizeSubTree(tree[curNode][0], curLevel + 1, startPos);
	}
	// mid
	updateWidth(curLevel, startPos + LSize); // startPos - 1 + LSize +  1
	// right
	int RSize = 0;
	if (tree[curNode][1] != -1)
	{
		// startPos - 1 + LSize + 2
		RSize = DFS_sizeSubTree(tree[curNode][1], curLevel + 1, startPos + LSize + 1);
	}
	return LSize + RSize + 1;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(tree, 0, sizeof(tree));
	memset(width, -1, sizeof(width));
	memset(isRoot, 1, sizeof(isRoot));

	int nodeNum, root, left, right;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> nodeNum >> left >> right;
		tree[nodeNum][0] = left;
		tree[nodeNum][1] = right;
		if(left > 0)
		{
			isRoot[left] = false;
		}
		if(right > 0)
		{
			isRoot[right] = false;
		}
	}
	for (int i = 1; i <= N; ++i)
	{
		if (isRoot[i])
		{
			root = i;
			break;
		}
	}

	// DFS
	DFS_sizeSubTree(root, 1, 1);

	int maxLevel = 1;
	int maxWidth = 0;
	for (int i = 1; i <= N; ++i)
	{
		if (maxWidth < width[i][1])
		{
			maxLevel = i;
			maxWidth = width[i][1];
		}
		//std::cout << i << " " << width[i][1] << "\n";
	}
	std::cout << maxLevel << " " << maxWidth;
}