import heapq
from collections import Counter, deque

class Solution:
    def leastInterval(self, tasks: list[str], n: int) -> int:
        if n == 0:
            return len(tasks)

        c = Counter(tasks)
        heap = [-f for f in c.values()]
        heapq.heapify(heap)
        
        times = 0
        queue = deque()
        
        while heap or queue:
            times += 1
            
            if heap:
                cnt = heapq.heappop(heap)
                cnt += 1
                if cnt != 0:
                    queue.append((times + n, cnt))
                
            if queue and queue[0][0] == times:
                _, cnt = queue.popleft()
                heapq.heappush(heap, cnt)
            
        return times

        
    
sol = Solution()
assert sol.leastInterval(["A","A","A","B","B","B"], 2) == 8
assert sol.leastInterval(["A","A","A","B","B","B"], 0) == 6
assert sol.leastInterval(["A","A","A","B","B","B","C","C"], 2) == 8
assert sol.leastInterval(["A","A","A","A"], 3) == 13
assert sol.leastInterval(["A","A","A","B","B","B","C","C","C","D"], 2) == 10
assert sol.leastInterval(["A","A","B","B","C","C"], 4) == 6