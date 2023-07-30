# https://leetcode.com/problems/decode-ways/description/

# note: we can compare strings if they are the same positions
# we also can compare 1s and 10s

class Solution:
    def numDecodings(self, s: str) -> int:
        if not s or s[0] == '0':
            return 0

        dp = [0] * (len(s) + 1) # dp[i] means the number of ways to decode string s[:i]
        dp[0] = dp[1] = 1

        for i in range(2, len(s) + 1):
            if s[i - 1] != '0':
                dp[i] += dp[i - 1]
            if s[i - 2:i] >= '10' and s[i - 2:i] <= '26':
                dp[i] += dp[i - 2]

        return dp[-1]
        

s = Solution()
assert s.numDecodings("12") == 2
assert s.numDecodings("226") == 3
assert s.numDecodings("06") == 0
assert s.numDecodings("1") == 1
assert s.numDecodings("10") == 1
assert s.numDecodings("27") == 1
