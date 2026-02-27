class Solution:
    def largestRectangleArea(self, heights: list[int]) -> int:
        stack = []
        max_area = 0
        for i, h in enumerate(heights):
            start = i
            while stack and stack[-1][1] > h:
                index, height = stack.pop()
                max_area = max(max_area, height * (i - index)) # 2
                start = index # 0
            stack.append((start, h))
        
        for i, h in stack:
            max_area = max(max_area, h * (len(heights) - i))
        
        return max_area
        
    
s = Solution()
assert s.largestRectangleArea([2,1,5,6,2,3]) == 10
assert s.largestRectangleArea([2,4]) == 4
assert s.largestRectangleArea([2,1,2]) == 3

               