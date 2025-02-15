
#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout << std::setprecision(10) << std::fixed;

  double total_time = 0;
  double x, y, jump_dist, jump_time, total_dist;
  std::cin >> x >> y >> jump_dist >> jump_time;
  total_dist = std::sqrt(x * x + y * y);
  if (1 >= jump_dist / jump_time)
  {
	std::cout << total_dist;
	return 0;
  }
  if (total_dist < jump_dist)
  {
	std::cout << std::min(jump_time + (jump_dist - total_dist), std::min(2 * jump_time, total_dist));
	return 0;
  }
  while (total_dist > 2 * jump_dist)
  {
	total_time += jump_time;
	total_dist -= jump_dist;
  }
  total_time += std::min(2 * jump_time, jump_time + (total_dist - jump_dist));
  std::cout << total_time;
}
