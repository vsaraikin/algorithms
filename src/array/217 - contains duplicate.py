class Solution:
    def containsDuplicate(self, nums: list[int]) -> bool:
        return len(set(nums)) != len(nums)   
        
        
s = Solution()
        
assert True == s.containsDuplicate([1,2,3,1])
assert False == s.containsDuplicate([1,2,3,4])
assert True == s.containsDuplicate([1,1,1,3,3,4,3,2,4,2])