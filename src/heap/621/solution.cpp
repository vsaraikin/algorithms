class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        std::vector<int> freq(26, 0);
        std::priority_queue<int> pq;

        for (char t: tasks) {
            freq[t - 'A']++;
        }

        for (int t: freq) {
            if (t > 0) {
                pq.push(t);
            }
        }

        int time = 0;

        while (!pq.empty()) {
            std::vector<int> tmp;

            for (int i = 0; i < n + 1; ++i) {
                if (!pq.empty()) {
                    tmp.push_back(pq.top() - 1);
                    pq.pop();
                }
            }

            for (int c : tmp) {
                if (c > 0) {
                    pq.push(c);
                }
            }

            time += pq.empty() ? tmp.size() : n + 1;
        }
        return time;
    } 
};