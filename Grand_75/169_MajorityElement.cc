#define assertm(exp, msg) assert(((void)msg, exp))
// #define NDEBUG
#include <cassert>
#include <vector>

class Solution {
public:
  static int majorityElement(const std::vector<int>& nums) {
    int curMax {}, curCount = 0;
    for (auto &elem : nums) {
      if (!curCount) {
        curMax = elem;
        ++curCount;
        continue;
      }
      if (elem == curMax) {
        ++curCount;
      } else {
        --curCount;
      }
    }
    return curMax;
  }
};

int main(int argc, char* argv[])
{
  assert(Solution::majorityElement({3,2,3})==3);
  assert(Solution::majorityElement({2,2,1,1,1,2,2})==2);
}
