class Solution:
    def maxArea(self, height: list[int]) -> int:
        n = len(height)
        start = 0
        end = n - 1
        
        vol = 0
        while start < end:
            vol = max(min(height[start], height[end]) * (end - start), vol)
            if height[start] > height[end]:
                end -= 1
            else:
                start += 1
        
        return vol
        
s = Solution()
assert s.maxArea([1,8,6,2,5,4,8,3,7]) == 49
assert s.maxArea([1, 1]) == 1
