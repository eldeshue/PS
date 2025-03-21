
#include <iostream>
#include <string>

bool isCorrectMsg(const std::string& msg, int idx)
{
	if (idx == msg.size() && idx != 0)
		return true;
	// pattern 1, 100+1+
	// find 100,
	else if (idx < msg.size() - 2 && msg[idx] == '1' && msg[idx + 1] == '0' && msg[idx + 2] == '0')
	{
		idx += 3;
		// find 0+
		while (idx < msg.size() && msg[idx] == '0')
		{
			idx++;
		}
		// find 1
		if (idx < msg.size() && msg[idx] == '1')
		{
			bool result = false;
			// find 1+
			idx++;
			while (idx < msg.size() && msg[idx] == '1')
			{
				idx++;
				// ~111,1...
				// or
				// ~1111,0...
				if (idx < msg.size() && msg[idx] == '0')
					result = isCorrectMsg(msg, idx - 1);
			}
			return result | isCorrectMsg(msg, idx);
		}
		else
		{
			return false;
		}
	}
	// pattern 2, 01
	else if (idx < msg.size() - 1 && msg[idx] == '0' && msg[idx + 1] == '1')
	{
		idx += 2;
		return isCorrectMsg(msg, idx);
	}
	else // fail to match pattern 1, 2 -> false
	{
		return false;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string msg;
	int N;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> msg;
		if (isCorrectMsg(msg, 0))
			std::cout << "YES\n";
		else
			std::cout << "NO\n";
	}
}

