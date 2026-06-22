#include <vector>

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        for (const int& el: nums) {
            q.push(el);
            if (q.size() > k) {
                q.pop();
            }
        }

        return q.top();
    };
private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
};