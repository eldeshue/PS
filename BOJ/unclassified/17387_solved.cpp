
/*
    boj 17387, 선분 교차 2 

    외적을 이용한 ccw 알고리즘.
    주어진 점 4개로 구성된 2개의 선분이 교차하는지 여부를 판단한다.

    먼저 한 직선을 기준으로 나머지 두 점과 외적을 수행하여 그 부호로 같은 방향인지 확인
    다른 직선을 기준으로 위 과정을 반복함. 이를 ccw 알고리즘이라 함.

    두 번의 ccw의 결과 얻어진 값을 통해서 선분의 교차 여부가 판정됨.
    ccw 결과 값을 곱하여 판정함.

    곱한 결과 그 부호가 양의 값이다 -> 두 ccw의 부호가 같다, 즉 교차하지 않는다.
    부호가 같다는 것은 기준이 되는 선분을 포함하는 직선을 기준으로 나머지 두 선이 한 쪽에 모여있는 경우임.
    부호가 다르다는 것은 기준이 되는 선분을 포함하는 직선을 기준으로 두 점이 나눠진다는 것.

    이러한 판정은 선분의 특성상 판정값이 옳바르다 해도 교차하지는 않을 수 있음.
        -> 기울기는 평행하지 않지만, 두 선분이 길이가 잛아서 교차하지 않는 경우가 이에 해당
        -> 따라서 다른 한 선을 기준으로 ccw를 또 한 번 수행하는 것임.
*/

/*

#include <iostream>
#include <array>

using vec = std::pair<long long, long long>;

// p1p2와 p1p3를 외적시켜봄.
// 양의 값 -> p1 p2 p3가 반시계방향
// 0 -> 한 직선 위
// 음의 값 -> 시계방향
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

    // 음수면 교차, 양수면 미교차, 0이면 둘 중 하나는 평행
    long long p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4); // p1p2
    long long p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2); // p3p4

    // is overlapped?
    // 둘 다 0인 경우 -> 한 직선 위에 존재함
    // 한 직선 위에 두 선분이 존재하고, 둘의 일부가 겹치면 이는 교차함
    if (p1p2 == 0 && p3p4 == 0) {
        // sorting
        if (p1 > p2) std::swap(p2, p1);
        if (p3 > p4) std::swap(p3, p4);
        
        return p3 <= p2 && p1 <= p4; // 두 선분이 겹치는지 확인
    }
    
    // 둘 다 음수가 나와야만 두 ccw의 결과가 모두 교차를 뜻한다.
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