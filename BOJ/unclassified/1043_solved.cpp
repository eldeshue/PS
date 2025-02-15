// solved.
// 그래프 탐색 문제, 많은 생각을 가져다 준 좋은 문제임.
// 문제 분석 과정에서 조건 파악도 훌륭했다고 생각함. 하지만 시간이 많이 걸렸음.
// 두 종류의 노드가 혼합되어 서로 다른 처리를 해줘야 했던 부분이 문제의 핵심 아이디어인듯.
// 별도로 함수를 나눠서 처리한게 주효했다고 생각함.
#include <iostream>
#include <vector>
#include <queue>

std::vector<int> partyGraph[50];	// party -> people
std::vector<int> peopleGraph[51];	// people -> party
std::queue<int> nextParty;
std::queue<int> nextPeople;
bool visitedParty[50] = { false };
bool visitedPeople[51] = { false };

void peopleToParty();

void partyToPeople()
{
	if (nextParty.empty())
	{
		return;
	}
	// arrive
	int cur_party = nextParty.front();
	nextParty.pop();
	visitedParty[cur_party] = true;

	// add people in the queue
	// if, not visited
	for(const auto& elem : partyGraph[cur_party])
	{
		if (!visitedPeople[elem])
		{
			nextPeople.push(elem);
		}
	}

	// exit
	if ( nextPeople.empty() && nextParty.empty() ) // 양쪽 큐 모두 비워져야 순회 종료.
	{
		return;
	}
	else if (nextPeople.empty() && !nextParty.empty()) // 마저 순회해야 함.
	{
		partyToPeople();
	}
	else
	{	// move to next party
		peopleToParty();
	}
}

void peopleToParty()
{
	if (nextPeople.empty())
	{
		return;
	}
	// arrive
	int cur_people = nextPeople.front();
	nextPeople.pop();
	visitedPeople[cur_people] = true;

	// add parties in the queue
	// if, not visited
	for(const auto& elem : peopleGraph[cur_people])
	{
		if (!visitedParty[elem])
		{
			nextParty.push(elem);
		}
	}

	// exit
	if ( nextParty.empty() && nextPeople.empty() )
	{
		return;
	}
	else if (nextParty.empty() && !nextPeople.empty()) // 마저 순회해야 함.
	{
		peopleToParty();
	}
	else
	{	// move to next people
		partyToPeople();
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int numPeople, numTruePeople, numParty, numPartyPeople, input;
	std::cin >> numPeople >> numParty >> numTruePeople;
	
	// set people who knows truth
	for (int i = 0; i < numTruePeople; ++i)
	{
		std::cin >> input;
		nextPeople.push(input);
	}

	// set party
	for (int p = 0; p < numParty; ++p)
	{
		std::cin >> numPartyPeople;
		for (int i = 0; i < numPartyPeople; ++i)
		{
			std::cin >> input;
			partyGraph[p].push_back(input);
			peopleGraph[input].push_back(p);
		}
	}

	// traversal BFS, 2 graph.
	// people -> party, party -> people
	peopleToParty();
	
	int result = 0;
	for (int i = 0; i < numParty; ++i)
	{
		if (!visitedParty[i])
		{
			result++;
		}
	}
	std::cout << result;
}