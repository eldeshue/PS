#include <iostream>
#include <memory.h>
#include <queue>
#include <string>
#include <vector>

using point = std::pair<int, int>;

int h, w, cnt;
int board[100][100];
bool keys[26];
std::vector<point> doors[26];		// y, x
std::queue<point> Q;	// only for available position.

bool pos_sanity_check(int y, int x)
{
	if (!(0 <= y && y < h) || !(0 <= x && x < w))
		return false;
	return true;
}

void handle_next_pos(int y, int x)
{
	int& val = board[y][x];
	if (val == '*')
		return ;
	else if (val == '.')
	{
		Q.push(std::make_pair(y, x));
	}
	else if (val == '$')
	{
		cnt++;
		Q.push(std::make_pair(y, x));
	}
	else if ('a' <= val && val <= 'z') // key
	{
		keys[val - 'a'] = true;
		Q.push(std::make_pair(y, x));
		if (!doors[val - 'a'].empty())
		{
			for (const auto& door_pos : doors[val - 'a'])
			{
				Q.push(door_pos);
				board[door_pos.first][door_pos.second] = '*';
			}
			doors[val - 'a'].clear();
		}
	}
	else if ('A' <= val && val <= 'Z') // door
	{
		if (keys[val - 'A'] == true)
		{
			Q.push(std::make_pair(y, x));
		}
		else
		{
			doors[val - 'A'].push_back(std::make_pair(y, x));
		}
	}
	val = '*';	// visited;
}

void find_entrance()
{
	for (int i = 0; i < h - 1; ++i)
		handle_next_pos(i, 0);
	for (int i = 1; i < h; ++i)
		handle_next_pos(i, w - 1);
	for (int i = 0; i < w - 1; ++i)
		handle_next_pos(h - 1, i);
	for (int i = 1; i < w; ++i)
		handle_next_pos(0, i);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int num_test;
	std::string input_buffer;
	std::cin >> num_test;
	for (int i = 0; i < num_test; ++i)
	{
		// taking input
		cnt = 0;
		memset(keys, 0, sizeof(keys));
		for (int j = 0; j < 26; ++j)
			doors[j].clear();
		std::cin >> h >> w;
		for (int row = 0; row < h; ++row) // board
		{
			std::cin >> input_buffer;
			for (int col = 0; col < w; ++col)
			{
				board[row][col] = input_buffer[col];
			}
		}
		std::cin >> input_buffer; // keys
		for (const char& c : input_buffer)
		{
			if (c == '0')
				break;
			keys[c - 'a'] = true;
		}
		// init Q
		find_entrance();
		// BFS start
		while(!Q.empty())
		{
			int y = Q.front().first;
			int x = Q.front().second;
			Q.pop();
			if (pos_sanity_check(y - 1, x) == true)
				handle_next_pos(y - 1, x);
			if (pos_sanity_check(y, x + 1) == true)
				handle_next_pos(y, x + 1);
			if (pos_sanity_check(y + 1, x) == true)
				handle_next_pos(y + 1, x);
			if (pos_sanity_check(y, x - 1) == true)
				handle_next_pos(y, x - 1);
		}
		// debugging
		/*
		for (int j = 0; j < h; ++j)
		{
			for (int k = 0; k < w; ++k)
			{
				std::cout << (char)board[j][k] << ' ';
			}
			std::cout << '\n';
		}
		*/
		std::cout << cnt << '\n';
	}
}
