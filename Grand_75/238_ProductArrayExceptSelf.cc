#define assertm(exp, msg) assert(((void)msg, exp))
// #define NDEBUG
#include <cassert>

#include <vector>

// First idea: use two arr to generate the fwd/bwd product result
class FirstSolution {
public:
  static std::vector<int> productExceptSelf(const std::vector<int>& nums) {
    if (nums.empty()) return {};
    if (nums.size()==1) return {0};
    std::vector<int> fwdProduct;
    fwdProduct.assign(nums.size(),1);
    std::vector<int> bwdProduct;
    bwdProduct.assign(nums.size(),1);
    fwdProduct[0] = 1;
    bwdProduct[bwdProduct.size()-1] = 1;
    for (int i=0;i<nums.size()-1;i++) {
      fwdProduct[i+1] = fwdProduct[i] * nums[i];
      const int back = nums.size()-i-1;
      bwdProduct[back-1] = bwdProduct[back] * nums[back];
    }
    std::vector<int> re;
    re.reserve(re.size());
    for (int i=0;i<nums.size();i++) {
      re.push_back(fwdProduct[i]*bwdProduct[i]);
    }
    return re;
  }
};

// #2 soluction, optimize the memory usage
// inplace memory usage, directly operate on the return array
class SecondSolution {
public:
  static std::vector<int> productExceptSelf(const std::vector<int>& nums) {
    if (nums.empty()) return {};
    if (nums.size()==1) return {0};
    std::vector<int> re;
    // init all elems as 1
    re.assign(nums.size(),1);
    int fwdMem = 1,bwdMem = 1,back = 0;
    for (int i=0;i<nums.size()-1;i++) {
      fwdMem *= nums[i];
      re[i+1] *= fwdMem;
      back = nums.size()-i-1;
      bwdMem *= nums[back];
      re[back-1]*=bwdMem;
    }
    return re;
  }
};


bool checkVec(const std::vector<int>& a,const std::vector<int>& b)
{
  if (a.size()!=b.size()) return false;
  for (int i=0;i<a.size();i++) {
    if (a[i]!=b[i]) return false;
  }
  return true;
}

int main(int argc, char* argv[])
{
  using Solution = SecondSolution;
  assert(checkVec(Solution::productExceptSelf({1,2,3,4}),{24,12,8,6}));
  assert(checkVec(Solution::productExceptSelf({-1,1,0,-3,3}),{0,0,9,0,0}));
}
