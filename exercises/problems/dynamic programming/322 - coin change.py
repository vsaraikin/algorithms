coins1 = [1,2,5]
coins2 = [2]
coins3 = [1]

amount1 = 11
amount2 = 3
amount3 = 0

class Solution:
    def coinChange(self, coins: list[int], amount: int) -> int:
        arr = [amount + 1] * (amount + 1)
        arr[0] = 0

        for i in range(1, amount + 1):
            for coin in coins:
                if coin <= i:
                    arr[i] = min(arr[i], arr[i - coin] + 1)
        
        if arr[amount] > amount:
            return -1 
        else:
            return arr[amount]    
        
s = Solution()
assert 3 == s.coinChange(coins1, amount1)
assert -1 ==  s.coinChange(coins2, amount2)
assert 0 == s.coinChange(coins3, amount3)

