
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <memory.h>

using uint = unsigned int;

int N;
std::string sentence;
std::vector<std::string> words;
uint cache[51];

int cal_word_cost(std::string sentence_substr, const std::string& word)
{
	int pos, result = 0;
	for (int i = 0; i < word.size(); ++i)
	{
		pos = sentence_substr.find(word[i], 0);
		if (pos == std::string::npos)
		{
			return -1;
		}
		else
		{
			if (word[pos] != sentence_substr[pos])
			{
				result++;
			}
			sentence_substr[pos] = ' ';
		}
	}
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, -1, sizeof(cache));
	
	/*
	std::string str1, str2;
	std::cin >> str1 >> str2;
	std::cout << cal_word_cost(str1, str2);
	*/
	std::string input;
	std::cin >> sentence;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		words.push_back(input);
	}

	// tabulation.
	cache[0] = 0;
	for (int end_pos = 1; end_pos <= sentence.size(); ++end_pos)
	{
		for (const std::string& cur_word : words)
		{
			int start_pos = end_pos - cur_word.size();
			if (start_pos < 0 || cache[start_pos] == -1)
				continue;
			int delta = cal_word_cost(sentence.substr(start_pos, cur_word.size()), cur_word);
			if (delta >= 0)
				cache[end_pos] = std::min(cache[end_pos], cache[start_pos] + delta);
		}
	}
	std::cout << static_cast<int>(cache[sentence.size()]);
}