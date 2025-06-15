#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>


using namespace std;


int knapsack(int W, vector<int>& wt, vector<int>& val) {
    int n = wt.size();
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            dp[i][w] = dp[i-1][w];

            if (w >= wt[i-1])
                dp[i][w] = max(dp[i][w], dp[i-1][w - wt[i-1]] + val[i-1]);
        }
    }
    return dp[n][W];
}

int main() {
    {
        vector<int> weights = {1, 3, 4, 5};
        vector<int> values  = {1, 4, 5, 7};
        int capacity = 7;
        int res = knapsack(capacity, weights, values);
        assert(res == 9);
    }
    {
        vector<int> weights = {2, 2, 3};
        vector<int> values  = {3, 7, 4};
        int capacity = 5;
        int res = knapsack(capacity, weights, values);
        assert(res == 11);
    }
    cout << "All tests passed!";
    return 0;
}