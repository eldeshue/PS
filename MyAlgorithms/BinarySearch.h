
#ifndef _BINARY_SEARCH_
#define _BINARY_SEARCH_

#include <vector>
#include <functional>
typedef std::vector<int>::iterator itr;

int BinSearchMin(itr start, itr end, std::function<bool(int)> f)
{ // [ )
  itr low = start, high = end;

  while (low != high)
  {
    int length = high - low;
    length = length >> 1;
    itr mid = low + length;
    f(*mid) ? high = mid : low = mid + 1;
  }

  if (low == end)
  {
    return -1;
  }
  else
  {
    return (low - start); // index of min value that satisfying condition
  }
}

int BinSearchMax(itr start, itr end, std::function<bool(int)> f)
{ // ( ]
  itr low = start, high = end;

  while (low != high)
  {
    int length = high - low + 1;
    length = length >> 1;
    itr mid = low + length;
    f(*mid) ? low = mid : high = mid - 1;
  }

  if (low == start)
  {
    return -1;
  }
  else
  {
    return (low - start - 1); // index of min value that satisfying condition
  }
}

#endif