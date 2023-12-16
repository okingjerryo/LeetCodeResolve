#define assertm(exp, msg) assert(((void)msg, exp))
// #define NDEBUG
#include <cassert>

#include <vector>

// The basic idea is as follows:
// First, sort the array. This allows for direct movement of locations based on the current sum status.
//    Since the goal is to achieve a sum of zero, any initial pointers exceeding zero should be skipped.
//    Assume a location 'cur' is less than 0, then the other two pointers will be positioned after 'cur'.
//      If equal to zero: record the current combination and move to the next positions of 'r' and 'l'.
//      If not equal to zero: move 'r' left if the sum is over zero, or move 'l' right if the sum is less than zero.


class Solution {
public:
  static std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::ranges::sort(nums);
    std::vector<std::vector<int>> re;
    for (auto cIter = nums.cbegin(); cIter!=nums.cend(); ++cIter) {
      if (*cIter > 0) break;
      auto bIter = cIter+1;
      auto eIter = nums.end()-1;
      if (cIter> nums.cbegin() && (*cIter==*(cIter-1))) continue;
      while (bIter<eIter) {
        int sum = *cIter + *bIter + *eIter;
        if (!sum) {
          re.push_back({*cIter, *bIter, *eIter});
          // find the next place which not equal curr r;
          do {
            ++bIter;
          } while (bIter<nums.cend() && *bIter==*(bIter-1));
          // find the next place which not equal curr l;
          do {
            --eIter;
          } while (eIter > cIter && *eIter==*(eIter+1));
        } else {
          sum > 0 ? --eIter : ++bIter;
        }
      }
    }
    return re;
  }
};

bool checkVector(const std::vector<std::vector<int>>& src, const std::vector<std::vector<int>>& ref) {
  if (src.size()!=ref.size()) return false;
  for (int i = 0;i<src.size();i++) {
    if (src[i]!=ref[i]) return false;
  }
  return true;
}

int main(int argc, char* argv[])
{
  std::vector<int> test = {-1,0,1,2,-1,-4};
  assert(checkVector(Solution::threeSum(test),{{-1,-1,2},{-1,0,1}}));
  test = {0,0,0};
  assert(checkVector(Solution::threeSum(test),{{0,0,0}}));
  test = {0,1,1};
  assert(checkVector(Solution::threeSum(test),{}));
  test = {0,0,0,0};
  assert(checkVector(Solution::threeSum(test),{{0,0,0}}));
  test = {1,0,0};
  assert(checkVector(Solution::threeSum(test),{}));
  test = {1,0,0,0};
  assert(checkVector(Solution::threeSum(test),{{0,0,0}}));
  test = {-1,0,0,0,2};
  assert(checkVector(Solution::threeSum(test),{{0,0,0}}));
  test = {-3,-3,-5,0};
  assert(checkVector(Solution::threeSum(test),{}));
}
