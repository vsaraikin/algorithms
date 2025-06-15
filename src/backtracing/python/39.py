class Solution:
    def combinationSum(self, candidates: list[int], target: int) -> list[list[int]]:
        ans = []
        
        def dfs(pos: int, target: int, path: list[int]):
            if target < 0:
                return
            
            if target == 0:
                ans.append(path.copy())
                return
                
            for i in range(pos, len(candidates)):
                path.append(candidates[i])
                dfs(i, target - candidates[i], path)
                path.pop()
        
        candidates.sort()
        dfs(0, target, [])
        return ans
            
        
s = Solution()
# print(s.combinationSum([2,3,6,7], 7))
assert s.combinationSum([2,3,6,7], 7) == [[2,2,3],[7]]
        