
// 큰 수 연산을 극복하자.

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <set>

int char36_to_int(char c)
{
	if (isalpha(c))
	{
		return (c - 'A' + 10);
	}
	return (c - '0');
}
char int_to_char36(int i)
{
	const static char radix[36] = 
	{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	return (radix[i % 36]);
}

class num36	// 36 base, big number.
{
private:
	char full_adder36(char c1, char c2, char &carry) const
	{
		int i1 = char36_to_int(c1);
		int i2 = char36_to_int(c2);
		int i3 = char36_to_int(carry);
		carry = int_to_char36((i1 + i2 + i3) / 36);
		return int_to_char36((i1 + i2 + i3) % 36);
	}
	void reverse_num()
	{
		for (int i = 0; i < num.size() / 2; ++i)
			std::swap(num[i], num[num.size() - 1 - i]);
	}

public:
	std::string num;		// member variable
	num36() : num("0") {};
	num36(const std::string& input) : num(input) {};
	num36(int len, char c) 
	{
		for (int i = 0; i < len; ++i)
		{
			num.push_back('0');
		}
		num.push_back(c);
		reverse_num();
	}
	~num36() {};

	char& at(int idx) { return num[idx]; };
	void print() { std::cout << num; };
	num36& operator=(const num36& ref)
	{
		this->num = ref.num;
		return *this;
	}
	num36 operator+(const num36& ref) const
	{
		num36 result("");	// empty string
		char carry = '0';

		const num36* pref = &ref;
		num36* s = const_cast<num36 *>(this); // const cast to swap s & l
		num36* l = const_cast<num36 *>(pref); // do not change the content.
		if (s->num.size() > l->num.size())
		{
			std::swap(s, l);
		}
		int idx = 0;
		for (; idx < s->num.size(); ++idx)
		{
			result.num.push_back(full_adder36(l->num[l->num.size() - 1 - idx], 
				s->num[s->num.size() - 1 - idx], carry));
		}
		while (true)
		{
			if (idx == l->num.size())
			{
				if (carry != '0')
					result.num.push_back(carry);
				break;
			}
			result.num.push_back(full_adder36(l->num[l->num.size() - 1 - idx], 
				'0', carry));
			idx++;
		}
		result.reverse_num();
		return result;
	}
};

std::vector<num36> numbers;
num36 priority[36];

std::vector<int> idx_arr;

bool cmp_idx(const int idx1, const int idx2)
{
	if (priority[idx1].num.size() != priority[idx2].num.size())
		return (priority[idx2].num.size() < priority[idx1].num.size());
	for (int i = 0; i < priority[idx1].num.size(); ++i)
	{
		if (priority[idx2].num[i] != priority[idx1].num[i])
			return (priority[idx2].num[i] < priority[idx1].num[i]);
	}
	return (false);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	idx_arr.resize(36);
	for (int i = 0; i < 36; ++i)	// index buffer for sorting.
	{
		idx_arr[i] = i;
	}

	int N, K;
	std::string input;
	std::set<char> target;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		numbers.push_back(num36(input));
		for (int i = 0; i < input.size(); ++i)
		{
			// setting priority for greedy
			int cur_num = char36_to_int(input[i]);
			priority[cur_num] 
				= priority[cur_num] 
				+ num36(input.size() -1 - i, int_to_char36(35 - cur_num));	// 35 = 'Z'
		}
	}
	std::cin >> K;
	std::sort(idx_arr.begin(), idx_arr.begin() + 35, cmp_idx);
	for (int i = 0; i < K; ++i)	// 상위 우선순위 K개를 변화 대상으로 저장...
	{
		target.insert(int_to_char36(idx_arr[i]));
	}
	// 각각의 값을 변환하고 덧셈, 큰 수 곱셈을 못하므로...
	num36 result;
	for (int i = 0; i < N; ++i)
	{
		// 값 변환
		for (char& cur_char : numbers[i].num)
		{
			if (target.find(cur_char) != target.end())
			{
				cur_char = 'Z';
			}
		}
		// 누적 합
		result = result + numbers[i];
	}
	result.print();
}