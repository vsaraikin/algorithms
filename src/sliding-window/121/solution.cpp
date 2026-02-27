#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max_profit = 0, last_min = 0;
        last_min = prices[0];
        for (int right = 1; right < prices.size(); right++) {
            if (prices[right-1] < last_min) {
                last_min = prices[right-1];
            }
            if (prices[right] - last_min > max_profit) {
                max_profit = prices[right] - last_min;
            }

        }
        return max_profit;
    }
};

int main(){
    Solution solution;

    vector<int> prices1 = {7,1,5,3,6,4};
    int expected1 = 5;
    assert(solution.maxProfit(prices1) == expected1);

    vector<int> prices2 = {7,6,4,3,1};
    int expected2 = 0;
    assert(solution.maxProfit(prices2) == expected2);


    vector<int> prices4 = {5};
    int expected4 = 0;
    assert(solution.maxProfit(prices4) == expected4);

    vector<int> prices5 = {3,3,3,3,3};
    int expected5 = 0;
    assert(solution.maxProfit(prices5) == expected5);

    vector<int> prices6 = {10,9,8,7,6,5,4,3,2,1};
    int expected6 = 0;
    assert(solution.maxProfit(prices6) == expected6);

    vector<int> prices7 = {2,4,1};
    int expected7 = 2;
    assert(solution.maxProfit(prices7) == expected7);

    vector<int> prices8 = {1,2};
    int expected8 = 1;
    assert(solution.maxProfit(prices8) == expected8);

    vector<int> prices9 = {1,100};
    int expected9 = 99;
    assert(solution.maxProfit(prices9) == expected9);

    vector<int> prices10 = {3,2,6,5,0,3};
    int expected10 = 4;
    assert(solution.maxProfit(prices10) == expected10);

    cout << "Все тесты пройдены успешно!\n";

    return 0;
}