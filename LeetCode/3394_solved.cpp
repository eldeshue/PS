#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

#include <functional>
#include <algorithm>

class Solution {
private:
	using Seg = pair<int, int>;
	bool sweep(int const MAX, vector<Seg>& buffer)
	{
		// sort
		sort(buffer.begin(), buffer.end(), less<Seg>());

		// sweep
		int result = 0;
		int lastPos = buffer.begin()->second;
		for (auto const [s, e] : buffer)
		{
			if (lastPos <= s)
			{
				++result;
			}
			lastPos = max(lastPos, e);
		}
		return (result >= 2);
	};
public:
	bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
		int const N = rectangles.size();
		vector<Seg> buffer(N);

		// vertical
		transform(rectangles.begin(), rectangles.end(), buffer.begin(),
			[](vector<int> const& rec)
			{
				return make_pair(rec[0], rec[2]);
			});
		if (sweep(n, buffer)) return true;

		// horizontal
		transform(rectangles.begin(), rectangles.end(), buffer.begin(),
			[](vector<int> const& rec)
			{
				return make_pair(rec[1], rec[3]);
			});
		if (sweep(n, buffer)) return true;

		return false;
	}

};

