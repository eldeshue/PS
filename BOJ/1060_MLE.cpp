
#include <iostream>
#include <set>
#include <vector>
#include <queue>	// priority queue
#define INF 2e9
int length, N, minS, maxS;
std::set<int> S;

typedef struct segment
{
	int start;	// included
	int end;	// included
	segment(int s, int e) : start(s), end(e) {};
} segment;
struct cmpSeg 
{
	bool operator() (segment s1, segment s2)
	{
		if (s1.end - s1.start != s2.end - s2.start)
		{
			return (s1.end - s1.start) < (s2.end - s1.start);
		}
		else
		{
			return s1.start < s2.start;
		}
	}
};
struct cmpResult
{
	bool operator() (std::pair<int, int>& pair1, std::pair<int, int>& pair2)	
	{
		if (pair1.second == pair2.second || (pair1.second == INF && pair2.second == INF))
		{
			return pair1.first > pair2.first;
		}
		else
		{
			return pair1.second > pair2.second;
		}
	}
};

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>, cmpResult> PQ;
std::priority_queue<segment, std::vector<segment>, cmpSeg> segPQ;

int calNumArea(int start, int end, int tgt) // both end included
{
	return (tgt - start + 1) * (end - tgt + 1);
}

void calSegment(int& count, const segment& tgtSeg)
{
	for (int i = 0; i <= (tgtSeg.end - tgtSeg.start) / 2 ; ++i)
	{
		int left = tgtSeg.start + i;
		int right = tgtSeg.end - i;
		PQ.push(std::make_pair(left, calNumArea(tgtSeg.start, tgtSeg.end, left)));
		PQ.push(std::make_pair(right, calNumArea(tgtSeg.start, tgtSeg.end, right)));
		count += 2;

		if (left + 1 == right) // even
		{
			break;
		}
		else if (left + 2 == right) // odd
		{
			PQ.push(std::make_pair(left + 1, calNumArea(tgtSeg.start, tgtSeg.end, left + 1)));
			count++;
			break;		
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// initialize set S
	int input;
	std::cin >> length;
	for (int i = 0; i < length; ++i)
	{
		std::cin >> input;
		S.insert(input);
	}
	minS = *(S.begin());
	maxS = *(S.rbegin());
	// put segments
	int e, s = 0;
	for (const auto& elem : S)
	{
		e = elem;
		if (e > s + 1)
		{
			segPQ.push(segment(s + 1, e - 1));
		}
		s = e;
	}

	// calculate and put result in the PQ
	std::cin >> N;
	int count = 0;	
	// S
	for (const auto& pos : S)
	{
		PQ.push(std::make_pair(pos, 0));
		count++;
	}
	// segments
	while (!segPQ.empty())
	{
		calSegment(count, segPQ.top());
		segPQ.pop();
	}
	int pos = maxS + 1;
	while (count <= N)
	{
		PQ.push(std::make_pair(pos, INF));
		count++;
	}

	// print in order
	for (int i = 0; i < N; ++i)
	{
		std::cout << PQ.top().first << " ";
		PQ.pop();
	}
}