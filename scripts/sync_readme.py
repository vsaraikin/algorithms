"""Regenerate all topic READMEs from filesystem + metadata.

Run from repo root:
    python3 scripts/sync_readme.py

Each topic lives in src/<topic>/<problem_number>/{solution.py,solution.cpp}.
The script rewrites src/<topic>/README.md and src/README.md so the tables
and badges match the actual files on disk, sorted by difficulty.

Tables that are missing metadata for a problem get a warning printed and
the problem is rendered as "Unknown #<num>" so nothing is silently lost.
"""

from __future__ import annotations

import re
from collections import Counter
from dataclasses import dataclass
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
SRC = REPO_ROOT / "src"

DIFFICULTY_RANK = {"Easy": 0, "Medium": 1, "Hard": 2}
DIFFICULTY_COLOR = {"Easy": "brightgreen", "Medium": "yellow", "Hard": "red"}

TOPIC_ORDER = [
    "arrays-and-hashing",
    "two-pointers",
    "sliding-window",
    "stack",
    "binary-search",
    "linked-list",
    "trees",
    "tries",
    "heap",
    "backtracking",
    "graphs",
    "advanced-graphs",
    "dynamic-programming",
    "greedy",
    "intervals",
    "math-and-geometry",
    "bit-manipulation",
    "divide-and-conquer",
    "concurrency",
]

TOPIC_TITLE = {
    "arrays-and-hashing": "Arrays & Hashing",
    "two-pointers": "Two Pointers",
    "sliding-window": "Sliding Window",
    "stack": "Stack",
    "binary-search": "Binary Search",
    "linked-list": "Linked List",
    "trees": "Trees",
    "tries": "Tries",
    "heap": "Heap & Priority Queue",
    "backtracking": "Backtracking",
    "graphs": "Graphs",
    "advanced-graphs": "Advanced Graphs",
    "dynamic-programming": "Dynamic Programming",
    "greedy": "Greedy",
    "intervals": "Intervals",
    "math-and-geometry": "Math & Geometry",
    "bit-manipulation": "Bit Manipulation",
    "divide-and-conquer": "Divide & Conquer",
    "concurrency": "Concurrency",
}


@dataclass(frozen=True)
class Problem:
    title: str
    difficulty: str  # "Easy" | "Medium" | "Hard"
    slug: str        # leetcode slug; url = https://leetcode.com/problems/<slug>/


# Problem metadata keyed by (topic, leetcode_id).
# When you add a new problem folder, add a row here; the script prints a
# warning for any folder without a matching entry.
PROBLEMS: dict[tuple[str, int], Problem] = {
    # arrays-and-hashing
    ("arrays-and-hashing", 1):   Problem("Two Sum",                       "Easy",   "two-sum"),
    ("arrays-and-hashing", 36):  Problem("Valid Sudoku",                  "Medium", "valid-sudoku"),
    ("arrays-and-hashing", 49):  Problem("Group Anagrams",                "Medium", "group-anagrams"),
    ("arrays-and-hashing", 128): Problem("Longest Consecutive Sequence",  "Medium", "longest-consecutive-sequence"),
    ("arrays-and-hashing", 153): Problem("Find Minimum in Rotated Sorted Array", "Medium", "find-minimum-in-rotated-sorted-array"),
    ("arrays-and-hashing", 217): Problem("Contains Duplicate",            "Easy",   "contains-duplicate"),
    ("arrays-and-hashing", 238): Problem("Product of Array Except Self",  "Medium", "product-of-array-except-self"),
    ("arrays-and-hashing", 242): Problem("Valid Anagram",                 "Easy",   "valid-anagram"),
    ("arrays-and-hashing", 347): Problem("Top K Frequent Elements",       "Medium", "top-k-frequent-elements"),

    # two-pointers
    ("two-pointers", 11):  Problem("Container With Most Water",     "Medium", "container-with-most-water"),
    ("two-pointers", 15):  Problem("3Sum",                           "Medium", "3sum"),
    ("two-pointers", 42):  Problem("Trapping Rain Water",            "Hard",   "trapping-rain-water"),
    ("two-pointers", 125): Problem("Valid Palindrome",               "Easy",   "valid-palindrome"),
    ("two-pointers", 167): Problem("Two Sum II - Input Array Is Sorted", "Medium", "two-sum-ii-input-array-is-sorted"),
    ("two-pointers", 344): Problem("Reverse String",                 "Easy",   "reverse-string"),
    ("two-pointers", 977): Problem("Squares of a Sorted Array",      "Easy",   "squares-of-a-sorted-array"),

    # sliding-window
    ("sliding-window", 3):   Problem("Longest Substring Without Repeating Characters", "Medium", "longest-substring-without-repeating-characters"),
    ("sliding-window", 76):  Problem("Minimum Window Substring",              "Hard",   "minimum-window-substring"),
    ("sliding-window", 121): Problem("Best Time to Buy and Sell Stock",       "Easy",   "best-time-to-buy-and-sell-stock"),
    ("sliding-window", 209): Problem("Minimum Size Subarray Sum",             "Medium", "minimum-size-subarray-sum"),
    ("sliding-window", 239): Problem("Sliding Window Maximum",                "Hard",   "sliding-window-maximum"),
    ("sliding-window", 424): Problem("Longest Repeating Character Replacement", "Medium", "longest-repeating-character-replacement"),
    ("sliding-window", 567): Problem("Permutation in String",                 "Medium", "permutation-in-string"),

    # stack
    ("stack", 20):  Problem("Valid Parentheses",                   "Easy",   "valid-parentheses"),
    ("stack", 84):  Problem("Largest Rectangle in Histogram",      "Hard",   "largest-rectangle-in-histogram"),
    ("stack", 150): Problem("Evaluate Reverse Polish Notation",    "Medium", "evaluate-reverse-polish-notation"),
    ("stack", 155): Problem("Min Stack",                           "Medium", "min-stack"),
    ("stack", 739): Problem("Daily Temperatures",                  "Medium", "daily-temperatures"),
    ("stack", 853): Problem("Car Fleet",                           "Medium", "car-fleet"),

    # binary-search
    ("binary-search", 4):   Problem("Median of Two Sorted Arrays",         "Hard",   "median-of-two-sorted-arrays"),
    ("binary-search", 33):  Problem("Search in Rotated Sorted Array",      "Medium", "search-in-rotated-sorted-array"),
    ("binary-search", 74):  Problem("Search a 2D Matrix",                  "Medium", "search-a-2d-matrix"),
    ("binary-search", 153): Problem("Find Minimum in Rotated Sorted Array", "Medium", "find-minimum-in-rotated-sorted-array"),
    ("binary-search", 704): Problem("Binary Search",                       "Easy",   "binary-search"),
    ("binary-search", 875): Problem("Koko Eating Bananas",                 "Medium", "koko-eating-bananas"),
    ("binary-search", 981): Problem("Time Based Key-Value Store",          "Medium", "time-based-key-value-store"),

    # linked-list
    ("linked-list", 2):   Problem("Add Two Numbers",                "Medium", "add-two-numbers"),
    ("linked-list", 19):  Problem("Remove Nth Node From End of List", "Medium", "remove-nth-node-from-end-of-list"),
    ("linked-list", 21):  Problem("Merge Two Sorted Lists",         "Easy",   "merge-two-sorted-lists"),
    ("linked-list", 23):  Problem("Merge k Sorted Lists",           "Hard",   "merge-k-sorted-lists"),
    ("linked-list", 25):  Problem("Reverse Nodes in k-Group",       "Hard",   "reverse-nodes-in-k-group"),
    ("linked-list", 138): Problem("Copy List with Random Pointer",  "Medium", "copy-list-with-random-pointer"),
    ("linked-list", 141): Problem("Linked List Cycle",              "Easy",   "linked-list-cycle"),
    ("linked-list", 143): Problem("Reorder List",                   "Medium", "reorder-list"),
    ("linked-list", 146): Problem("LRU Cache",                      "Medium", "lru-cache"),
    ("linked-list", 206): Problem("Reverse Linked List",            "Easy",   "reverse-linked-list"),
    ("linked-list", 287): Problem("Find the Duplicate Number",      "Medium", "find-the-duplicate-number"),

    # trees
    ("trees", 98):   Problem("Validate Binary Search Tree",         "Medium", "validate-binary-search-tree"),
    ("trees", 100):  Problem("Same Tree",                            "Easy",   "same-tree"),
    ("trees", 102):  Problem("Binary Tree Level Order Traversal",    "Medium", "binary-tree-level-order-traversal"),
    ("trees", 104):  Problem("Maximum Depth of Binary Tree",         "Easy",   "maximum-depth-of-binary-tree"),
    ("trees", 110):  Problem("Balanced Binary Tree",                 "Easy",   "balanced-binary-tree"),
    ("trees", 124):  Problem("Binary Tree Maximum Path Sum",         "Hard",   "binary-tree-maximum-path-sum"),
    ("trees", 199):  Problem("Binary Tree Right Side View",          "Medium", "binary-tree-right-side-view"),
    ("trees", 226):  Problem("Invert Binary Tree",                   "Easy",   "invert-binary-tree"),
    ("trees", 230):  Problem("Kth Smallest Element in a BST",        "Medium", "kth-smallest-element-in-a-bst"),
    ("trees", 235):  Problem("Lowest Common Ancestor of a Binary Search Tree", "Medium", "lowest-common-ancestor-of-a-binary-search-tree"),
    ("trees", 543):  Problem("Diameter of Binary Tree",              "Easy",   "diameter-of-binary-tree"),
    ("trees", 572):  Problem("Subtree of Another Tree",              "Easy",   "subtree-of-another-tree"),
    ("trees", 1448): Problem("Count Good Nodes in Binary Tree",      "Medium", "count-good-nodes-in-binary-tree"),

    # tries
    ("tries", 208): Problem("Implement Trie (Prefix Tree)",           "Medium", "implement-trie-prefix-tree"),
    ("tries", 211): Problem("Design Add and Search Words Data Structure", "Medium", "design-add-and-search-words-data-structure"),

    # heap
    ("heap", 355):  Problem("Design Twitter",                  "Medium", "design-twitter"),
    ("heap", 621):  Problem("Task Scheduler",                  "Medium", "task-scheduler"),
    ("heap", 703):  Problem("Kth Largest Element in a Stream", "Easy",   "kth-largest-element-in-a-stream"),
    ("heap", 973):  Problem("K Closest Points to Origin",      "Medium", "k-closest-points-to-origin"),
    ("heap", 1046): Problem("Last Stone Weight",               "Easy",   "last-stone-weight"),

    # backtracking
    ("backtracking", 22): Problem("Generate Parentheses", "Medium", "generate-parentheses"),
    ("backtracking", 39): Problem("Combination Sum",      "Medium", "combination-sum"),
    ("backtracking", 78): Problem("Subsets",              "Medium", "subsets"),

    # graphs
    ("graphs", 130): Problem("Surrounded Regions",          "Medium", "surrounded-regions"),
    ("graphs", 133): Problem("Clone Graph",                 "Medium", "clone-graph"),
    ("graphs", 207): Problem("Course Schedule",             "Medium", "course-schedule"),
    ("graphs", 417): Problem("Pacific Atlantic Water Flow", "Medium", "pacific-atlantic-water-flow"),

    # dynamic-programming
    ("dynamic-programming", 5):    Problem("Longest Palindromic Substring", "Medium", "longest-palindromic-substring"),
    ("dynamic-programming", 70):   Problem("Climbing Stairs",                "Easy",   "climbing-stairs"),
    ("dynamic-programming", 91):   Problem("Decode Ways",                    "Medium", "decode-ways"),
    ("dynamic-programming", 139):  Problem("Word Break",                     "Medium", "word-break"),
    ("dynamic-programming", 152):  Problem("Maximum Product Subarray",       "Medium", "maximum-product-subarray"),
    ("dynamic-programming", 198):  Problem("House Robber",                   "Medium", "house-robber"),
    ("dynamic-programming", 213):  Problem("House Robber II",                "Medium", "house-robber-ii"),
    ("dynamic-programming", 300):  Problem("Longest Increasing Subsequence", "Medium", "longest-increasing-subsequence"),
    ("dynamic-programming", 322):  Problem("Coin Change",                    "Medium", "coin-change"),
    ("dynamic-programming", 377):  Problem("Combination Sum IV",             "Medium", "combination-sum-iv"),
    ("dynamic-programming", 416):  Problem("Partition Equal Subset Sum",     "Medium", "partition-equal-subset-sum"),
    ("dynamic-programming", 647):  Problem("Palindromic Substrings",         "Medium", "palindromic-substrings"),
    ("dynamic-programming", 746):  Problem("Min Cost Climbing Stairs",       "Easy",   "min-cost-climbing-stairs"),
    ("dynamic-programming", 1143): Problem("Longest Common Subsequence",     "Medium", "longest-common-subsequence"),

    # bit-manipulation
    ("bit-manipulation", 338): Problem("Counting Bits", "Easy", "counting-bits"),

    # concurrency
    ("concurrency", 1114): Problem("Print in Order", "Easy", "print-in-order"),
}

# Short intro note rendered under the title. Empty string = no note.
TOPIC_NOTE = {
    "arrays-and-hashing": "Arrays store values of the same type at contiguous memory locations. Hashing gives average-O(1) lookup.",
    "two-pointers": "Maintain two indices that sweep the input to reduce an O(n²) scan to O(n).",
    "sliding-window": "A movable subrange over an array or string; expand/contract it to satisfy a constraint in O(n).",
    "stack": "LIFO structure — useful for matching, monotonic scans, and expression evaluation.",
    "binary-search": "Halve the search space each step — O(log n) over any sorted or monotonic predicate.",
    "linked-list": "Node-by-node traversal; common tricks: fast/slow pointers, dummy head, in-place reversal.",
    "trees": "Recursive hierarchical structure — most problems reduce to DFS, BFS, or BST invariants.",
    "tries": "Prefix tree — O(L) insert/lookup for strings over a fixed alphabet.",
    "heap": "Priority queue backed by a binary heap — O(log n) push/pop, O(1) peek of min or max.",
    "backtracking": "Explore candidates via DFS, undoing each choice on the way back up.",
    "graphs": "BFS, DFS, and Union-Find over explicit or implicit graphs.",
    "advanced-graphs": "Shortest paths, MST, topological sort, SCCs.",
    "dynamic-programming": "Solve a problem by combining answers to overlapping subproblems — top-down (memoization) or bottom-up (tabulation).",
    "greedy": "Commit to the locally optimal choice at each step; works when a greedy-choice property holds.",
    "intervals": "Sort by start or end and sweep — merge, insert, or count overlaps.",
    "math-and-geometry": "Number theory, modular arithmetic, and 2D geometry primitives.",
    "bit-manipulation": "Work directly on the bit representation — XOR tricks, bitmasks, popcount.",
    "divide-and-conquer": "Split into independent subproblems, solve each recursively, combine the results.",
    "concurrency": "Coordinate threads with mutexes, semaphores, or condition variables.",
}

# Extra free-form markdown appended after the table for a given topic.
# Keyed by topic; empty string = no extra section.
TOPIC_EXTRA: dict[str, str] = {
    "sliding-window": """## Template

```python
def sliding_window(s):
    left = 0
    result = []

    for right in range(len(s)):
        # expand window with s[right]

        while window_violates_constraint():
            # shrink window from the left
            left += 1

        # record answer for the current valid window

    return result
```
""",
    "graphs": """## Representations

```python
# Adjacency list (unweighted)
adj = {0: [1, 2], 1: [0, 2, 3], 2: [0, 1], 3: [1]}

# Adjacency list (weighted)
adj = {0: [(1, 2.5), (2, 1)], 1: [(0, 2.5), (2, 4), (3, 3)]}
```

## Traversals

```python
def bfs(graph, start):
    visited, queue = {start}, deque([start])
    while queue:
        node = queue.popleft()
        for nb in graph[node]:
            if nb not in visited:
                visited.add(nb)
                queue.append(nb)

def dfs(graph, node, visited):
    visited.add(node)
    for nb in graph[node]:
        if nb not in visited:
            dfs(graph, nb, visited)
```
""",
}


def find_problem_dirs(topic: str) -> list[int]:
    topic_dir = SRC / topic
    if not topic_dir.is_dir():
        return []
    out = []
    for child in topic_dir.iterdir():
        if child.is_dir() and child.name.isdigit():
            out.append(int(child.name))
    return sorted(out)


def language_cell(topic: str, num: int, filename: str, label: str) -> str:
    path = SRC / topic / str(num) / filename
    if path.exists():
        return f"[{label}](./{num}/{filename})"
    return "—"


def badge(label: str, message: str, color: str) -> str:
    def esc(s: str) -> str:
        return s.replace("-", "--").replace("_", "__").replace(" ", "_")
    url = f"https://img.shields.io/badge/{esc(label)}-{esc(message)}-{color}"
    return f"![{label}: {message}]({url})"


def progress_bar(done: int, total: int, width: int = 20) -> str:
    if total == 0:
        return "▱" * width + f" 0/0"
    filled = round(done * width / total)
    return "▰" * filled + "▱" * (width - filled) + f" {done}/{total}"


def sort_key(pair: tuple[int, Problem | None]) -> tuple[int, int]:
    num, prob = pair
    rank = DIFFICULTY_RANK.get(prob.difficulty, 99) if prob else 99
    return (rank, num)


def build_table(topic: str, problem_nums: list[int]) -> tuple[str, Counter, Counter]:
    """Return (markdown_table, difficulty_counter, language_counter)."""
    rows: list[tuple[int, Problem | None]] = []
    for num in problem_nums:
        rows.append((num, PROBLEMS.get((topic, num))))

    rows.sort(key=sort_key)

    lines = [
        "| # | Problem | Difficulty | Python | C++ |",
        "| --- | --- | --- | --- | --- |",
    ]
    difficulty_counter: Counter = Counter()
    language_counter: Counter = Counter()

    for num, prob in rows:
        py = language_cell(topic, num, "solution.py", "solution.py")
        cpp = language_cell(topic, num, "solution.cpp", "solution.cpp")
        if py != "—":
            language_counter["Python"] += 1
        if cpp != "—":
            language_counter["C++"] += 1

        if prob is None:
            print(f"[WARN] No metadata for ({topic}, {num}) — add it to PROBLEMS")
            title = f"Unknown #{num}"
            diff = "?"
            url = ""
        else:
            title = prob.title
            diff = prob.difficulty
            url = f"https://leetcode.com/problems/{prob.slug}/"
            difficulty_counter[diff] += 1

        title_cell = f"[{title}]({url})" if url else title
        lines.append(f"| {num} | {title_cell} | {diff} | {py} | {cpp} |")

    return "\n".join(lines), difficulty_counter, language_counter


def render_topic_header(topic: str, problem_nums: list[int]) -> str:
    total = len(problem_nums)
    diff_counts: Counter = Counter()
    lang_counts: Counter = Counter()
    for num in problem_nums:
        prob = PROBLEMS.get((topic, num))
        if prob:
            diff_counts[prob.difficulty] += 1
        if (SRC / topic / str(num) / "solution.py").exists():
            lang_counts["Python"] += 1
        if (SRC / topic / str(num) / "solution.cpp").exists():
            lang_counts["C++"] += 1

    badges = [badge("solved", str(total), "blue")]
    for diff in ("Easy", "Medium", "Hard"):
        if diff_counts[diff]:
            badges.append(badge(diff, str(diff_counts[diff]), DIFFICULTY_COLOR[diff]))
    if lang_counts["Python"]:
        badges.append(badge("Python", str(lang_counts["Python"]), "3776AB"))
    if lang_counts["C++"]:
        badges.append(badge("C%2B%2B", str(lang_counts["C++"]), "00599C"))

    return " ".join(badges)


def render_topic_readme(topic: str) -> str:
    problem_nums = find_problem_dirs(topic)
    title = TOPIC_TITLE.get(topic, topic.replace("-", " ").title())
    note = TOPIC_NOTE.get(topic, "")
    extra = TOPIC_EXTRA.get(topic, "")

    parts = [f"# {title}", ""]
    if problem_nums:
        parts.append(render_topic_header(topic, problem_nums))
        parts.append("")
    if note:
        parts.append(f"> {note}")
        parts.append("")

    if problem_nums:
        parts.append("## Problems")
        parts.append("")
        table, _, _ = build_table(topic, problem_nums)
        parts.append(table)
        parts.append("")
    else:
        parts.append("_No problems solved yet._")
        parts.append("")

    if extra:
        parts.append(extra)

    return "\n".join(parts).rstrip() + "\n"


def render_root_readme() -> str:
    total_problems = 0
    total_py = 0
    total_cpp = 0
    diff_totals: Counter = Counter()
    rows: list[tuple[str, int, int, int, int, int, int]] = []  # topic, total, E, M, H, py, cpp

    for topic in TOPIC_ORDER:
        nums = find_problem_dirs(topic)
        e = m = h = py = cpp = 0
        for n in nums:
            prob = PROBLEMS.get((topic, n))
            if prob:
                diff_totals[prob.difficulty] += 1
                if prob.difficulty == "Easy":
                    e += 1
                elif prob.difficulty == "Medium":
                    m += 1
                elif prob.difficulty == "Hard":
                    h += 1
            if (SRC / topic / str(n) / "solution.py").exists():
                py += 1
            if (SRC / topic / str(n) / "solution.cpp").exists():
                cpp += 1
        rows.append((topic, len(nums), e, m, h, py, cpp))
        total_problems += len(nums)
        total_py += py
        total_cpp += cpp

    neetcode_target = 150
    bar = progress_bar(total_problems, neetcode_target, width=30)

    badges = [
        badge("problems_solved", str(total_problems), "blue"),
        badge("Easy", str(diff_totals["Easy"]), DIFFICULTY_COLOR["Easy"]),
        badge("Medium", str(diff_totals["Medium"]), DIFFICULTY_COLOR["Medium"]),
        badge("Hard", str(diff_totals["Hard"]), DIFFICULTY_COLOR["Hard"]),
        badge("Python", str(total_py), "3776AB"),
        badge("C%2B%2B", str(total_cpp), "00599C"),
    ]

    lines = [
        "# Algorithms & Data Structures",
        "",
        " ".join(badges),
        "",
        "> Solutions to LeetCode problems, grouped by topic — mostly following [NeetCode 150](https://neetcode.io/practice) and [Blind 75](https://www.teamblind.com/post/New-Year-Gift---Curated-List-of-Top-75-LeetCode-Questions-to-Save-Your-Time-OaM1orEU).",
        "",
        "## Progress",
        "",
        f"```\nNeetCode 150: {bar}\n```",
        "",
        "## Topics",
        "",
        "| Topic | Solved | Easy | Medium | Hard | Python | C++ |",
        "| --- | --- | --- | --- | --- | --- | --- |",
    ]
    for topic, total, e, m, h, py, cpp in rows:
        title = TOPIC_TITLE.get(topic, topic)
        e_c = e or "—"
        m_c = m or "—"
        h_c = h or "—"
        py_c = py or "—"
        cpp_c = cpp or "—"
        total_c = total or "—"
        lines.append(
            f"| [{title}](./{topic}/README.md) | {total_c} | {e_c} | {m_c} | {h_c} | {py_c} | {cpp_c} |"
        )

    lines += [
        "",
        "## Approach",
        "",
        "1. Try to solve the problem alone for 20 minutes.",
        "2. If stuck, read a hint; give it another 10 minutes.",
        "3. If still stuck, study the solution — then resolve from scratch the next day.",
        "",
        "## Layout",
        "",
        "```",
        "src/<topic>/<leetcode_id>/",
        "    solution.py",
        "    solution.cpp  # optional",
        "```",
        "",
        "Run `python3 scripts/sync_readme.py` after adding a new problem to refresh tables and badges.",
        "",
    ]
    return "\n".join(lines)


def main() -> None:
    written = 0
    for topic in TOPIC_ORDER:
        topic_dir = SRC / topic
        if not topic_dir.exists():
            print(f"[SKIP] {topic} (directory missing)")
            continue
        readme = render_topic_readme(topic)
        (topic_dir / "README.md").write_text(readme)
        written += 1

    (SRC / "README.md").write_text(render_root_readme())
    print(f"Wrote {written} topic READMEs + root README.")


if __name__ == "__main__":
    main()
