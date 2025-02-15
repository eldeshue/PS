// Divide & Conquer by Recursion
// solved.
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

typedef std::vector<int>::iterator v_itr;

int main()
{
  // input
  int n, q;
  std::cin >> n;
  std::vector<int> rsc(n);
  for (auto &r_elem : rsc)
  {
    std::cin >> r_elem;
  }
  std::cin >> q;
  std::vector<int> tgt(q);
  for (auto &t_elem : tgt)
  {
    std::cin >> t_elem;
  }
  /*
  // test
  std::vector<int> rsc(5);
  rsc[0] = 1;
  rsc[1] = 5;
  rsc[2] = 7;
  rsc[3] = 10;
  rsc[4] = 21;
  std::vector<int> tgt(4);
  tgt[0] = 2;
  tgt[1] = 4;
  tgt[2] = 17;
  tgt[3] = 8;
  // test
  */
  std::sort(rsc.begin(), rsc.end());

  std::function<bool(int, v_itr)> ok = [&tgt, &rsc, &ok](int target_val, v_itr itr) -> bool { // recurse
    while (itr != rsc.begin())
    {
      if (target_val >= *itr)
      {
        break;
      }
      --itr;
    }

    if (*itr == target_val)
    {
      return true;
    }
    else if (itr == rsc.begin())
    {
      return false;
    }
    else
    {
      return ok(target_val - *itr, itr - 1) || ok(target_val, itr - 1);
    }
  };

  for (const auto &elem : tgt)
  {
    if (ok(elem, rsc.end() - 1))
    {
      std::cout << "yes\n";
    }
    else
    {
      std::cout << "no\n";
    }
  }
}