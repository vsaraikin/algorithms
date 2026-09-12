#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>


// tickets = [["MUC","LHR"], ["JFK","MUC"], ["SFO","SJC"], ["LHR","SFO"]]

class Solution {
public:
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets) {
		for (const auto& flight: tickets) {
			m[flight[0]].insert(flight[1]);
		}
		dfs("JFK");
		std::reverse(route.begin(), route.end());
		return route;
    }

	void dfs(const std::string& airport) {
		while (!m[airport].empty()) {
			auto it_closest = m[airport].begin();
			std::string next = *it_closest;
			m[airport].erase(it_closest);
			dfs(next);
		}
		route.push_back(airport);
	}
private:
    std::unordered_map<std::string, std::multiset<std::string>> m;
    std::vector<std::string> route;
};