nums = [1,2,3,4]
nums2 = [-1,1,0,-3,3]

class Solution:
    
    def productExceptSelf(self, elements: list[int]) -> list[int]:

        n = len(elements)

        left, right = [1]*n, [1]*n

        for i in range(1, n):
            left[i] = left[i-1] * elements[i-1]

        for i in range(n-2, -1, -1): # reversed(range(n-1))
            right[i] = right[i+1] * elements[i+1]

        for i in range(n):
            elements[i] = left[i] * right[i]

        return elements


s = Solution()
print(s.productExceptSelf(nums))