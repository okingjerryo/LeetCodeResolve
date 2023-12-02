#include <vector>
#include <iostream>
#include <numeric>

#define assertm(exp, msg) assert(((void)msg, exp))
// #define NDEBUG
#include <cassert>
class Solution {
public:
  static int searchInsert(const std::vector<int>& nums, int target) {
    int start = 0, end = nums.size() - 1, mid = 0;
    while (start <= end) {
      mid = (start + end)/2;
      if (nums[mid]  == target) return mid;
      else if (nums[mid] > target ) {
        end = mid - 1;
      } else {
        start = mid + 1;
      }
    }
    return end +1;
  }
};

int main(int argc, char* argv[]) {
  assert(Solution::searchInsert({1,3,5,6}, 5) == 2);
  assert(Solution::searchInsert({1,3,5,6}, 2) == 1);
  assert(Solution::searchInsert({1,3,5,6}, 7) == 4);
  assert(Solution::searchInsert({}, 7) == 0);
  assert(Solution::searchInsert({1}, 7) == 1);
  assert(Solution::searchInsert({7}, 1) == 0);
}
