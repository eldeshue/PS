// 하노이의 탑.
// 제한적인 큰 수 연산.
#include <iostream>
#include <string>
#include <stack>

int N;
std::stack<int> tower[3];

class BigInt // actually, unsigned int
{
private:
	std::string numStr;

public:
	BigInt(int n) { numStr = std::to_string(n); };
	~BigInt() { numStr.clear(); };
	BigInt& operator*(int n);
	BigInt& operator--();

	friend std::ostream& operator<<(std::ostream& o, const BigInt& i);
};

std::ostream& operator<<(std::ostream& o, const BigInt& i) { 
	auto itr = i.numStr.rbegin();
	while (itr != i.numStr.rend()) // little endian, 낮은 주소에 낮은 자리 값, 역순으로 출력해야 함.
	{
		o << *itr; 
		itr++;
	}

	return o;
}

void moveTower(int from, int to, int rest, int size)
{
	if (size == 0)
	{
		return;
	}
	else
	{
		//
		moveTower(from, rest, to, size - 1);
		// move lowest level	
		tower[to].push(tower[from].top());
		tower[from].pop();
		std::cout << "\n" << from + 1 << " " << to + 1;
		//
		moveTower(rest, to, from, size - 1); 
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	for (int i = N; i >= 1; --i)
	{
		tower[0].push(i);
	}
	BigInt result(1);
	for (int i = 0; i < N; ++i)
	{
		result * 2; // pow(2, N);
	}
	std::cout << (--result);
	
	if (N <= 20)
	{
		moveTower(0, 2, 1, N);
	}
}

BigInt& BigInt::operator*(int n) // 제한적인 큰 수 연산, 곱하는 수 n이 1자리 수여야 가능
{
	int carry = 0, digit = 0;
	for (int i = 0; i < numStr.size(); ++i)
	{
		carry += (numStr[i] - '0') * n;
		numStr[i] = '0' + (carry % 10);
		carry /= 10;
	}
	if (carry > 0)
	{
		numStr.push_back('0' + carry);
	}
	return *this;
}
BigInt& BigInt::operator--() // 제한적인 큰 수 연산, unsigned에 대해서만 작동함
{
	bool borrow = true;
	for (int i = 0; i < numStr.size(); ++i)
	{
		if (borrow && numStr[i] == '0')
		{
			numStr[i] = '9';
		}
		else if (borrow)
		{
			numStr[i]--;
			borrow = false;
		}
		else
		{
			break;
		}
	}
	return *this;
}
