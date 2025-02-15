// time out
#include <iostream>
#include <stack>

std::stack<int> RB_stack;
int data[1000000];

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  // input
  int N;
  std::cin >> N;
  for (int h = 0; h < N; ++h)
  {
    std::cin >> data[h];
  }

  // calculate
  for (int i = N - 1; i >= 0; --i)
  {
    int standard = data[i];

    if (RB_stack.empty())
    {
      data[i] = -1;
      RB_stack.push(standard);
    }
    else if (standard >= RB_stack.top())
    {
      RB_stack.pop();
      i++;
    }
    else
    {
      data[i] = RB_stack.top();
      RB_stack.push(standard);
    }
  }

  // output
  for (int j = 0; j < N; ++j)
  {
    std::cout << data[j] << " ";
  }
  std::cout << std::endl;
}