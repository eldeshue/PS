
/*
	이진 트리의 성질을 응용하는 문제

	과거 풀어봤던 문제의 다른 버젼.
	전위 순회 결과물이 주어지고, 이를 후위 순회 결과로 바꾸는 문제임.

	문제의 핵심은 주어진 배열의 내용이 어디서 어디가 어떤 트리의 일부인지 아는 것.
	즉 서브트리의 식별에 핵심이 존재함.

	처음에는 스택을 활용해서 문제를 풀려고 하였으나, 이내 실패함.

	다시 처음으로 돌아가서 트리의 특성인 재귀성을 응용하여 접근함.
	검색 이진 트리의 핵심인 원소간의 대소비교를 활용하여 
	해당 노드의 좌우를 식별하도록 처리함.

	이후 재귀적으로 호출하여 원소를 분해함.
*/
#include <iostream>
#include <vector>

// prevRoot is minimum, curRoot is maximum
int fromPreToPost(const std::vector<int>& input,  std::vector<int>& result,
	const int minVal, int maxVal, int curPos)
{
	if (curPos >= input.size())	// base case
	{
		return curPos;
	}
	const int root = input[curPos];	// first node of subtree is root
	// left
	int nextPos = curPos + 1;
	if (nextPos < input.size() && input[nextPos] < root)
		nextPos = fromPreToPost(input, result, minVal, root, nextPos);
	// right
	if (nextPos < input.size() && input[nextPos] < maxVal)
		nextPos = fromPreToPost(input, result, root, maxVal, nextPos);
	// conquer
	result.push_back(root);
	return nextPos;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::vector<int> input, result;
	int nums;
	while (std::cin >> nums)
	{
		input.push_back(nums);
	}
	// recursive
	fromPreToPost(input, result, -1, 1000000, 0);
	// print
	for (const int& n : result)
	{
		std::cout << n << '\n';
	}
}