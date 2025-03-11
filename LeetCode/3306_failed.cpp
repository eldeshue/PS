#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

#include <unordered_map>
#include <functional>

class Solution {
private:
	bool IsVowl(char const c)
	{
		return ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u'));
	}

public:
	long long countOfSubstrings(string word, int k)
	{
		std::unordered_map<char, int> vowl_freq;
		int vowl_cnt = 0;
		int consonant_cnt = 0;
		auto IsGood = [&]() { return (vowl_cnt == 5 && consonant_cnt == k); };
		auto IncVowlCnt = [&](char const c) {
			++vowl_freq[c];
			if (vowl_freq[c] == 1)
				++vowl_cnt;
			};
		auto DecVowlCnt = [&](char const c) {
			--vowl_freq[c];
			if (vowl_freq[c] == 0)
				--vowl_cnt;
			};

		bool prev_status = false, cur_status = false;
		auto IncStatus = [&](char const c) {
			if (IsVowl(c))
				++consonant_cnt;
			else
				IncVowlCnt(c);
			prev_status = cur_status;
			cur_status = IsGood();
			};
		auto DecStatus = [&](char const c) {
			if (IsVowl(c))
				--consonant_cnt;
			else
				DecVowlCnt(c);
			prev_status = cur_status;
			cur_status = IsGood();
			};

		long long lcnt = 0, rcnt = 0, result = 0;
		int left = 0;
		for (int right = 0; right < word.size(); ++right)
		{
			IncStatus(word[right]);

			if (prev_status == true && cur_status == false)
			{
				// move left
				lcnt = 1;
				while (cur_status)
				{
					DecVowlCnt(word[left]);
					++left;
					++lcnt;
				}

				// accumulate result
				result += lcnt * rcnt;

				// reset status
				lcnt = 0, rcnt = 0;
			}
			else if (prev_status == false && cur_status == true)
			{
				rcnt = 1;
			}
			else if (prev_status == true && cur_status == true)
			{
				++rcnt;
			}
			else if (prev_status == false && cur_status == false)
			{
				// do nothing ? 
			}
		}
		return result;
	}
};