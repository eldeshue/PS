
#include <iostream>
#include <stack>
#include <queue>
#include <memory.h>

short int start, goal;
bool visited[10000];

short int Double(const short int num)
{
    return (num * 2) % 10000;
}

short int Sub(const short int num)
{
    if (num == 0)
    {
        return 9999;
    }
    else
    {
        return num - 1;
    }
}

short int Rshift(const short int num)
{
    short int r = num % 10;
    return num / 10 + 1000 * r;
}

short int Lshift(const short int num)
{
    short int l = num / 1000;
    return (num % 1000) * 10 + l;
}

void BFS()
{
    std::queue<std::pair<unsigned long long, short int>> nextNode;
    nextNode.push(std::make_pair(1, start));
    memset(visited, 0, sizeof(visited));

    short int nexNum;
    short int curNum;
    unsigned long long curStat;
    while (!nextNode.empty())
    {
        curStat = nextNode.front().first;
        curNum = nextNode.front().second;
        nextNode.pop();
        if (curNum == goal)
        {
            break;
        }
        nexNum = Double(curNum);
        if (visited[nexNum] != true)
        {
            visited[nexNum] = true;
            nextNode.push(std::make_pair((curStat << 2) + 0, nexNum));
        }
        nexNum = Sub(curNum);
        if (visited[nexNum] != true)
        {
            visited[nexNum] = true;
            nextNode.push(std::make_pair((curStat << 2) + 1, nexNum));
        }
        nexNum = Lshift(curNum);
        if (visited[nexNum] != true)
        {
            visited[nexNum] = true;
            nextNode.push(std::make_pair((curStat << 2) + 2, nexNum));
        }
        nexNum = Rshift(curNum);
        if (visited[nexNum] != true)
        {
            visited[nexNum] = true;
            nextNode.push(std::make_pair((curStat << 2) + 3, nexNum));
        }
    }
    std::stack<char> result;
    while (curStat != 1)
    {
        switch (curStat & 3)
        {
        case 3:
            result.push('R');
            break;
        case 2:
            result.push('L');
            break;
        case 1:
            result.push('S');
            break;
        case 0:
            result.push('D');
            break;
        default:
            break;
        }
        curStat = curStat >> 2;
    }
    while (!result.empty())
    {
        std::cout << result.top();
        result.pop();
    }
    std::cout << "\n";
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    short int numTest;
    std::cin >> numTest;
    for (short int i = 0; i < numTest; ++i)
    {
        std::cin >> start >> goal;
        BFS();
    }
}