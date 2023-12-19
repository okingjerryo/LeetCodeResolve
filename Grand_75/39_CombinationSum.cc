#define assertm(exp, msg) assert(((void)msg, exp))
// #define NDEBUG
#include <cassert>
#include <vector>

bool findCombCore(std::vector<std::vector<int>>& ret, std::vector<int>& candidate, int target, const std::vector<int>& last)
{
  if (target<0) return false;

  for (auto elem: candidate) {
    if (elem > target) break; // Stop advanced

    if (!last.empty() && elem< *(last.cend()-1)) continue; // Stop branch
    std::vector<int> curr(last.begin(),last.end());
    curr.push_back(elem);
    if (elem == target) {
      ret.emplace_back(curr.cbegin(),curr.cend());
      return true;
    } else {
      findCombCore(ret,candidate,target-elem,curr);
    }
  }
  return false;
}
// first solution, traverse based. will waste memory.
class FirstSolution {
public:
  static std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
    std::ranges::sort(candidates);
    std::vector<std::vector<int>> ret;
    std::vector<int> last;
    findCombCore(ret,candidates,target,last);
    return ret;
  }
};


bool checkTwoDimVector(std::vector<std::vector<int>> a, const std::vector<const std::vector<int>>& b)
{
  if (a.size()!=b.size()) return false;
  for (int i = 0; i<a.size(); ++i) {
    if (a[i].size()!=b[i].size()) return false;
    for (int j=0;j<a[i].size();++j) {
      if (a[i][j]!=b[i][j]) return false;
    }
  }
  return true;
}

int main(int argc, char* argv[])
{
  using Solution = FirstSolution;
  std::vector<int> test = {2,3,6,7};
  // assert(checkTwoDimVector(Solution::combinationSum(test,7),{{2,2,3},{7}}));
  test = {2,3,5};
  assert(checkTwoDimVector(Solution::combinationSum(test,8),{{2,2,2,2},{2,3,3},{3,5}}));
  test = {2};
  assert(checkTwoDimVector(Solution::combinationSum(test,1),{}));
}
