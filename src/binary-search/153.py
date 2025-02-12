class Solution:
    def findMin(self, elements: list[int]) -> int:
        if len(elements) == 2:
            if abs(elements[1] - elements[0]) > 1:
                return min(elements[1], elements[0])
            else:
                return min(elements)
        
        elif len(elements) == 1:
            return elements[0]
        
        else:
            mid = len(elements) // 2
            left = elements[:mid]
            right = elements[mid:]
            
            return min(self.findMin(left), self.findMin(right))
    
    
        
s = Solution()
assert s.findMin([3,4,5,1,2]) == 1
assert s.findMin([4,5,6,7,0,1,2]) == 0
assert s.findMin([11,13,15,17]) == 11
