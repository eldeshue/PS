
/*
    boj 17387, ���� ���� 2 

    ������ �̿��� ccw �˰���.
    �־��� �� 4���� ������ 2���� ������ �����ϴ��� ���θ� �Ǵ��Ѵ�.

    ���� �� ������ �������� ������ �� ���� ������ �����Ͽ� �� ��ȣ�� ���� �������� Ȯ��
    �ٸ� ������ �������� �� ������ �ݺ���. �̸� ccw �˰����̶� ��.

    �� ���� ccw�� ��� ����� ���� ���ؼ� ������ ���� ���ΰ� ������.
    ccw ��� ���� ���Ͽ� ������.

    ���� ��� �� ��ȣ�� ���� ���̴� -> �� ccw�� ��ȣ�� ����, �� �������� �ʴ´�.
    ��ȣ�� ���ٴ� ���� ������ �Ǵ� ������ �����ϴ� ������ �������� ������ �� ���� �� �ʿ� ���ִ� �����.
    ��ȣ�� �ٸ��ٴ� ���� ������ �Ǵ� ������ �����ϴ� ������ �������� �� ���� �������ٴ� ��.

    �̷��� ������ ������ Ư���� �������� �ǹٸ��� �ص� ���������� ���� �� ����.
        -> ����� �������� ������, �� ������ ���̰� ��Ƽ� �������� �ʴ� ��찡 �̿� �ش�
        -> ���� �ٸ� �� ���� �������� ccw�� �� �� �� �����ϴ� ����.
*/

/*

#include <iostream>
#include <array>

using vec = std::pair<long long, long long>;

// p1p2�� p1p3�� �������Ѻ�.
// ���� �� -> p1 p2 p3�� �ݽð����
// 0 -> �� ���� ��
// ���� �� -> �ð����
int ccw(const vec& p1, const vec& p2, const vec& p3)
{
    long long s = (p2.first - p1.first) * (p3.second - p1.second)
        - (p3.first - p1.first) * (p2.second - p1.second);

    if (s > 0) return 1;
    else if (s == 0) return 0;
    else return -1; 
}

bool isLineIntersect(const std::array<vec, 4> lines)
{
    vec p1 = lines[0];
    vec p2 = lines[1];
    vec p3 = lines[2];
    vec p4 = lines[3];

    // ������ ����, ����� �̱���, 0�̸� �� �� �ϳ��� ����
    long long p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4); // p1p2
    long long p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2); // p3p4

    // is overlapped?
    // �� �� 0�� ��� -> �� ���� ���� ������
    // �� ���� ���� �� ������ �����ϰ�, ���� �Ϻΰ� ��ġ�� �̴� ������
    if (p1p2 == 0 && p3p4 == 0) {
        // sorting
        if (p1 > p2) std::swap(p2, p1);
        if (p3 > p4) std::swap(p3, p4);
        
        return p3 <= p2 && p1 <= p4; // �� ������ ��ġ���� Ȯ��
    }
    
    // �� �� ������ ���;߸� �� ccw�� ����� ��� ������ ���Ѵ�.
    return (p1p2 <= 0) && (p3p4 <= 0);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

    std::array<vec, 4> two_line;
    for (int p = 0; p < 4; ++p)
    {
        std::cin >> two_line[p].first >> two_line[p].second;
    }
    std::cout << isLineIntersect(two_line);
}

*/