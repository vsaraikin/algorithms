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
assert 3 == s.coinChange([1,5,10], 12)
assert -1 ==  s.coinChange([2], 3)
assert 0 == s.coinChange([1], 0)

