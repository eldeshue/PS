
#include <iostream>
#include <string>
#include <memory.h>

bool is_row[50];
bool is_col[50];

int main()
{
    memset(is_row, 0, sizeof(is_row));
    memset(is_col, 0, sizeof(is_col));
    std::string input;
    int row, col;
    std::cin >> row >> col;
    for (int r = 0; r < row; ++r)
    {
        std::cin >> input;
        for (int c = 0; c < col; ++c)
        {
            if (input[c] == 'X')
            {
                is_row[r] = true;
                is_col[c] = true;
            }
        }
    }
    int count1 = 0, count2 = 0;
    for (int i = 0; i < col; ++i)
    {
        if (is_col[i] == false)
            count1++;
    }
    for (int i = 0; i < row; ++i)
    {
        if (is_row[i] == false)
            count2++;
    }
    std::cout << std::max(count1, count2);
}