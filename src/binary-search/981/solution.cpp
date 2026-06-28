#include <cassert>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class TimeMap {
  public:
	TimeMap() {}

	void set(std::string key, std::string value, int timestamp) {
		storage[key].push_back({timestamp, value});
	}

	std::string get(std::string key, int timestamp) {
		auto it = storage.find(key);
		if (storage.end() == it) {
			return "";
		}
		const auto& v = it->second;
		int l = 0;
		int r = (int)v.size() - 1;
		int ans = -1;
		while (l <= r) {
			int mid = l + (r - l) / 2;
			if (v[mid].first <= timestamp) {
				ans = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		return ans == -1 ? "" : v[ans].second;
	}

  private:
	std::unordered_map<std::string, std::vector<std::pair<int, std::string>>>
		storage;
};


int main() {
	TimeMap tm;
	tm.set("foo", "bar", 1);
	assert(tm.get("foo", 1) == "bar");
	assert(tm.get("foo", 3) == "bar");
	tm.set("foo", "bar2", 4);
	assert(tm.get("foo", 4) == "bar2");
	assert(tm.get("foo", 5) == "bar2");
	assert(tm.get("foo", 3) == "bar");
	assert(tm.get("foo", 0) == "");

	TimeMap tm2;
	tm2.set("a", "x1", 5);
	tm2.set("a", "x2", 10);
	tm2.set("a", "x3", 15);
	assert(tm2.get("a", 5) == "x1");
	assert(tm2.get("a", 9) == "x1");
	assert(tm2.get("a", 10) == "x2");
	assert(tm2.get("a", 14) == "x2");
	assert(tm2.get("a", 15) == "x3");
	assert(tm2.get("a", 100) == "x3");
	assert(tm2.get("a", 4) == "");

	TimeMap tm3;
	assert(tm3.get("nope", 1) == "");

	TimeMap tm4;
	tm4.set("k", "v1", 1);
	tm4.set("k", "v2", 2);
	tm4.set("k", "v3", 3);
	assert(tm4.get("k", 2) == "v2");
	assert(tm4.get("k", 3) == "v3");
	assert(tm4.get("missing", 5) == "");

	return 0;
}
