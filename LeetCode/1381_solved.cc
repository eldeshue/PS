
#include <iostream>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")

class CustomStack
{
private:
	const int maxSize;
	int *const pData;
	int *const pLazy;
	int sp;

public:
	CustomStack(int maxSize) : maxSize(maxSize), pData(new int[maxSize]), pLazy(new int[maxSize]), sp(-1)
	{
		for (int i = 0; i < maxSize; ++i)
			pLazy[i] = 0;
	}

	void push(int x)
	{
		if (sp == maxSize - 1)
			return;
		sp++;
		pData[sp] = x;
	}

	int pop()
	{
		if (sp == -1)
			return -1;
		const int result = pData[sp] + pLazy[sp];
		if (sp > 0)
			pLazy[sp - 1] += pLazy[sp];
		pLazy[sp] = 0;
		sp--;
		return result;
	}

	void increment(int k, int val)
	{
		if (k - 1 > sp)
			k = sp + 1;
		if (k > 0)
			pLazy[k - 1] += val;
	}
};

auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}
