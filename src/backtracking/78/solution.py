class Solution:
    def subsets(self, nums: list[int]) -> list[list[int]]:
        res = []
        subset = []
        
        def dfs(i: int):
            res.append(subset.copy())
            
            for j in range(i, len(nums)):
                subset.append(nums[j])
                dfs(j + 1)
                subset.pop()
                
        dfs(0)
        return res
        
        
out = Solution().subsets([1,2])
assert set(map(tuple, out)) == {
    (), (1,), (2,), (1,2)
}
print("Test passed!")