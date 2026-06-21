#include <vector>
#include <queue>

class KthLargest {
public:
    KthLargest(int k, std::vector<int>& nums) {
        this->k = k;
        for (int el: nums) {
            v.push(el);
            if (v.size() > k) {
                v.pop();
            }
        }
    }
    
    int add(int val) {
        v.push(val);
        if (v.size() > k) {
            v.pop();
        }
        return v.top();
    }

private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> v;
    int k;
};
