#include <algorithm>
#include <cassert>
#include <functional>
#include <utility>
#include <vector>

class Solution {
  public:
	int carFleet(int target, std::vector<int>& position,
	             std::vector<int>& speed) {
		std::vector<std::pair<int, double>> cars;
		cars.reserve(position.size());

		for (int i = 0; i < (int)position.size(); ++i) {
			double t = (double)(target - position[i]) / speed[i];
			cars.emplace_back(position[i], t);
		}

		std::sort(cars.begin(), cars.end(), std::greater<>());
		int fleets = 0;
		double lastTime = 0;
		for (const auto& [pos, t] : cars) {
			if (t > lastTime) {
				fleets++;
				lastTime = t;
			}
		}
		return fleets;
	}
};

int main() {
	Solution s;

	std::vector<int> p1 = {10, 8, 0, 5, 3};
	std::vector<int> v1 = {2, 4, 1, 1, 3};
	assert(s.carFleet(12, p1, v1) == 3);

	std::vector<int> p2 = {3};
	std::vector<int> v2 = {3};
	assert(s.carFleet(10, p2, v2) == 1);

	std::vector<int> p3 = {0, 2, 4};
	std::vector<int> v3 = {4, 2, 1};
	assert(s.carFleet(100, p3, v3) == 1);

	std::vector<int> p4 = {6, 8};
	std::vector<int> v4 = {3, 2};
	assert(s.carFleet(10, p4, v4) == 2);

	std::vector<int> p5 = {0, 4, 2};
	std::vector<int> v5 = {2, 1, 3};
	assert(s.carFleet(6, p5, v5) == 2); // car at pos 0 arrives last, own fleet

	std::vector<int> p6 = {4, 1, 0, 7};
	std::vector<int> v6 = {2, 2, 1, 1};
	assert(s.carFleet(10, p6, v6) == 3);

	return 0;
}
