class Solution:
    def maxProduct(self, nums: list[int]) -> int:
        n = len(nums)
        if not nums:
            return 0
        elif n == 1:
            return nums[0]
        
        maxEnding = minEnding = nums[0]
        ans = nums[0]
        for i in range(1, n):
            x = nums[i]
            
            tmpMaxEnding = 
            tmpMinEnding = 
                
            maxEnding = max(maxEnding, maxEnding * x)
            minEnding = max(minEnding, minEnding * x)
            
            

            
            
            
            
            
       

s = Solution() 
assert s.maxProduct([2,3,-2, 4]) == 6
# assert s.maxProduct([-2, 3, -4]) == 24