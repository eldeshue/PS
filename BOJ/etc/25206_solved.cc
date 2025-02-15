
#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, float> gradeToScore = {
	{"A+", 4.5f},
	{"A0", 4.0f},
	{"B+", 3.5f},
	{"B0", 3.0f},
	{"C+", 2.5f},
	{"C0", 2.0f},
	{"D+", 1.5f},
	{"D0", 1.0f},
	{"F", 0.0f},
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string grade;
	float totalScore = 0.0f, maxScore = 0.0f, input;
	for (int i = 0; i < 20; ++i)
	{
		std::cin >> grade >> input >> grade;
		if (grade != "P")
		{
			totalScore += input * gradeToScore[grade];
			maxScore += input;
		}
	}
	std::cout << std::fixed;
	std::cout.precision(6);
	std::cout << totalScore / maxScore;
}
