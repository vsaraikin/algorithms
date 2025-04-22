class Solution:
    def findMedianSortedArrays(self, nums1: list[int], nums2: list[int]) -> float:
        def binary_search(nums: list) -> float:
            l = len(nums)
            if l == 1:
                return nums[0]
            elif not nums1 and nums2:
                return 
            elif l % 2 == 1:
                return nums[l // 2 + 1]
            else:
                mid_left, mid_right = l // 2 - 1, l // 2
                return (nums[mid_left] + nums[mid_right]) / 2
        
            
        v1, v2 = binary_search(nums1), binary_search(nums2)
        return (v1 + v2) / 2
            

s = Solution() 
assert s.findMedianSortedArrays([1,3], [2]) == 2.0
assert s.findMedianSortedArrays([1,2], [3,4]) == 2.5
assert s.findMedianSortedArrays([1], []) == 1
