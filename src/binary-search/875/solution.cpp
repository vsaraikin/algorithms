#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

class Solution {
  public:
	int minEatingSpeed(std::vector<int>& piles, int h) {
		int l = 1;
		int r = *std::max_element(piles.begin(), piles.end());
		while (l < r) {
			int mid = l + (r - l) / 2;
			long long hours = 0;
			for (int p : piles) {
				hours += (long long)std::ceil((double)p / mid);
			}
			if (hours <= h) r = mid;
			else l = mid + 1;
		}
		return l;
	}
};

int main() {
	Solution s;

	std::vector<int> input1 = {3, 6, 7, 11};
	assert(s.minEatingSpeed(input1, 8) == 4);

	std::vector<int> input2 = {30, 11, 23, 4, 20};
	assert(s.minEatingSpeed(input2, 5) == 30);

	std::vector<int> input3 = {30, 11, 23, 4, 20};
	assert(s.minEatingSpeed(input3, 6) == 23);

	std::vector<int> input4 = {1};
	assert(s.minEatingSpeed(input4, 1) == 1);

	std::vector<int> input5 = {1000000000};
	assert(s.minEatingSpeed(input5, 2) == 500000000);

	std::vector<int> input6 = {312884470};
	assert(s.minEatingSpeed(input6, 968709470) == 1);

	std::vector<int> input7 = {1, 1, 1, 1};
	assert(s.minEatingSpeed(input7, 4) == 1);

	std::vector<int> input8 = {1, 1, 1, 1};
	assert(s.minEatingSpeed(input8, 5) == 1);

	std::vector<int> input9 = {5, 5, 5, 5};
	assert(s.minEatingSpeed(input9, 5) == 5);

	std::vector<int> input10 = {3, 6, 7, 11};
	assert(s.minEatingSpeed(input10, 4) == 11); // h == n → нужна max(piles)

	return 0;
}
