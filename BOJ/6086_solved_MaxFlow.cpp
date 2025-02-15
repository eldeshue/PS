
// 8086 최대 유량 알고리즘 문제. 에드워드 카프 알고리즘
// 시작 점에서 끝 점까지 가는 경로를 탐색하고, 해당 경로의 최대 유량으로 경로를 채운다.
// 이렇게 경로들을 반복해서 찾아가면서 지났던 경로는 유량을 채우고, 
// 보다 나은 경로가 있을 때 까지 탐색(BFS)를 반복한다.

// 포드 풀커슨 알고리즘의 대미는 경로를 수정하는 데에 있다.
// 이는 허용 용량이 0인 역방향 파이프의 존재로 설명된다. 
// 즉 역방향 파이프를 경유하면서 기존의 잘못된 경로를 지우고, 다른 방향에서 새로이 채워볼 수 있다.
// https://velog.io/@kasterra/%EC%9C%A0%EB%9F%89-%EA%B7%B8%EB%9E%98%ED%94%84-%ED%8F%AC%EB%93%9C-%ED%92%80%EC%BB%A4%EC%8A%A8-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98

// 당면한 문제는 양방향 간선이라 위 가정이 일반적으로 성립하지는 않다.
// 한 번 더 생각할 필요가 있다.

/*
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

constexpr int NODE_NUM = 52;
using uint = unsigned int;
int capacity[NODE_NUM][NODE_NUM];
int flow[NODE_NUM][NODE_NUM];

int map_node(char c)
{
	if ('A' <= c && c <= 'Z')
		return static_cast<int>(c - 'A');
	else if ('a' <= c && c <= 'z')
		return static_cast<int>(c - 'a' + 26);
}

uint BFS(uint start, uint end)
{
	uint prev_node[NODE_NUM];
	memset(prev_node, -1, sizeof(prev_node));
	std::queue<int> Q;
	Q.push(start);

	uint cur_node;
	while (!Q.empty())
	{
		cur_node = Q.front();
		Q.pop();
		if (cur_node == end)
			break;
		for (int next_node = 0; next_node < 52; ++next_node)
		{
			// 증가 경로의 탐색
			// BFS에 대해 미답지이며, 동시에 증가할 가능성이 있는(즉 용량이 남은) 간선을 추가
			// 역방향 간선이어도 갈 수 있음(그저 이미 가본 곳이면 못갈 뿐).
			if (capacity[cur_node][next_node] - flow[cur_node][next_node] > 0 &&
				prev_node[next_node] == -1)
			{
				Q.push(next_node);
				prev_node[next_node] = cur_node;
			}
		}
	}
	// trace back the route
	// 탐색한 증가 경로가 sink에 도달하지 못했다 -> sink를 향하는 증가경로는 없다.
	if (prev_node[end] == -1) return 0;	// no aug route, edmond carp done.
	int aug_flow = 2e9;
	cur_node = end;
	for (cur_node = end; cur_node != start; cur_node = prev_node[cur_node])
	{
	// increasing flow
		aug_flow = std::min(aug_flow, 
			capacity[prev_node[cur_node]][cur_node] - flow[prev_node[cur_node]][cur_node]);
	}
	// 증가한 유량(aug flow)만큼을 경로에 반영함.
	// 순방향 경로였다면, 이는 단순한 확장이었음.
	// 역방향 경로였다면, 이는 일부만큼을 다른 경로로 전용, 즉 달리 흘린 것임.
	for (cur_node = end; cur_node != start; cur_node = prev_node[cur_node])
	{
		flow[prev_node[cur_node]][cur_node] += aug_flow;	// forward flow
		flow[cur_node][prev_node[cur_node]] -= aug_flow;	// reverse flow
	}
	return aug_flow;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	// taking input
	memset(capacity, 0, sizeof(capacity));
	memset(flow, 0, sizeof(flow));
	uint num_edge, total_flow = 0;
	std::cin >> num_edge;
	for (int i = 0; i < num_edge; ++i)
	{
		char from, to;
		uint node1, node2, cap;
		std::cin >> from >> to >> cap;
		node1 = map_node(from);
		node2 = map_node(to);
		capacity[node1][node2] += cap;
		capacity[node2][node1] += cap;	// 간선이 양방향이라 반대도 더해준다.
	}
	// Edmond Karp algorithm
	while (true)
	{
		uint prev_flow = total_flow;
		total_flow += BFS(0, 25);	// source is 'A', sink is 'Z'
		if (prev_flow == total_flow)
			break;
	}
	// result
	std::cout << total_flow;
}
*/