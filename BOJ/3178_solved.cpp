
/*
	trie ����. ������ trie�� Ǯ��� �ȵǴ� ����.

	trie�� ���Ǹ�, �� �ŵ��� Ȯ���ϰ� ���ؿ�
	trie��� ������ �ٽ����� ����(�ؽ��� �޸� ����)���� �����ؾ߸� Ǯ �� �ִ� ����.

	��ü���� ȯ���� ������� �ʰ�, 1���������� �����Ϸ��� �� �ڽſ��� ���� ���ΰ� ��.
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct cmp_str_reverse
{
private:
	int K;
public:
	cmp_str_reverse(int k) : K(k) {};
	bool operator()(const std::string& str1, const std::string& str2)
	{
		for (int i = 2 * K - 1; i >= 0; --i)
		{
			if (str1[i] != str2[i])
			{
				return str1[i] < str2[i];
			}
		}
		return true;
	}
};

void forwardSearch(const std::vector<std::string>& words,
	const int &K, int minRow, int maxRow, int curCol, int &result)
{
	char prevVal = words[minRow][curCol];
	int prevRow = minRow;

	if (curCol == K)
		return;
	for (int r = minRow; r <= maxRow; ++r)
	{
		const char& curVal = words[r][curCol];
		if (curVal != prevVal)
		{
			result++;
			forwardSearch(words, K, prevRow, r - 1, curCol + 1, result);
			prevVal = curVal;
			prevRow = r;
		}
	}
	result++;
	forwardSearch(words, K, prevRow, maxRow, curCol + 1, result);
}

void backwardSearch(const std::vector<std::string>& words,
	const int &K, int minRow, int maxRow, int curCol, int &result)
{
	char prevVal = words[minRow][curCol];
	int prevRow = minRow;

	if (curCol == K - 1)
		return;
	for (int r = minRow; r <= maxRow; ++r)
	{
		const char& curVal = words[r][curCol];
		if (curVal != prevVal)
		{
			result++;
			backwardSearch(words, K, prevRow, r - 1, curCol - 1, result);
			prevVal = curVal;
			prevRow = r;
		}
	}
	result++;
	backwardSearch(words, K, prevRow, maxRow, curCol - 1, result);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K, result = 0;
	std::cin >> N >> K;
	std::vector<std::string> words(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> words[i];
	}
	// forward search
	std::sort(words.begin(), words.end());
	forwardSearch(words, K, 0, N - 1, 0, result);
	// backward search
	std::sort(words.begin(), words.end(), cmp_str_reverse(K));
	backwardSearch(words, K, 0, N - 1, 2 * K - 1, result);
	std::cout << result;
}