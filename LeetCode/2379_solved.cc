#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

class Solution {
private:
public:
	int minimumRecolors(string blocks, int k)
	{
		// sliding window, window size k
		int result = blocks.size(), cur_white_cnt = 0;
		for (int i = 0; i < blocks.size(); ++i)
		{
			if (blocks[i] == 'W')
				++cur_white_cnt;

			if (i >= k - 1)
			{
				if ((i - k) >= 0 && blocks[i - k] == 'W')
				{
					--cur_white_cnt;
				}
				result = std::min(result, cur_white_cnt);
			}
		}
		return result;
	}
};