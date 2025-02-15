
#include <iostream>
#include <string>
#include <stack>
#include <vector>

int N;
std::stack<int> st;
std::vector<int> inputBuffer;
std::string resultBuffer;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	inputBuffer.resize(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> inputBuffer[i];
	}

	st.push(0);
	int count = 0, index = 0, num = 1;
	while(count < 2 * N)
	{
		if (st.top() != inputBuffer[index])
		{
			st.push(num);
			resultBuffer.append("+\n");
			num++;
		}
		else // st.top() == inputBuffer[index]
		{
			st.pop();
			resultBuffer.append("-\n");
			index++;
		}
		count++;
	}

	if (num != N + 1)
	{
		std::cout << "NO";
	}
	else
	{
		std::cout << resultBuffer;
	}
}