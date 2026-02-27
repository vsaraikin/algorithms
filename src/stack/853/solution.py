class Solution:
    # neetcode solution
    def carFleet(self, target: int, position: list[int], speed: list[int]) -> int: 
        stack = []
        for pos, sp in sorted(zip(position, speed),reverse = True):
            stack.append((target - pos) / sp)
            if len(stack) == 2 and stack[-1] <= stack[-2]:
                stack.pop()
            
        return len(stack)
    
    # gpt solution
    def carFleet(self, target: int, position: list[int], speed: list[int]) -> int: 
        cars = [(pos, (target - pos) / spd) for pos, spd in zip(position, speed)]
        cars.sort(reverse=True)
        current_time, fleets = 0, 0
        for pos, time in cars:
            if time > current_time:
                current_time = time
                fleets += 1
        return fleets

s = Solution()
assert s.carFleet(12, [10, 8, 0, 5, 3], [2, 4, 1, 1, 3])