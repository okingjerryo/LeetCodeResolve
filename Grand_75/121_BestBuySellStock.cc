#include <vector>
#define assertm(exp, msg) assert(((void)msg, exp))
// #define NDEBUG
#include <cassert>
class Solution {
public:
  static int maxProfit(const std::vector<int>& prices) {
    int minHis = INT_MAX,re = 0;
    for (const auto& elem: prices)
    {
      minHis = std::min(minHis,elem);
      re = std::max(elem - minHis,re);
    }
    return re;
  }
};

int main(int argc, char* argv[])
{
  assert(Solution::maxProfit({0}) == 0);
  assert(Solution::maxProfit({7,1,5,3,6,4}) == 5);
  assert(Solution::maxProfit({7,6,4,3,1}) == 0);

}
