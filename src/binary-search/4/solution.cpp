#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <utility>
#include <vector>

class Solution {
  public:
	double findMedianSortedArrays(std::vector<int> &nums1,
								  std::vector<int> &nums2) {
		// left must be smaller
		if (nums1.size() > nums2.size()) {
			std::swap(nums1, nums2);
		}
		int m = nums1.size();
		int n = nums2.size();
		int total = m + n;
		int half = (total + 1) / 2; // left half

		int lo = 0, hi = m;
		while (lo <= hi) {
			int i = (lo + hi) / 2;
			int j = half - i;

			int L1 = (i == 0) ? INT_MIN: nums1[i-1];
			int R1 = (i == m) ? INT_MAX: nums1[i];
			int L2 = (j == 0) ? INT_MIN: nums2[j-1];
			int R2 = (j == n) ? INT_MAX: nums2[j];

			if (L1 <= R2 && L2 <= R1) {
				if (total % 2 == 1) {
					return std::max(L1, L2);
				}
				return (std::max(L1, L2) + std::min(R1, R2)) / 2.0;
			}
			if (L1 > R2) {
				hi = i - 1;
			}
			else {
				lo = i + 1;
			}

		}
		return 0.0;

	}

	// double findMedianSortedArrays(std::vector<int>& nums1,
	//                               std::vector<int>& nums2) {

	//     std::vector<int> merged;
	//     merged.reserve(nums1.size() + nums2.size());

	//     int i = 0;
	//     int j = 0;
	//     while (i < nums1.size() && j < nums2.size()) {
	//         if (nums1[i] > nums2[j]) {
	//             merged.emplace_back(nums2[j]);
	//             j++;
	//         } else if (nums1[i] == nums2[j]) {
	//             merged.emplace_back(nums2[j]);
	//             merged.emplace_back(nums1[i]);
	//             i++;
	//             j++;
	//         } else {
	//             merged.emplace_back(nums1[i]);
	//             i++;
	//         }
	//     }

	//     while (i < nums1.size()) {
	//         merged.emplace_back(nums1[i]);
	//         i++;
	//     }

	//     while (j < nums2.size()) {
	//         merged.emplace_back(nums2[j]);
	//         j++;
	//     }

	//     int l = 0;
	//     int r = merged.size() - 1;
	//     int mid = (l + r) / 2;
	//     double res;
	//     if (merged.size() % 2 == 0) {
	//         res = (double)(merged[mid] + merged[mid + 1]) / 2;
	//     } else {
	//         res = merged[mid];
	//     }
	//     return res;
	// }
};

int main() {
	Solution s;

	std::vector<int> a1 = {1, 3};
	std::vector<int> b1 = {2};
	assert(s.findMedianSortedArrays(a1, b1) == 2.0);

	std::vector<int> a2 = {1, 2};
	std::vector<int> b2 = {3, 4};
	assert(s.findMedianSortedArrays(a2, b2) == 2.5);

	std::vector<int> a3 = {0, 0};
	std::vector<int> b3 = {0, 0};
	assert(s.findMedianSortedArrays(a3, b3) == 0.0);

	std::vector<int> a4 = {};
	std::vector<int> b4 = {1};
	assert(s.findMedianSortedArrays(a4, b4) == 1.0);

	std::vector<int> a5 = {2};
	std::vector<int> b5 = {};
	assert(s.findMedianSortedArrays(a5, b5) == 2.0);

	std::vector<int> a6 = {1, 3};
	std::vector<int> b6 = {2, 7};
	assert(s.findMedianSortedArrays(a6, b6) == 2.5);

	std::vector<int> a7 = {1, 2, 3, 4, 5};
	std::vector<int> b7 = {6, 7, 8, 9, 10};
	assert(s.findMedianSortedArrays(a7, b7) == 5.5);

	std::vector<int> a8 = {1, 2};
	std::vector<int> b8 = {-1, 3};
	assert(s.findMedianSortedArrays(a8, b8) == 1.5);

	std::vector<int> a9 = {1, 5, 9};
	std::vector<int> b9 = {2, 3, 4, 6, 7, 8};
	assert(s.findMedianSortedArrays(a9, b9) == 5.0);

	std::vector<int> a10 = {3};
	std::vector<int> b10 = {-2, -1};
	assert(s.findMedianSortedArrays(a10, b10) == -1.0);

	return 0;
}
