class Solution:
    def carFleet(self, target: int, position: list[int], speed: list[int]) -> int: 
        stack = []
        for pos, sp in sorted(zip(position, speed),reverse = True):

            dist = target - pos
            time = dist / sp 
            
            if not stack:
                stack.append(time)
            elif time > stack[-1]:
                stack.append(time)

        return len(stack)

s = Solution()
assert s.carFleet(12, [10, 8, 0, 5, 3], [2, 4, 1, 1, 3])