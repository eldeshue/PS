#include <iostream>
#include <functional>
#include <tuple>
#include <set>
#include <queue>

class BabyShark
{
private:
    int field[20][20];
    int size, sec;
    int stomac;
    int maxLeng;
    int curX, curY, nextX, nextY;

public:
    BabyShark(int L) : maxLeng(L), stomac(0), size(2), sec(0)
    {
        for (int i = 0; i < 20; ++i)
        {
            for (int j = 0; j < 20; ++j)
            {
                field[i][j] = 0;
            }
        }
    };
    ~BabyShark() {};

    void set(int x, int y, int val);
    bool edibleFishBFS();
    void moveAndEat();
    int result() { return sec; };
    void show()
    {
        std::cout << sec << " " << size << "\n";
        for (int i = 0; i < maxLeng; ++i)
        {
            for (int j = 0; j < maxLeng; ++j)
            {
                std::cout << field[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int length, v;
    std::cin >> length;
    BabyShark b(length);
    for (int i = 0; i < length; ++i)
    {
        for (int j = 0; j < length; ++j)
        {
            std::cin >> v;
            b.set(i, j, v);
        }
    }

    while (b.edibleFishBFS()) // cant find edible fish, help
    {
        b.moveAndEat();
        //b.show();
    }
    std::cout << b.result();
}

void BabyShark::set(int x, int y, int val)
{
    if (val == 9)
    {
        curX = x;
        curY = y;
    }
    else
    {
        field[x][y] = val;
    }
}

struct cmpPos {
    bool operator()(std::tuple<int, int, int> const & p1, 
        std::tuple<int, int, int> const & p2) const
	{
		int x1 = std::get<0>(p1), x2 = std::get<0>(p2), 
			y1 = std::get<1>(p1), y2 = std::get<1>(p2),
            t1 = std::get<2>(p1), t2 = std::get<2>(p2);
        if (t1 == t2)
        {
            if (x1 == x2)
            {
                return y1 < y2;
            }
            else
            {
                return x1 < x2;
            }
        }
        else
        {
            return t1 < t2;
        }
   	}
};

bool BabyShark::edibleFishBFS()
{
    // find edible fish, the closest, far north, far whest.
    std::queue<std::tuple<int, int, int>> nextPos;
    bool visited[20][20];
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        {
            visited[i][j] = false;
        }
    }
    int time = 0;
    nextPos.push(std::make_tuple(curX, curY, time));
    visited[curX][curY] = true;

    std::set<std::tuple<int, int, int>, cmpPos> sortedPos;

    int x, y, t, up, down, left, right,
        u_val, l_val, d_val, r_val;
    bool isFish = false;
    while (!nextPos.empty())
    {
        x = std::get<0>(nextPos.front());
        y = std::get<1>(nextPos.front());
        t = std::get<2>(nextPos.front());
        nextPos.pop();

        up = y - 1;
        down = y + 1;
        left = x - 1;
        right = x + 1;
        if (up >= 0)
        {
            u_val = field[x][up];
            if (u_val <= size && !visited[x][up])
			{
				if (0 < u_val && u_val < size) // 값이 0이 아니고, size보다 작다면, 찾음.
				{
                    isFish = true;
                    sortedPos.insert(std::make_tuple(x, up, t + 1));
				}
				// 자신과 같거나, 0인 경우, 지나감.
				// visited
				visited[x][up] = true;
				nextPos.push(std::make_tuple(x, up, t + 1));
			}
        }
        if (left >= 0)
        {
            l_val = field[left][y];
			if (l_val <= size && !visited[left][y])
			{
				if (0 < l_val && l_val < size) // 값이 0이 아니고, size보다 작다면, 찾음.
				{
                    isFish = true;
                    sortedPos.insert(std::make_tuple(left, y, t + 1));
				}
				// 자신과 같거나, 0인 경우, 지나감.
				visited[left][y] = true;
				nextPos.push(std::make_tuple(left, y, t + 1));
			}
        }
        if (down < maxLeng)
        {
            d_val = field[x][down];
			if (d_val <= size && !visited[x][down])
			{
				if (0 < d_val && d_val < size) // 값이 0이 아니고, size보다 작다면, 찾음.
				{
                    isFish = true;
                    sortedPos.insert(std::make_tuple(x, down, t + 1));
				}
				// 자신과 같거나, 0인 경우, 지나감.
				visited[x][down] = true;
				nextPos.push(std::make_tuple(x, down, t + 1));
			}
        }
        if (right < maxLeng)
        {
            r_val = field[right][y];
			if (r_val <= size && !visited[right][y])
			{
				if (0 < r_val && r_val < size) // 값이 0이 아니고, size보다 작다면, 찾음.
				{
                    isFish = true;
                    sortedPos.insert(std::make_tuple(right, y, t + 1));
				}
				// 자신과 같거나, 0인 경우, 지나감.
				visited[right][y] = true;
				nextPos.push(std::make_tuple(right, y, t + 1));
			}
        }
    }
    if (isFish)
    {
		nextX = std::get<0>(*sortedPos.begin());
		nextY = std::get<1>(*sortedPos.begin());
		sec += std::get<2>(*sortedPos.begin());
    }
    return isFish;
}

void BabyShark::moveAndEat()
{
    // move
    curX = nextX;
    curY = nextY;
    // eat
    field[curX][curY] = 0;
    stomac++;
    if (stomac == size) // promotion
    {
        size++;
        stomac = 0;
    }
}