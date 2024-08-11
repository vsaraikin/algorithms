class Solution:
    def search(self, nums: list[int], target: int) -> int:
        start = 0
        end = len(nums) - 1

        while start <= end:
            mid = (end + start) // 2
            
            if nums[mid] < target:
                start = mid + 1
            elif nums[mid] == target:
                return mid
            else:
                end = mid - 1

        return -1


s = Solution() 
assert s.search([-1,0,3,5,9,12], 9) == 4