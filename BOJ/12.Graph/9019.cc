#include <iostream>
#include <string>
#include <queue>

short int start, goal;

short int Double(const short int &num)
{
  if (num > 5000)
  {
    return (num * 2) % 10000;
  }
  else
  {
    return num * 2;
  }
}

short int Sub(const short int &num)
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

short int Rshift(const short int &num)
{
  short int r = num % 10;
  return num / 10 + 1000 * r;
}

short int Lshift(const short int &num)
{
  short int l = num / 1000;
  return (num % 1000) * 10 + l;
}

void BFS()
{
  // 비트마스킹
  std::queue<std::string> nextNode;
  nextNode.push("");

  short int curNum = start;
  std::string curStat;
  // BFS
  while (!nextNode.empty())
  {
    curStat = nextNode.front();
    curNum = start;
    nextNode.pop();
    for (const auto &c : curStat)
    {
      switch (c)
      {
      case 'D':
        curNum = Double(curNum);
        break;
      case 'S':
        curNum = Sub(curNum);
        break;
      case 'L':
        curNum = Lshift(curNum);
        break;
      case 'R':
        curNum = Rshift(curNum);
        break;

      default:
        break;
      }
    }
    if (curNum == goal)
    {
      break;
    }
    // exponential 하게 queue가 증가함.
    // 하지만 별도의 방법으로 큐에 안집어넣기도 좀 그런데....
    nextNode.push(curStat + 'D');
    nextNode.push(curStat + 'S');
    nextNode.push(curStat + 'L');
    nextNode.push(curStat + 'R');
  }
  std::cout << curStat << "\n";
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