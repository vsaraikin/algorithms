#include <vector>
#include <queue>

class Solution {
public:
    int lastStoneWeight(std::vector<int>& stones) {
        std::priority_queue<int> q;  // max-heap, local so calls are independent
        for (int el: stones) {
            q.push(el);
        }

        while (q.size() >= 2) {
            int a = q.top();
            q.pop();
            int b = q.top();
            q.pop(); 

            int smashed = a - b;
            q.push(smashed);
        }

        return q.empty() ? 0 : q.top();
    }
};
