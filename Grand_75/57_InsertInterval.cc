#define assertm(exp, msg) assert(((void)msg, exp))
// #define NDEBUG
#include <cassert>

#include <iostream>
#include <vector>
struct Area
{
  explicit Area(const std::vector<int>& input)
  {
    start = input.at(0);
    end = input.at(1);
  }

  int start;
  int end;
};

class Solution
{
public:
  static std::vector<std::vector<int>> insert(const std::vector<std::vector<int>>& intervals, const std::vector<int>& newInterval)
  {
    std::vector<Area> opVec;
    // build data structure
    opVec.reserve(intervals.size());
    for (const auto& elem : intervals) {
      opVec.emplace_back(elem);
    }
    Area willEffect(newInterval);

    auto position = opVec.begin();
    auto iter = opVec.begin();
    while (iter!=opVec.end()) {
      Area& elem = *iter;
      // not overlap of target
      if (elem.end < willEffect.start || elem.start > willEffect.end) {
        ++iter;
        if (elem.end < willEffect.start ) position = iter; // if willEffect is over, update the insertion place.
        continue;
      }
      // has overlap, need merge,
      willEffect.start = std::min(elem.start,willEffect.start);
      willEffect.end = std::max(elem.end,willEffect.end);
      iter = opVec.erase(iter);
      position = iter;
    }
    opVec.insert(position,willEffect);
    // construct re;
    std::vector<std::vector<int>> re;
    re.reserve(opVec.size());
    for (const auto& elem: opVec) {
      re.push_back({elem.start,elem.end});
    }
    return re;
  }
};

bool checkResult(const std::vector<std::vector<int>>& vec1, const std::vector<std::vector<int>>&vec2)
{
  if (vec1.size()!=vec2.size()) return false;
  for (int i =0;i<vec1.size();i++) {
    if (vec1.at(i)!=vec2.at(i)) return false;
  }
  return true;
}
int main(int argc, char* argv[])
{
  assert(checkResult(Solution::insert({{1,3},{6,9}},{2,5}),{{1,5},{6,9}}));
  assert(checkResult(Solution::insert({{1,2},{3,5},{6,7},{8,10},{12,16}},{4,8}),{{1,2},{3,10},{12,16}}));
  assert(checkResult(Solution::insert({{1,2}},{4,8}),{{1,2},{4,8}}));
  assert(checkResult(Solution::insert({{4,8}},{1,2}),{{1,2},{4,8}}));
  assert(checkResult(Solution::insert({},{1,2}),{{1,2}}));
}
