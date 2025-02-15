
/*
    monoton deque
*/
#include <iostream>
#include <vector>
#include <deque>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::deque<int> D;  // keep decreesing order, push front
    int N, L;
    std::cin >> N >> L;
    std::vector<int> A(N);
    for (int i = 0; i < N; ++i)
        std::cin >> A[i];
    for (int curPos = 0; curPos < N; ++curPos)
    {
        // update
        // add
        while (!D.empty() && D.front() > A[curPos])
        {
            D.pop_front();
        }
        D.push_front(A[curPos]);
        // erase
        int endPos = curPos - L;
        if (endPos >= 0 && A[endPos] == D.back())
            D.pop_back();
        std::cout << D.back() << ' ';
    }
}