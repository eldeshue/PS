// using tabulation
#include <iostream>

long int fibonacci[91];

void calcFibonacci()
{
  fibonacci[0] = 0;
  fibonacci[1] = 1;
  for (int i = 2; i <= 90; ++i)
  {
    fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int N;
  std::cin >> N;
  calcFibonacci();
  // N <= 90
  std::cout << fibonacci[N];
}