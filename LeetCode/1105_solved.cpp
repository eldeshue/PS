
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
private:
public:
	// solution method
	using tiii = tuple<int, int, int>; // base h, total h, total width
	int minHeightShelves(vector<vector<int>>& books, int shelfWidth)
	{
        vector<int> cache(books.size() + 1, 0); // total height, keep minimum
        // cache[book number] = max Height

        cache[0] = 0;
        cache[1] = books[0][1];
        for (int curIdx = 1; curIdx <= books.size(); ++curIdx)  // move to next shelf
        {
            int capacity = shelfWidth - books[curIdx - 1][0];
            int maxHeight = books[curIdx - 1][1];
            cache[curIdx] = cache[curIdx - 1] + maxHeight;

            int prevIdx = curIdx - 1;
            // keep current shelf
            while (prevIdx > 0 && (capacity - books[prevIdx - 1][0]) >= 0)
            {
                capacity -= books[prevIdx - 1][0];
                maxHeight = max(maxHeight, books[prevIdx - 1][1]);
                cache[curIdx] = min(cache[curIdx], cache[prevIdx - 1] + maxHeight);
                prevIdx--;
            }
        }

        return cache[books.size()];
	}
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();

