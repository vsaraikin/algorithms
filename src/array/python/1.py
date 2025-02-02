l = [2, 7, 11, 15]
l2 = [3, 2, 4]
l3 = [3, 3]

class Solution:
    def twoSum(self, nums, target):
        for i in range(0, len(nums)):
            for j in range(i + 1, len(nums)):
                if nums[i] + nums[j] == target:
                    return i, j
                

s = Solution()
print(s.twoSum(l, 9))
print(s.twoSum(l2, 6))
print(s.twoSum(l3, 6))
