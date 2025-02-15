
#include <iostream>
#include <memory.h>
#include <vector>

typedef std::pair<long long, long long> ratio;
typedef std::pair<ratio, long long> edge;

long long N;
bool visited[11];
ratio val[11];
std::vector<edge> graph[11];

long long GCD(long long num1, long long num2)
{
	long long CD = 1;
	for (long long i = 2; i < 10;)
	{
		long long rest1 = num1 % i;
		long long rest2 = num2 % i;
		if (rest1 == 0 && rest2 == 0)
		{
			num1 /= i;
			num2 /= i;
			CD *= i;
		}
		else
		{
			++i;
		}
	}

	return CD;
}

long long LCM(long long num1, long long num2)
{
	long long lcm = GCD(num1, num2);
	lcm = num1 * num2 / lcm;
	return lcm;
}

long long DFS(long long curNode)
{
	long long dividee = val[curNode].first;
	long long divisor = val[curNode].second;
	long long lcm = divisor;

	for (const auto& nextEdge : graph[curNode])
	{
		long long nextNode = nextEdge.second;
		long long ndividee = nextEdge.first.first;
		long long ndivisor = nextEdge.first.second;
		if (!visited[nextNode])
		{
			visited[nextNode] = true;
			long long gcd1 = GCD(dividee, ndividee);
			long long gcd2 = GCD(divisor, ndivisor);
			val[nextNode].first = dividee * ndivisor / gcd1 / gcd2;
			val[nextNode].second = divisor * ndividee / gcd1 / gcd2;
			lcm = LCM(lcm, DFS(nextNode));
		}
	}

	return lcm;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(visited, 0, sizeof(visited));

	long long n1, n2, r1, r2;
	std::cin >> N;
	for (long long i = 0; i < N - 1; ++i)
	{
		std::cin >> n1 >> n2 >> r1 >> r2;
		long long gcd = GCD(r1, r2);
		r1 /= gcd;
		r2 /= gcd;
		graph[n1].push_back(edge(ratio(r1, r2), n2));
		graph[n2].push_back(edge(ratio(r2, r1), n1));
	}

	// DFS, 무조건 루트는 0
	visited[0] = true;
	val[0].first = 1;
	val[0].second = 1;
	long long lcm = DFS(0);

	// 
	for (long long i = 0; i < N; ++i)
	{
		std::cout << val[i].first * lcm / val[i].second << " ";
	}
}