#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
	std::unordered_map<int, std::vector<int>> preMap;
	std::unordered_set<int> visiting;

public:
	bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
		preMap.clear();
		visiting.clear();
		for (int i = 0; i < numCourses; i++) {
			preMap[i] = {};
		}
		for (const auto& prereq : prerequisites) {
			preMap[prereq[0]].push_back(prereq[1]);
		}

		for (int c = 0; c < numCourses; c++) {
			if (!dfs(c)) {
				return false;
			}
		}
		return true;
	}

	bool dfs(int crs) {
		if (visiting.count(crs)) {
			return false;  // цикл: курс уже в текущем пути
		}
		if (preMap[crs].empty()) {
			return true;  // нет пререквизитов или уже проверен (список очищен)
		}

		visiting.insert(crs);
		for (int pre : preMap[crs]) {
			if (!dfs(pre)) {
				return false;
			}
		}
		visiting.erase(crs);
		preMap[crs].clear();  // проверен -> «чёрный»: обнуляем зависимости
		return true;
	}
};

int main() {
	Solution s;

	// 1: цепочка 0->1->2, цикла нет
	{
		std::vector<std::vector<int>> pre{{1, 0}, {2, 1}};
		assert(s.canFinish(3, pre) == true);
	}
	// 2: взаимная зависимость -> цикл
	{
		std::vector<std::vector<int>> pre{{1, 0}, {0, 1}};
		assert(s.canFinish(2, pre) == false);
	}
	// 3: нет зависимостей
	{
		std::vector<std::vector<int>> pre{};
		assert(s.canFinish(3, pre) == true);
	}
	// 4: ромб, цикла нет
	{
		std::vector<std::vector<int>> pre{{1, 0}, {2, 0}, {3, 1}, {3, 2}};
		assert(s.canFinish(4, pre) == true);
	}
	// 5: цикл в глубине 1->2->3->1
	{
		std::vector<std::vector<int>> pre{{1, 0}, {2, 1}, {3, 2}, {1, 3}};
		assert(s.canFinish(4, pre) == false);
	}
	// 6: петля на себя 0->0 -> цикл
	{
		std::vector<std::vector<int>> pre{{0, 0}};
		assert(s.canFinish(1, pre) == false);
	}

	return 0;
}
