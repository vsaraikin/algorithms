from collections import defaultdict
import heapq

"""
from one point it can be solved with heap
but in fact solution with heap sucks
"""

class Twitter:

    def __init__(self):
        self.timestamp = 0
        self.tweets = defaultdict(list)
        self.folowees = defaultdict(set)
        

    def postTweet(self, userId: int, tweetId: int) -> None:
        self.folowees[userId].add(userId) # ensure we'll use our own posts
        self.timestamp += 1
        self.tweets[userId].append((self.timestamp, tweetId))
        

    def getNewsFeed(self, userId: int) -> list[int]:
        if userId and not self.folowees:
            return []

        heap = []
        
        for fid in self.folowees[userId]:
            tl = self.tweets[fid]
            if tl:
                idx = len(tl) - 1
                ts, tid = tl[idx]
                heapq.heappush(heap, (-ts, fid, idx))
            
        res = []
        while heap and len(res) < 10:
            _, fid, idx = heapq.heappop(heap)
            _, tid = self.tweets[fid][idx]
            res.append(tid)
            if idx > 0:
                prev_ts, prev_tid = self.tweets[fid][idx - 1]
                heapq.heappush(heap, (-prev_ts, fid, idx - 1))
        
        return res
        

    def follow(self, followerId: int, followeeId: int) -> None:
        self.folowees[followeeId].add(followerId)
        self.folowees[followerId].add(followeeId)
        

    def unfollow(self, followerId: int, followeeId: int) -> None:
        if followerId != followeeId:
            self.folowees[followerId].discard(followeeId)
        



# obj = Twitter()
# obj.postTweet(userId,tweetId)
# param_2 = obj.getNewsFeed(userId)
# obj.follow(followerId,followeeId)
# obj.unfollow(followerId,followeeId)