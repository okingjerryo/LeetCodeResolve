#include <vector>
#include <iostream>
#include <numeric>

#define assertm(exp, msg) assert(((void)msg, exp))
// #define NDEBUG
#include <cassert>

class Solution {
public:
  static int pivotIndex(const std::vector<int>&nums) {
    if (nums.empty()) return -1;
    int rightSum = std::accumulate(nums.cbegin(), nums.cend(), 0);
    int leftSum = 0;
    for (int i = 0; i < nums.size(); i++) {
      rightSum -= nums[i];
      if (leftSum == rightSum) return i;
      leftSum += nums[i];
    }
    return -1;
  }
};

int main(int argc, char* argv[]) {
  assert(Solution::pivotIndex({}) == -1);
  assert(Solution::pivotIndex({0}) == 0);
  assert(Solution::pivotIndex({0}) == 0);
  assert(Solution::pivotIndex({1, 7, 3, 6, 5, 6}) == 3);
  assert(Solution::pivotIndex({1, 2, 3}) == -1);
  assert(Solution::pivotIndex({2, 1, 1}) == -1);
}
