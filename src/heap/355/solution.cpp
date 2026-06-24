#include <queue>
#include <vector>
#include <unordered_set>

class Twitter {
public:
    Twitter() {
        
    };
    
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({last_timestamp, tweetId});
        ++last_timestamp;
    }
    
    std::vector<int> getNewsFeed(int userId) {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> feed;

        std::vector<int> res;

        auto addTweets = [&](int userId) {
            for (auto tweet: tweets[userId]) {
                feed.push(tweet);
                if (feed.size() > limit) {
                    feed.pop();
                }
            }
        };

        addTweets(userId); // own tweets;
        for (int folId: followers[userId]) {
            addTweets(folId);    
        }

        while (!feed.empty()) {
            res.push_back(feed.top().second);
            feed.pop();
        }

        std::reverse(res.begin(), res.end());

        return res;
    }
    
    void follow(int followerId, int followeeId) {
        if (followerId == followeeId) {
            return;
        }
        followers[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        followers[followerId].erase(followeeId);
    }
private:
    int last_timestamp = 0;
    const int limit = 10;
    std::unordered_map<int, std::unordered_set<int>> followers;
    std::unordered_map<int, std::vector<std::pair<int, int>>> tweets; // key = user, value = [(tweetId, timestamp), ...]
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
