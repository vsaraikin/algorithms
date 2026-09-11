#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <queue>

class Solution {
public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
		std::queue<std::string> q;
		std::unordered_set<std::string> visited;
		std::unordered_map<std::string, std::vector<std::string>> neighbours;

		for (const auto& word: wordList) {
			for (int j = 0; j < word.size(); ++j) {
				std::string pattern = word.substr(0, j) + '*' + word.substr(j + 1);
				neighbours[pattern].push_back(word);
			}
		}
		
		int res = 1;
		q.push(beginWord);
		visited.insert(beginWord);
		while (!q.empty()) {
			size_t sz = q.size();
			for (int k = 0; k < sz; ++k) {
				
				const std::string word = q.front();
				q.pop();
				for (int j = 0; j < word.size(); ++j) {
					std::string pattern = word.substr(0, j) + '*' + word.substr(j + 1);
					for (const auto& nei: neighbours[pattern]) {
						if (nei == endWord) {
							return res + 1;
						}
						if (!visited.count(nei)) {
							q.push(nei);
							visited.insert(nei);
						}
					}
				}
			}

			++res;
		}
		return 0;
    }
};