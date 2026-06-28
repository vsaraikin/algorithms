class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        std::priority_queue<pair<int, std::vector<int>>> pq;
        std::vector<std::vector<int>> res;
        for (auto point: points) {
            int p = proximity(point[0], point[1]);
            pq.push({p, point});
            if (pq.size() > k) {
                pq.pop();;
            }
        }

        while (!pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
        }

        return res;
    }

    int proximity(int x, int y) {
        return x * x + y * y;
    }
};