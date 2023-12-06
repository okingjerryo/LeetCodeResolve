#include <vector>
#include <unordered_map>
#define assertm(exp, msg) assert(((void)msg, exp))
// #define NDEBUG
#include <cassert>

class Solution {
public:
  static std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    // use a map to store an index history.
    std::unordered_map<int,int> historyMap{};

    for (auto iter =nums.cbegin(); iter!=nums.cend(); ++iter) {
      auto cIdx = static_cast<int>(iter-nums.cbegin());
      auto findIter = historyMap.find(target-*iter);

      if (findIter!=historyMap.end()) {
        return {findIter->second,cIdx};
      }
      historyMap.insert({*iter,cIdx});
    }
    return {-1,-1};
  }
};

bool checkVector(const std::vector<int> src, const std::vector<int> ref) {
  if (src.size()!=ref.size()) return false;
  for (int i = 0;i<src.size();i++) {
    if (src[i]!=ref[i]) return false;
  }
  return true;
}
int main(int argc, char* argv[]) {
  assert(checkVector(Solution::twoSum({2,7,11,15},9), {0,1}));
  assert(checkVector(Solution::twoSum({3,2,4},6), {1,2}));
  assert(checkVector(Solution::twoSum({3,3},6), {0,1}));
  assert(checkVector(Solution::twoSum({3,3},7), {-1,-1}));
}
