class Solution(object):
    def pivotIndex(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        # 类动规 150ms
        length = len(nums)
        try:
            # 初始化数组
            lsum = [0] * length     #从左边算的sum
            rsum = [0] * length     #从右边算的sum
            # lsum的初始元素与rsum 最后一位元素初始化
            lsum[0] = nums[0]
            rsum[length - 1] = nums[length - 1]
            # 生成从左到右以及从右到左的数组
            for i in range(1, length):
                lsum[i] = lsum[i - 1] + nums[i]

            for i in range(length - 2, -1, -1):
                rsum[i] = rsum[i + 1] + nums[i]
            # 检查首端
            if (rsum[1] == 0):
                return 0
            # 检查中部
            for i in range(length):
                if lsum[i] == rsum[i]:
                    return i
            # 检查末端
            if (lsum[length - 2] == 0):
                return length - 1

        except:
            return -1

        return -1
