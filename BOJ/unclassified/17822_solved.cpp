
/*
		Ư�� ��ȣ�� ����� �ɷ����� ����

		Ư�� �������� Ư�� Ƚ����ŭ ȸ��

		���ǿ� ���� �����ִ��� Ȯ��

		�����ϴ��� �Ǵ�

		���� ������ �Ǵ�

		���� ����� -> ������ ���ڴ� 0

		������ ��� ���ϱ� -> ������ ������ �����ؾ� ��.
*/

/*

#include <iostream>
#include <functional>
#include <algorithm>
#include <ranges>
#include <vector>

using Disk = std::pair<int, std::vector<int>>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int numDisk, diskLen, rotateCnt, x, d, k;
	std::cin >> numDisk >> diskLen >> rotateCnt;
	std::vector<Disk> disks(numDisk, std::make_pair(0, std::vector<int>(diskLen)));
	std::vector<int> totalSumOfDisk(numDisk, 0);
	for (int i = 0; i < numDisk; ++i)
	{
		disks[i].first = i;
		for (int j = 0; j < diskLen; ++j)
		{
			std::cin >> disks[i].second[j];
			totalSumOfDisk[i] += disks[i].second[j];
		}
	}
	std::cin >> x >> d >> k;

	// prepare lambda
	auto isDivideByX = [&x](const Disk& d)->bool { return d.first % x == 0; };
	auto unwrap = [](const Disk& d) {return d.second; };
	auto rotate = [](const auto& d, const bool dir, const int cnt, const int times) {
			
		};
	auto rotateWithDirWithDistWithCnt = std::bind(std::placeholders::_1, d, k, rotateCnt);

	// rotate
	auto targetDisk = disks
		| std::views::filter(isDivideByX)
		| std::views::transform(unwrap)
		| std::views::
		| std::views::transform(rotateWithDirWithDistWithCnt);
	// 

}

*/