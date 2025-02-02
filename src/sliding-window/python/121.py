class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        profit = 0
        buy_price = prices[0]
        for i in range(1, len(prices)):
            if prices[i] < buy_price:
                buy_price = prices[i]
            else:
                if profit < prices[i] - buy_price:
                    profit = prices[i] - buy_price

        
        return profit
        
    
s = Solution()
assert 5 == s.maxProfit([7,1,5,3,6,4])
assert 0 == s.maxProfit([7,6,4,3,1])
