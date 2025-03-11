#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

class Solution {
private:
public:
	int numberOfAlternatingGroups(vector<int>& colors, int k) {

		for (int i = 0; i < k - 1; ++i)
		{
			colors.push_back(colors[i]);
		}

		int result = 0, alternate_cnt = 1;
		char prev_color = colors[0];
		for (int i = 1; i < colors.size(); ++i)
		{
			if (prev_color == colors[i])
			{
				alternate_cnt = 1;
			}
			else
			{
				++alternate_cnt;
				result += (alternate_cnt >= k);
			}
			prev_color = colors[i];
		}
		return result;
	}
};