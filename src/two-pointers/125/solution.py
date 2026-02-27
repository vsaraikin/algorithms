class Solution:
    def isPalindrome(self, s: str) -> bool:
        def helper(char: str):
            if char.isnumeric() or char.isalpha():
                return False
            return True
        
        s = s.lower()
        n = len(s)
        start = 0
        end = n - 1
        
        while start < end:
            if s[start] != s[end]:

                if helper(s[start]):
                    start += 1
                    continue
                
                if helper(s[end]):
                    end -= 1
                    continue
                
                return False
            else:
                start += 1
                end -= 1
            
        return True
        

s = Solution()
assert s.isPalindrome("A man, a plan, a canal: Panama") == True
assert s.isPalindrome("race a car") == False
assert s.isPalindrome("0P") == False