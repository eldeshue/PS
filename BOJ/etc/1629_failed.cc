
#include <iostream>
#include <cmath>
#include <queue>

std::queue<int> PF;

void preProcess(int &A, int &B)
{
  int i = 2;
  while (i < A && i < B)
  {
    if ((A % i == 0) && (B % i == 0))
    {
      A /= i;
      B /= i;
    }
    else
    {
      i++;
    }
  }
}
void findPrimeFactor(int tgt)
{
  int i = 2;
  while (tgt != 1)
  {
    if ((tgt % i) == 0)
    {
      PF.push(i);
      tgt /= i;
    }
    else
    {
      i++;
    }
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int A, B, C;
  std::cin >> A >> B >> C;

  findPrimeFactor(B);

  while (true)
  {
    if (A >= C)
    {
      A = A % C;
    }

    if (A != 0 && !PF.empty())
    {
      A = std::pow(A, PF.front());
      PF.pop();
    }
    else
    {
      std::cout << A;
      return 0;
    }
  }
}