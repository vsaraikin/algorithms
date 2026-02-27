class Solution:
    # Recursion Solution
    def generateParenthesis(self, n: int) -> list[str]:
        def helper(curr_str, left, right):
            if 2 * n == len(curr_str):
                l.append(curr_str)
                return
            if left < n:
                helper(curr_str + '(', left + 1, right)
            if right < left:
                helper(curr_str + ')', left, right + 1)
                
        l = []
        helper("", 0, 0)
        return l
        
        
        
s = Solution()
assert s.generateParenthesis(3) == ["((()))","(()())","(())()","()(())","()()()"]