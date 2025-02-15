class Solution:
    def findMin(self, elements: list[int]) -> int:
        left, right = 0, len(elements) - 1
        while left < right:
            mid = (right + left) // 2
            if elements[mid] > elements[right]:
                left = mid + 1
            else:
                right = mid
                
        return elements[left]
    
    
        
s = Solution()
assert s.findMin([3,4,5,1,2]) == 1
assert s.findMin([4,5,6,7,0,1,2]) == 0
assert s.findMin([11,13,15,17]) == 11
