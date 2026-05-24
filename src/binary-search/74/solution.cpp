#include <cassert>
#include <vector>

class Solution {
public:
	// bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
    //     for (const auto& row: matrix) {
    //         if (row.front() <= target && target <= row.back()) {
                
    //             int start = 0;
    //             int end = matrix[0].size() - 1;
                
    //             while (start <= end) {
    //                 int i = (end + start) / 2;
    //                 if (row[i] == target) {
    //                     return true;
    //                 } else if (row[i] > target) {
    //                     end = i - 1;
    //                 } else {
    //                     start = i + 1;
    //                 }
    //             }
    //         }
    //     }
    //     return false;
    // };

    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int l = 0, r = m * n - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            int val = matrix[mid / n][mid % n];
            if (val == target) return true;
            if (val < target) l = mid + 1;
            else r = mid - 1;
        }
        return false;
    }
};

int main() {
	Solution s;

	std::vector<std::vector<int>> input1 = {
		{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
	assert(s.searchMatrix(input1, 3) == true);
	assert(s.searchMatrix(input1, 13) == false);
	assert(s.searchMatrix(input1, 1) == true);
	assert(s.searchMatrix(input1, 60) == true);
	assert(s.searchMatrix(input1, 0) == false);
	assert(s.searchMatrix(input1, 61) == false);

	std::vector<std::vector<int>> input2 = {{1}};
	assert(s.searchMatrix(input2, 1) == true);
	assert(s.searchMatrix(input2, 2) == false);

	std::vector<std::vector<int>> input3 = {{1, 3}};
	assert(s.searchMatrix(input3, 3) == true);
	assert(s.searchMatrix(input3, 2) == false);

	std::vector<std::vector<int>> input4 = {{1}, {3}, {5}};
	assert(s.searchMatrix(input4, 3) == true);
	assert(s.searchMatrix(input4, 4) == false);

	std::vector<std::vector<int>> input5 = {
		{-10, -5, 0, 5}, {7, 10, 13, 20}, {21, 22, 23, 24}};
	assert(s.searchMatrix(input5, -10) == true);
	assert(s.searchMatrix(input5, 24) == true);
	assert(s.searchMatrix(input5, 14) == false);

	return 0;
}
