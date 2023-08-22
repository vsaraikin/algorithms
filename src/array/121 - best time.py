prices = [7,1,5,3,6,4]
prices2 = [7,6,4,3,1]

class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        profit = 0
        last_min = prices[0]
        for i in range(1, len(prices)):
            if prices[i-1] < last_min:
                last_min = prices[i-1]
                
            if prices[i] - last_min > profit:
                profit = prices[i] - last_min
                
        return int(profit)
    
s = Solution()
print(s.maxProfit(prices))
print(s.maxProfit(prices2))
