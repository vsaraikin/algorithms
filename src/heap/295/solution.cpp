class MedianFinder {
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {  
        left.push(num);
        right.push(left.top());
        left.pop();

        if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }
    }
    
    double findMedian() {
        if (left.size() > right.size()) {
            return left.top();
        }

        return (left.top() + right.top()) / 2.0;
    }
private:
    std::priority_queue<int, std::vector<int>> left; // max-heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> right; // min-heap
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */