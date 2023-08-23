class Solution:
    def sortedSquares(self, nums: list[int]) -> list[int]:
        start = 0
        n = len(nums)
        end = n - 1
        idx = end
        arr = [0] * n
        
        while idx > -1 and end > -1:
            if abs(nums[start]) > abs(nums[end]):
                arr[idx] = nums[start] ** 2
                start += 1
            else:
                arr[idx] = nums[end] ** 2
                end -= 1
            idx -= 1
            
        return arr
        
s = Solution()
assert s.sortedSquares([-4,-1,0,3,10]) == [0,1,9,16,100]