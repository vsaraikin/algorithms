class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        bracket_mapping = {')': '(', '}': '{', ']': '['}

        for char in s:
            if char in bracket_mapping:
                top_element = stack.pop() if stack else '#'
                if bracket_mapping[char] != top_element:
                    return False
            else:
                stack.append(char)

        return not stack
            
    
s = Solution()
assert s.isValid("(]") == False
assert s.isValid("([)]") == False