#include <iostream>
#include <bitset>
#include <unordered_map>

int MAXROW, MAXCOLUM;


int DP()
{

}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    char input;
    int testNum;
    
    std::cin >> testNum;
    for (int i = 0; i < testNum; ++i)
    {
        // setting initial status of the room
        
        
        std::cin >> MAXROW >> MAXCOLUM;
        for (int r = 0; r < MAXROW; ++r)
        {
            for (int c = 0; c < MAXCOLUM; ++c)
            {
                std::cin >> input;
                if (input == 'x') // if unavailable. 'x'
                {
                    
                }
            }
        }
        // calculate max people
        std::cout << DP() << "\n";
    }
}