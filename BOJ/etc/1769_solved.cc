#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::string num;
    std::cin >> num;
    int N = std::accumulate(num.begin(), num.end(), 0, [](int const acc, char const c){
       return acc + (c - '0'); 
    });
    if (num.size() == 1)
    {
        std::cout << "0\n" << ((N % 3) ? "NO\n" : "YES\n");
    }
    else
    {
        int cnt = 1;
        while ((N / 10) != 0)
        {
            int tmp = 0;
            while (N)
            {
                tmp += N % 10;
                N /= 10;
            }
            ++cnt;
            N = tmp;
        }
        std::cout << cnt << '\n' << ((N % 3) ? "NO\n" : "YES\n");
    }
}
