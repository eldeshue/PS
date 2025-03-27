
#include <vector>

using namespace std;

#include <algorithm>

class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        // sweeping
        using Seg = pair<int, int>;
        vector<Seg> buffer;
        transform(meetings.begin(), meetings.end(), back_inserter(buffer), [](auto const &vec){
            return Seg(vec[0], vec[1]);
        });
        buffer.push_back(Seg(days + 1, 2e9));
        sort(buffer.begin(), buffer.end(), less<Seg>());

        int result = 0;
        int last_day = 0;
        for (Seg const meeting : buffer)
        {
            if (last_day < meeting.first)
            {
                result += meeting.first - last_day - 1;
            }
            last_day = max(last_day, meeting.second);
        }
        return result;
    }
};
