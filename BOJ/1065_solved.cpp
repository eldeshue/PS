
#include <iostream>

int main()
{
    int N, cnt = 0;
    std::cin >> N;
    for (int start = 1; start < 10; ++start)
    {
        // const
        int curVal = start, sum = start;
        while (sum <= N)
        {
            cnt++;
            sum = sum * 10 + start;
        }
        for (int d = 1; d < 10; ++d)
        {
            // increasing
            curVal = start + d;
            sum = start * 10 + curVal;
            while (curVal < 10 && sum <= N)
            {
                cnt++;
                curVal += d;
                sum = 10 * sum + curVal;
            }
            // decreasing
            curVal = start - d;
            sum = start * 10 + curVal;
            while (curVal >= 0 && sum <= N)
            {
                cnt++;
                curVal -= d;
                sum = sum * 10 + curVal;
            }
        }
    }
    std::cout << cnt;
}