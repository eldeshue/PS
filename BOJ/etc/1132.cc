
#include <iostream>
#include <string>
#include <algorithm>
#include <array>

std::array<char, 10> char_priority;
std::array<std::array<int, 14>, 10> stat{};
bool occupied[10];

// descending order
bool  cmp_alpha_status(char c1, char c2)
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
		occupied[i] = false;
	}
}

unsigned long long cal_alphabet_value(char c)
{
	unsigned long long result = 0;
	unsigned long long radix = 1e11;
	c -= 'A';
	for (int i = 11; i >= 0; --i)
	{
		result += radix * stat[c][13] * stat[c][i];
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
	stat[input_str[0] - 'A'][12] = 1;
	for (int j = 0; j < input_str.size(); ++j)
	{
		stat[input_str[j] - 'A'][input_str.size() - 1 - j]++;
		if (input_str[0] != input_str[j])
			stat[input_str[0] - 'A'][12] = 0;
	}
  }
  std::sort(char_priority.begin(), char_priority.end(), cmp_alpha_status);
  // exception handling
  int val = 1;
  for (int n = 9; n >= 0; --n)
  {
	if (stat[char_priority[n] - 'A'][12] == 1)
	{
		stat[char_priority[n] - 'A'][13] = val;
		occupied[val] = true;
		val++;
	}
  }
  // set value
  val = 9;
  for (int n = 0; n < 10; ++n)
  {
	while (occupied[val] == true)
		val--;
	if (stat[char_priority[n] - 'A'][12] == 1)
		continue ;
	stat[char_priority[n] - 'A'][13] = val;
	val--;
  }
  //
  unsigned long long result = 0;
  for (int n = 0; n < 10; ++n)
  {
	result += cal_alphabet_value(char_priority[n]);
  }
  std::cout << result;
}
