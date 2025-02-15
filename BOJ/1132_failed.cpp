// 첫 글자가 0으로 시작할 수는 없음, 따라서 이 부분을 예외로 처리해줘야 함.
#include <iostream>
#include <string>
#include <algorithm>
#include <array>

std::array<char, 10> char_priority;
std::array<std::array<int, 12>, 10> stat{};

// descending order
bool  cmp_alpha_status(int c1, int c2)
{
	c1 -= 'A';
	c2 -= 'A';
	for (int i = 11; i >= 0; --i)
	{
		if (stat[c1][i] == stat[c2][i])
			continue;
		return (stat[c1][i] > stat[c2][i]);
	}
	return (false);
}

void set_alpha()
{
	for (int i = 0; i < 10; ++i)
	{
		char_priority[i] = 'A' + i;
	}
}

unsigned long long cal_alphabet_value(char c, int n)
{
	unsigned long long result = 0;
	unsigned long long radix = 1e11;
	c -= 'A';
	for (int i = 11; i >= 0; --i)
	{
		result += radix * n * stat[c][i];
		radix /= 10;
	}
	return result;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int num_str;
  std::string input_str;
  std::cin >> num_str;
  set_alpha();
  for (int i = 0; i < num_str; ++i)
  {
	std::cin >> input_str;
	for (int j = 0; j < input_str.size(); ++j)
	{
		stat[(int)(input_str[j] - 'A')][input_str.size() - 1 - j]++;
	}
  }
  std::sort(char_priority.begin(), char_priority.end(), cmp_alpha_status);
  unsigned long long result = 0;
  for (int n = 0; n < 10; ++n)
  {
	result += cal_alphabet_value(char_priority[n], 9 - n);
  }
  std::cout << result;
}