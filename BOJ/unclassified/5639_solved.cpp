
/*
	���� Ʈ���� ������ �����ϴ� ����

	���� Ǯ��ô� ������ �ٸ� ����.
	���� ��ȸ ������� �־�����, �̸� ���� ��ȸ ����� �ٲٴ� ������.

	������ �ٽ��� �־��� �迭�� ������ ��� ��� � Ʈ���� �Ϻ����� �ƴ� ��.
	�� ����Ʈ���� �ĺ��� �ٽ��� ������.

	ó������ ������ Ȱ���ؼ� ������ Ǯ���� �Ͽ�����, �̳� ������.

	�ٽ� ó������ ���ư��� Ʈ���� Ư���� ��ͼ��� �����Ͽ� ������.
	�˻� ���� Ʈ���� �ٽ��� ���Ұ��� ��Һ񱳸� Ȱ���Ͽ� 
	�ش� ����� �¿츦 �ĺ��ϵ��� ó����.

	���� ��������� ȣ���Ͽ� ���Ҹ� ������.
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