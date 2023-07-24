coins1 = [1,2,5]
coins2 = [2]
coins3 = [1]
coins4 = [186,419,83,408]


amount1 = 11
amount2 = 3
amount3 = 0
amount4 = 6249



class Solution:
    # def coinChange(self, coins: list[int], amount: int) -> int:
        # pairs = []
        
        # while True:
        #     if not coins:
        #         return -1
            
        #     s = sum(pairs)
        #     if s < amount:
        #         pairs.append(max(coins))
        #     elif s == amount:
        #         return len(pairs)
        #     else:
        #         coins.remove(max(coins))
        #         pairs.pop()
    
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
print(s.coinChange(coins1, amount1))
print(s.coinChange(coins2, amount2))
print(s.coinChange(coins3, amount3))
print(s.coinChange(coins4, amount4))

