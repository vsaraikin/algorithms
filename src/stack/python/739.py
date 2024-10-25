class Solution:
    def dailyTemperatures(self, temperatures: list[int]) -> list[int]:
        stack = []

        n = len(temperatures)
        results = [0] * n

        for i in range(n):
            while stack and temperatures[i] > stack[-1][0]:
                popped = stack.pop()[1]
                results[popped] = i - popped
            stack.append((temperatures[i], i))
            
        return results
                    
                    
        
s = Solution()
assert s.dailyTemperatures([73,74,75,71,69,72,76,73]) == [1,1,4,2,1,1,0,0]