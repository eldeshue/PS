
#include <iostream>
#include <vector>

class A
{
public:
	A() { std::cout << "A constructor called.\n"; };
};

class B
{
public:
	B(A &&a) { std::cout << "B constructor called.\n"; };
};

int main()
{
	int b = 44;
	decltype(std::move(42)) rb = 3;
	std::cout << b << ' ' << rb << '\n';
	b = 42;
	rb = 44;
	std::cout << b << ' ' << rb << '\n';
}
