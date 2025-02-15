
#include <iostream>
#include <string>

std::string str;
int cursor;

void movLeft()
{
	if (cursor > 0)
	{
		cursor--;
	}
}

void movRight()
{
	if (cursor < str.size())
	{
		cursor++;
	}
}

void delChar()
{
	if (cursor > 0)
	{
		cursor--;
		str.erase(str.begin() + cursor);
	}
}

void insertChar(char c)
{
	if (cursor < str.size())
	{
		str.insert(str.begin() + cursor, c);
	}
	else if(cursor == str.size())
	{
		str.push_back(c);
	}
	cursor++;
}



int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	char c;
	int numCommand;
	std::cin >> str >> numCommand;
	cursor = str.size();
	for (int i = 0; i < numCommand; ++i)
	{
		std::cin >> c;
		switch (c)
		{
		case 'L':
			movLeft();
			break;
		case 'D':
			movRight();
			break;
		case 'B':
			delChar();
			break;
		case 'P':
			std::cin >> c;
			insertChar(c);
			break;
		default:
			break;
		}
	}

	std::cout << str;
}