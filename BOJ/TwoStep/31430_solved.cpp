/*
	BOJ 31430

	투 스텝 문제.

	투 스텝은 제출한 프로그램이 두 번 실행됨을 의미함.

	한 번의 실행에서는 A, B를입력으로 받아서 A+B를
	이를 13자 길이의 소문자 알파뱃으로 구성된 문자열로 변환해야 함.

	다음 실행에서는 이 변환된 문자열을 읽어서
	A+B 결과로 다시 복원해야 함.

	소문자 알파뱃으로 구성된 문자열만 가능함을 놓쳤더니, 큰 낭패를 보았다.
*/
#include <algorithm>
#include <iostream>
#include <string>

using ull = unsigned long long;

char from_char_to_hexdec(char i)
{
	i -= 'a';
	if (i >= 10)
	{
		return 'a' + i - 10;
	}
	else
	{
		return '0' + i;
	}
}

std::string solve1(ull A, ull B)
{
	A += B;

	// 16진수 문자열로 변환, 전송
	std::string result(13, '0');
	for (int offset = 0; offset < 13; ++offset)
	{
		result[12 - offset] = 'a' + (A % 26);
		A /= 26;
	}
	return result;
}

ull solve2(std::string& input)
{
	std::transform(input.begin(), input.end(), input.begin(), from_char_to_hexdec);
	return std::stoull(input, 0, 26);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T = 0;
	std::cin >> T;
	if (T == 1)
	{
		ull A, B;
		std::cin >> A >> B;
		std::cout << solve1(A, B);
	}
	else
	{
		std::string input;
		std::cin >> input;
		std::cout << solve2(input);
	}
}