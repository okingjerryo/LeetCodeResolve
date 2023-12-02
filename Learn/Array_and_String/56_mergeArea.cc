#include <vector>
#include <iostream>
#include <numeric>

#define assertm(exp, msg) assert(((void)msg, exp))
// #define NDEBUG
#include <algorithm>
#include <cassert>
#include <list>
#include <queue>

class Area {
public:
  Area(int start, int end):_start(start),_end(end) {}
  explicit Area(const std::vector<int>& ref) {
    _start = ref[0];
    _end = ref[1];
  }

  bool operator<(const Area& rh) const {
    return this->_end < rh._start && this->_start< rh._start;

  }
  bool operator==(const Area& rh) const {
    return this->_end >= rh._start && this->_start <= rh._end;
  }

  bool operator!=(const Area& rh) const {
    return (!operator==(rh));
  }

  bool merge (const Area& rh) {
    if (*this != rh) return false;
    _start = std::min(_start, rh._start);
    _end = std::max (_end, rh._end);
    return true;
  }

  bool exactMatch (const Area& rh) const {
    return (_start == rh._start) && (_end == rh._end);
  }
  std::vector<int> toVector() const {
    return {_start, _end};
  }

  int getStart() const {return _start;}
  int getEnd() const {return _end;}
private:
  int _start;
  int _end;
};
// ref #35 resolve method - operation level expend to Area list.
int findPlace(const std::vector<Area>& query,const Area& target , bool& merge) {
  int start = 0, end = query.size()-1, mid = 0;
  while (start <= end) {
    mid =  (start + end) /2;
    Area midArea = query[mid];
    if (midArea==target) {
      merge = true;
      return mid;
    } else if (midArea < target) {
      start = mid + 1;
    } else {
      end = mid - 1;
    }
  }
  return end + 1;
}
// soluton 1 using vector. but moving object takes so much time.
class SolutionVector {
public:
  static std::vector<std::vector<int>> merge(const std::vector<std::vector<int>>& intervals) {
    std::vector<Area> retArea; // insert at middle may have better performance.
    for (auto& elem: intervals) {
      Area cur(elem);
      bool needMerge = false;
      int i = findPlace(retArea,cur,needMerge);
      if (needMerge) {
        retArea[i].merge(cur);
        auto iter = retArea.begin()+i;
        // the iter front has possiability equal to current due to the new range.
        if (iter > retArea.begin() && *(iter-1) == *(iter)) iter -= 1;
        // from the start to the merge end.
        while (iter+1!=retArea.cend() && (*(iter))==(*(iter+1))) {
          (iter+1)->merge(*(iter));
          iter = retArea.erase(iter);
        }
      } else {
        retArea.insert(retArea.begin()+i, cur);
      }
    }
    // coverter to end
    std::vector<std::vector<int>> ret;
    for (auto& elem: retArea) {
      ret.push_back(std::move(elem.toVector()));
    }
    return ret;
  }
};


// Solucton2 using List to do merging iteration.
// Use list since modification of link list has constance cost.
// 1. Partical sort by the start index
// 2. Merge the accross filed area from begin to after.
// This soluction is better.

class SolutionList {
public:
  static std::vector<std::vector<int>> merge(const std::vector<std::vector<int>>& intervals) {
    // construct
    std::vector<Area> areaVec;
    for (const auto& elem: intervals) {
      areaVec.emplace_back(elem);
    }
    std::sort(areaVec.begin(),areaVec.end(),[](Area& elem1, Area& elem2) {
      return elem1.getStart()< elem2.getStart();
    });
    std::list<Area> areaList;
    for (auto & elem: areaVec) {
      areaList.emplace_back(elem);
    }

    auto iter = areaList.begin();

    while (iter != areaList.end()) {
      auto iterBack = iter;
      iter++;
      if (iter!= areaList.end() && *iterBack == *iter) {
        // need Merge
        iter->merge(*iterBack);
        iter = areaList.erase(iterBack);
      }
    }
    std::vector<std::vector<int>> ret(areaList.size());
    std::transform(areaList.begin(),areaList.end(),ret.begin(),[](Area& elem) {
      return elem.toVector();
    });
    return std::move(ret);
  }
};

bool checkResult(const std::vector<std::vector<int>>& elem1,const std::vector<std::vector<int>>& elem2 ) {
  if (elem1.size()!=elem2.size()) return false;
  for (int i=0;i<elem1.size();i++) {
    if (elem1[i] != elem2[i]) return false;
  }
  return true;
}

using Solution = SolutionList;
int main(int argc, char* argv[]) {
  // Unit test for Area class
  assert(Area(1,2)<Area(3,5));
  assert(Area(1,2)!=Area(3,5));
  assert(Area(1,3)==Area(3,5));
  assert(Area(1,4)==Area(2,5));
  Area a{1,4};
  assert(a.merge(Area(2,5)));
  assert(a.exactMatch({1,5}));
  std::vector<int> vec(a.toVector());
  assert(vec[0] == 1);
  assert(vec[1] == 5);
  // Unit test for the entire soluction
  assert(checkResult(Solution::merge({{1,4},{4,5}}),{{1,5}}));
  assert(checkResult(Solution::merge({{1,4},{0,0}}),{{0,0},{1,4}}));
  assert(checkResult(Solution::merge({{1,4},{0,0}}),{{0,0},{1,4}}));
  assert(checkResult(Solution::merge({{1,3},{2,6},{8,10},{15,18}}),{{1,6},{8,10},{15,18}}));
  assert(checkResult(Solution::merge({{2,3},{4,5},{6,7},{8,9},{1,10}}),{{1,10}}));
  assert(checkResult(Solution::merge({{0,2},{2,3},{4,4},{0,1},{5,7},{4,5},{0,0}}),{{0,3},{4,7}}));

  return 0;
};

