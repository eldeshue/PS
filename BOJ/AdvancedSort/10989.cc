// 수 정렬하기 3
// 메모리 제한이 8MB이고, 입력받는 숫자 최대 개수는 1천만개이다.
// 즉 입력받은 수를 모두 할당하면 무조건 메모리를 초과한다.
// 다만, 입력으로 주어지는 수의 범위가 10000으로 상당히 작다.
// 즉 이는  counting sort를 사용함이 옳다.
#include <iostream>

int table[10000] = {}; // 배열을 일종의 해시맵처럼 사용하여 입력받은 정렬대상의 수를 count함.

void set_table(int num)
{
  ++table[num - 1];
}

void print_table()
{
  for (int index = 0; index < 10000; ++index)
  {
    while (table[index] > 0)
    {
      int value = index + 1;
      std::cout << value << "\n";
      --table[index];
    }
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i)
  {
    int temp;
    std::cin >> temp;
    set_table(temp);
  }

  print_table();
}