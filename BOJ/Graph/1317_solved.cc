
/*
	위상정렬

	위상정렬 중 경험해본 최고난이도 문제였음.

	문자열의 끝단이 같은 경우 에지로 연결함.

	앞 뒤 끝단이 같은 문자열은 별도로 예외처리해줘야 함.
	그렇지 않으면 두 노드가 서로를 물어서 사이클을 만들어버림. -> 정상 그래프인데 비정상으로 판단해버림.

	문제의 결론은 3가지가 존재.
	1. 생성 불가능 -> 모든 노드를 정렬할 수 없거나, 각 노드 및 최종 결과물이 그룹이 아님.
	2. 중의적인 결과 -> 정상적인 그룹 단어를 이루지만, 그 배치에 순서가 없을 수 있음 -> 큐에 두 개 이상이 들어가는 경우
	3. 정상적인 그룹 단어.
*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>

bool isGroupWord(const std::string &str)
{
	bool visited[26] = {
		false,
	}; // lower case alphabat only
	char lastAlpha = str[0];
	visited[str[0] - 'a'] = true;

	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] != lastAlpha && visited[str[i] - 'a'] == true)
		{
			return false;
		}
		else if (str[i] != lastAlpha && visited[str[i] - 'a'] == false)
		{
			visited[str[i] - 'a'] = true;
			lastAlpha = str[i];
		}
	}
	return true;
}

class Graph
{
private:
	const int N;
	using AdjMat = std::vector<std::vector<bool>>;
	int visited;
	AdjMat data;
	std::vector<int> inDegree;
	std::vector<int> sortedIdx;
	bool isAmbiguous;

	Graph();

public:
	Graph(const int n) : N(n), visited(N), sortedIdx(N), data(N, std::vector<bool>(N, false)), inDegree(N, 0), isAmbiguous(false) {}
	void makeEdge(int from, int to)
	{
		data[from][to] = true;
		inDegree[to]++;
	}
	void topologicalSort()
	{
		std::queue<int> q;
		int pos = 0;

		for (int startNode = 0; startNode < N; ++startNode)
		{
			if (inDegree[startNode] != 0)
				continue;
			if (pos != 0)
				isAmbiguous = true;
			visited--;
			inDegree[startNode] = -1;
			q.push(startNode);
			while (!q.empty())
			{
				if (q.size() >= 2)
					isAmbiguous = true;
				int curNode = q.front();
				sortedIdx[pos++] = curNode;
				q.pop();
				for (int nextNode = 0; nextNode < N; ++nextNode)
				{
					if (data[curNode][nextNode] == true)
					{
						if (--inDegree[nextNode] == 0)
						{
							visited--;
							inDegree[nextNode] = -1;
							q.push(nextNode);
						}
					}
				}
			}
		}
	}
	bool isAllVisited() const { return visited == 0; };
	bool isResultAmbiguous() const { return isAmbiguous; };
	bool isEdge(int from, int to) const { return data[from][to]; };
	const std::vector<int> &result() const { return sortedIdx; };
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// get input
	int N;
	std::cin >> N;
	std::vector<std::string> nodes(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> nodes[i];
		// is groupWord?
		if (!isGroupWord(nodes[i]))
		{
			std::cout << "gg";
			return 0;
		}
	}

	// build graph
	Graph g(N);
	for (int from = 0; from < N; ++from)
	{
		for (int to = 0; to < N; ++to)
		{
			if (from == to || nodes[from].back() != nodes[to].front() || (nodes[to].front() == nodes[to].back() && g.isEdge(to, from)))
				continue;
			g.makeEdge(from, to);
		}
	}

	// topological sort
	g.topologicalSort();

	// set result
	std::string result;
	for (const int &i : g.result())
	{
		result.append(nodes[i]);
	}
	if (!g.isAllVisited() || !isGroupWord(result)) // cannot be sorted
	{
		std::cout << "gg";
	}
	else if (g.isResultAmbiguous()) // ambiguous
	{
		std::cout << "-_-";
	}
	else
	{
		std::cout << result;
	}
}
