from collections import defaultdict
import heapq

class Twitter:

    def __init__(self):
        self.timestamp = 0
        self.tweets = defaultdict(list)     # userId -> list of (ts, tweetId)
        self.followees = defaultdict(set)   # userId -> set of users they follow

    def postTweet(self, userId: int, tweetId: int) -> None:
        # auto-follow yourself so your own tweets always show up
        self.followees[userId].add(userId)
        self.timestamp += 1
        self.tweets[userId].append((self.timestamp, tweetId))

    def getNewsFeed(self, userId: int) -> list[int]:
        if userId not in self.followees:
            return []

        heap = []
        for fid in self.followees[userId]: # push the most recent tweet from each followee
            tl = self.tweets[fid]
            if tl:
                idx = len(tl) - 1
                ts, tid = tl[idx]
                heapq.heappush(heap, (-ts, fid, idx))

        res = []
        while heap and len(res) < 10:
            _, fid, idx = heapq.heappop(heap)
            ts, tid = self.tweets[fid][idx]
            res.append(tid)
            if idx > 0: # if that user has an older tweet, push it next
                prev_ts, prev_tid = self.tweets[fid][idx - 1]
                heapq.heappush(heap, (-prev_ts, fid, idx - 1))
        return res

    def follow(self, followerId: int, followeeId: int) -> None:
        # auto-follow yourself
        self.followees[followerId].add(followerId)
        self.followees[followerId].add(followeeId)

    def unfollow(self, followerId: int, followeeId: int) -> None:
        # cannot unfollow yourself
        if followeeId != followerId:
            self.followees[followerId].discard(followeeId)
        



# obj = Twitter()
# obj.postTweet(userId,tweetId)
# param_2 = obj.getNewsFeed(userId)
# obj.follow(followerId,followeeId)
# obj.unfollow(followerId,followeeId)