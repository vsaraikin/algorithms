class Solution:
    def search(self, nums: list[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        while left <= right:
            mid = (right + left) // 2
            if nums[mid] == target:
                return mid
            
            if nums[left] <= nums[mid]: # left is sorted
                if nums[left] <= target < nums[mid]: # target is in the left half
                    right = mid - 1
                else:
                    left = mid + 1
            else: # right is sorted
                if nums[mid] < target <= nums[right]: # target is in the right half
                    left = mid + 1
                else:
                    right = mid - 1

        return -1
    
    
s = Solution()
assert s.search([4,5,6,7,0,1,2], 0) == 4
assert s.search([4,5,6,7,0,1,2], 3) == -1
assert s.search([1], 0) == -1
assert s.search([1,3], 3) == 1
