class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        char_mapping = {')': '(', ']': '[', '}': '{'}
        for char in s:
            if char in char_mapping:
                top_element = stack.pop() if stack else "хуй"
                if top_element != char_mapping[char]:
                    return False
            else:
                stack.append(char)
        return not stack
            
    
s = Solution()
assert s.isValid("(]") == False
assert s.isValid("([)]") == False