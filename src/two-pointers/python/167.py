class Solution:
    
    def binary_search(self, target: int, arr: list[int]):
        start = 0
        end = len(arr) - 1
        while start <= end:
            mid = (start + end) // 2
            if arr[mid] == target:
                return True, mid
            elif arr[mid] < target:
                start = mid + 1
            else:
                end = mid - 1
        return False, None
    
    def twoSum(self, numbers: list[int], target: int) -> list[int]:
        """Binary search solution"""
        n = len(numbers)
        for i in range(n):
            complement = target - numbers[i]
            res, idx = self.binary_search(complement, numbers[i+1:])
            if res:
                return [i + 1, i + 2 + idx]
            
    def twoSum(self, numbers: list[int], target: int) -> list[int]:
        """Two pointers solution"""
        n = len(numbers)
        
        start = 0
        end = n-1
        
        while start < end:
            curr = numbers[start] + numbers[end]
            
            if curr == target:
                return [start + 1, end + 1]
            elif curr > target:
                end -= 1
            else:
                start += 1
        
        return []
 

                
                
    
        
    
s = Solution()
assert s.twoSum([2,7,11,15], 9) == [1, 2]
assert s.twoSum([2,3,4], 6) == [1, 3]
assert s.twoSum([-1, 0], -1) == [1, 2]
assert s.twoSum([0,0,3,4], 0) == [1, 2]
assert s.twoSum([5,25,75], 100) == [2, 3]
assert s.twoSum([3,24,50,79,88,150,345], 200) == [3, 6]