"""Regenerate all topic READMEs from filesystem + metadata.

Run from repo root:
    python3 scripts/sync_readme.py

Each topic lives in src/<topic>/<problem_number>/{solution.py,solution.cpp}.
A problem folder with no solution file (just a .gitkeep) is treated as
"in scope but not solved yet" and rendered with em dashes for both
language cells.

The script rewrites src/<topic>/README.md and src/README.md so the tables
and badges match the actual files on disk, sorted by difficulty.
"""

from __future__ import annotations

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
# Covers the full NeetCode 150 plus a few extras already in the repo.
# When you add a new problem folder, add a row here too — the script
# warns for any folder without a matching entry.
PROBLEMS: dict[tuple[str, int], Problem] = {
    # ============================== Arrays & Hashing ==============================
    ("arrays-and-hashing", 1):   Problem("Two Sum",                              "Easy",   "two-sum"),
    ("arrays-and-hashing", 36):  Problem("Valid Sudoku",                         "Medium", "valid-sudoku"),
    ("arrays-and-hashing", 49):  Problem("Group Anagrams",                       "Medium", "group-anagrams"),
    ("arrays-and-hashing", 128): Problem("Longest Consecutive Sequence",         "Medium", "longest-consecutive-sequence"),
    ("arrays-and-hashing", 153): Problem("Find Minimum in Rotated Sorted Array", "Medium", "find-minimum-in-rotated-sorted-array"),
    ("arrays-and-hashing", 217): Problem("Contains Duplicate",                   "Easy",   "contains-duplicate"),
    ("arrays-and-hashing", 238): Problem("Product of Array Except Self",         "Medium", "product-of-array-except-self"),
    ("arrays-and-hashing", 242): Problem("Valid Anagram",                        "Easy",   "valid-anagram"),
    ("arrays-and-hashing", 271): Problem("Encode and Decode Strings",            "Medium", "encode-and-decode-strings"),
    ("arrays-and-hashing", 347): Problem("Top K Frequent Elements",              "Medium", "top-k-frequent-elements"),

    # ============================== Two Pointers ==============================
    ("two-pointers", 11):  Problem("Container With Most Water",          "Medium", "container-with-most-water"),
    ("two-pointers", 15):  Problem("3Sum",                                "Medium", "3sum"),
    ("two-pointers", 42):  Problem("Trapping Rain Water",                 "Hard",   "trapping-rain-water"),
    ("two-pointers", 125): Problem("Valid Palindrome",                    "Easy",   "valid-palindrome"),
    ("two-pointers", 167): Problem("Two Sum II - Input Array Is Sorted",  "Medium", "two-sum-ii-input-array-is-sorted"),
    ("two-pointers", 344): Problem("Reverse String",                      "Easy",   "reverse-string"),
    ("two-pointers", 977): Problem("Squares of a Sorted Array",           "Easy",   "squares-of-a-sorted-array"),

    # ============================== Sliding Window ==============================
    ("sliding-window", 3):   Problem("Longest Substring Without Repeating Characters", "Medium", "longest-substring-without-repeating-characters"),
    ("sliding-window", 76):  Problem("Minimum Window Substring",                "Hard",   "minimum-window-substring"),
    ("sliding-window", 121): Problem("Best Time to Buy and Sell Stock",         "Easy",   "best-time-to-buy-and-sell-stock"),
    ("sliding-window", 209): Problem("Minimum Size Subarray Sum",               "Medium", "minimum-size-subarray-sum"),
    ("sliding-window", 239): Problem("Sliding Window Maximum",                  "Hard",   "sliding-window-maximum"),
    ("sliding-window", 424): Problem("Longest Repeating Character Replacement", "Medium", "longest-repeating-character-replacement"),
    ("sliding-window", 567): Problem("Permutation in String",                   "Medium", "permutation-in-string"),

    # ============================== Stack ==============================
    ("stack", 20):  Problem("Valid Parentheses",                "Easy",   "valid-parentheses"),
    ("stack", 84):  Problem("Largest Rectangle in Histogram",   "Hard",   "largest-rectangle-in-histogram"),
    ("stack", 150): Problem("Evaluate Reverse Polish Notation", "Medium", "evaluate-reverse-polish-notation"),
    ("stack", 155): Problem("Min Stack",                        "Medium", "min-stack"),
    ("stack", 739): Problem("Daily Temperatures",               "Medium", "daily-temperatures"),
    ("stack", 853): Problem("Car Fleet",                        "Medium", "car-fleet"),

    # ============================== Binary Search ==============================
    ("binary-search", 4):   Problem("Median of Two Sorted Arrays",          "Hard",   "median-of-two-sorted-arrays"),
    ("binary-search", 33):  Problem("Search in Rotated Sorted Array",       "Medium", "search-in-rotated-sorted-array"),
    ("binary-search", 74):  Problem("Search a 2D Matrix",                   "Medium", "search-a-2d-matrix"),
    ("binary-search", 153): Problem("Find Minimum in Rotated Sorted Array", "Medium", "find-minimum-in-rotated-sorted-array"),
    ("binary-search", 704): Problem("Binary Search",                        "Easy",   "binary-search"),
    ("binary-search", 875): Problem("Koko Eating Bananas",                  "Medium", "koko-eating-bananas"),
    ("binary-search", 981): Problem("Time Based Key-Value Store",           "Medium", "time-based-key-value-store"),

    # ============================== Linked List ==============================
    ("linked-list", 2):   Problem("Add Two Numbers",                  "Medium", "add-two-numbers"),
    ("linked-list", 19):  Problem("Remove Nth Node From End of List", "Medium", "remove-nth-node-from-end-of-list"),
    ("linked-list", 21):  Problem("Merge Two Sorted Lists",           "Easy",   "merge-two-sorted-lists"),
    ("linked-list", 23):  Problem("Merge k Sorted Lists",             "Hard",   "merge-k-sorted-lists"),
    ("linked-list", 25):  Problem("Reverse Nodes in k-Group",         "Hard",   "reverse-nodes-in-k-group"),
    ("linked-list", 138): Problem("Copy List with Random Pointer",    "Medium", "copy-list-with-random-pointer"),
    ("linked-list", 141): Problem("Linked List Cycle",                "Easy",   "linked-list-cycle"),
    ("linked-list", 143): Problem("Reorder List",                     "Medium", "reorder-list"),
    ("linked-list", 146): Problem("LRU Cache",                        "Medium", "lru-cache"),
    ("linked-list", 206): Problem("Reverse Linked List",              "Easy",   "reverse-linked-list"),
    ("linked-list", 287): Problem("Find the Duplicate Number",        "Medium", "find-the-duplicate-number"),

    # ============================== Trees ==============================
    ("trees", 98):   Problem("Validate Binary Search Tree",                                "Medium", "validate-binary-search-tree"),
    ("trees", 100):  Problem("Same Tree",                                                  "Easy",   "same-tree"),
    ("trees", 102):  Problem("Binary Tree Level Order Traversal",                          "Medium", "binary-tree-level-order-traversal"),
    ("trees", 104):  Problem("Maximum Depth of Binary Tree",                               "Easy",   "maximum-depth-of-binary-tree"),
    ("trees", 105):  Problem("Construct Binary Tree from Preorder and Inorder Traversal", "Medium", "construct-binary-tree-from-preorder-and-inorder-traversal"),
    ("trees", 110):  Problem("Balanced Binary Tree",                                       "Easy",   "balanced-binary-tree"),
    ("trees", 124):  Problem("Binary Tree Maximum Path Sum",                               "Hard",   "binary-tree-maximum-path-sum"),
    ("trees", 199):  Problem("Binary Tree Right Side View",                                "Medium", "binary-tree-right-side-view"),
    ("trees", 226):  Problem("Invert Binary Tree",                                         "Easy",   "invert-binary-tree"),
    ("trees", 230):  Problem("Kth Smallest Element in a BST",                              "Medium", "kth-smallest-element-in-a-bst"),
    ("trees", 235):  Problem("Lowest Common Ancestor of a Binary Search Tree",             "Medium", "lowest-common-ancestor-of-a-binary-search-tree"),
    ("trees", 297):  Problem("Serialize and Deserialize Binary Tree",                      "Hard",   "serialize-and-deserialize-binary-tree"),
    ("trees", 543):  Problem("Diameter of Binary Tree",                                    "Easy",   "diameter-of-binary-tree"),
    ("trees", 572):  Problem("Subtree of Another Tree",                                    "Easy",   "subtree-of-another-tree"),
    ("trees", 1448): Problem("Count Good Nodes in Binary Tree",                            "Medium", "count-good-nodes-in-binary-tree"),

    # ============================== Tries ==============================
    ("tries", 208): Problem("Implement Trie (Prefix Tree)",               "Medium", "implement-trie-prefix-tree"),
    ("tries", 211): Problem("Design Add and Search Words Data Structure", "Medium", "design-add-and-search-words-data-structure"),
    ("tries", 212): Problem("Word Search II",                             "Hard",   "word-search-ii"),

    # ============================== Heap & Priority Queue ==============================
    ("heap", 215):  Problem("Kth Largest Element in an Array", "Medium", "kth-largest-element-in-an-array"),
    ("heap", 295):  Problem("Find Median from Data Stream",    "Hard",   "find-median-from-data-stream"),
    ("heap", 355):  Problem("Design Twitter",                  "Medium", "design-twitter"),
    ("heap", 621):  Problem("Task Scheduler",                  "Medium", "task-scheduler"),
    ("heap", 703):  Problem("Kth Largest Element in a Stream", "Easy",   "kth-largest-element-in-a-stream"),
    ("heap", 973):  Problem("K Closest Points to Origin",      "Medium", "k-closest-points-to-origin"),
    ("heap", 1046): Problem("Last Stone Weight",               "Easy",   "last-stone-weight"),

    # ============================== Backtracking ==============================
    ("backtracking", 17):  Problem("Letter Combinations of a Phone Number", "Medium", "letter-combinations-of-a-phone-number"),
    ("backtracking", 22):  Problem("Generate Parentheses",                  "Medium", "generate-parentheses"),
    ("backtracking", 39):  Problem("Combination Sum",                       "Medium", "combination-sum"),
    ("backtracking", 40):  Problem("Combination Sum II",                    "Medium", "combination-sum-ii"),
    ("backtracking", 46):  Problem("Permutations",                          "Medium", "permutations"),
    ("backtracking", 51):  Problem("N-Queens",                              "Hard",   "n-queens"),
    ("backtracking", 78):  Problem("Subsets",                               "Medium", "subsets"),
    ("backtracking", 79):  Problem("Word Search",                           "Medium", "word-search"),
    ("backtracking", 90):  Problem("Subsets II",                            "Medium", "subsets-ii"),
    ("backtracking", 131): Problem("Palindrome Partitioning",               "Medium", "palindrome-partitioning"),

    # ============================== Graphs ==============================
    ("graphs", 127): Problem("Word Ladder",                                              "Hard",   "word-ladder"),
    ("graphs", 130): Problem("Surrounded Regions",                                       "Medium", "surrounded-regions"),
    ("graphs", 133): Problem("Clone Graph",                                              "Medium", "clone-graph"),
    ("graphs", 200): Problem("Number of Islands",                                        "Medium", "number-of-islands"),
    ("graphs", 207): Problem("Course Schedule",                                          "Medium", "course-schedule"),
    ("graphs", 210): Problem("Course Schedule II",                                       "Medium", "course-schedule-ii"),
    ("graphs", 261): Problem("Graph Valid Tree",                                         "Medium", "graph-valid-tree"),
    ("graphs", 286): Problem("Walls and Gates",                                          "Medium", "walls-and-gates"),
    ("graphs", 323): Problem("Number of Connected Components in an Undirected Graph",    "Medium", "number-of-connected-components-in-an-undirected-graph"),
    ("graphs", 417): Problem("Pacific Atlantic Water Flow",                              "Medium", "pacific-atlantic-water-flow"),
    ("graphs", 684): Problem("Redundant Connection",                                     "Medium", "redundant-connection"),
    ("graphs", 695): Problem("Max Area of Island",                                       "Medium", "max-area-of-island"),
    ("graphs", 994): Problem("Rotting Oranges",                                          "Medium", "rotting-oranges"),

    # ============================== Advanced Graphs ==============================
    ("advanced-graphs", 269):  Problem("Alien Dictionary",                "Hard",   "alien-dictionary"),
    ("advanced-graphs", 332):  Problem("Reconstruct Itinerary",           "Hard",   "reconstruct-itinerary"),
    ("advanced-graphs", 743):  Problem("Network Delay Time",              "Medium", "network-delay-time"),
    ("advanced-graphs", 778):  Problem("Swim in Rising Water",            "Hard",   "swim-in-rising-water"),
    ("advanced-graphs", 787):  Problem("Cheapest Flights Within K Stops", "Medium", "cheapest-flights-within-k-stops"),
    ("advanced-graphs", 1584): Problem("Min Cost to Connect All Points",  "Medium", "min-cost-to-connect-all-points"),

    # ============================== Dynamic Programming ==============================
    ("dynamic-programming", 5):    Problem("Longest Palindromic Substring",                "Medium", "longest-palindromic-substring"),
    ("dynamic-programming", 10):   Problem("Regular Expression Matching",                  "Hard",   "regular-expression-matching"),
    ("dynamic-programming", 62):   Problem("Unique Paths",                                 "Medium", "unique-paths"),
    ("dynamic-programming", 70):   Problem("Climbing Stairs",                              "Easy",   "climbing-stairs"),
    ("dynamic-programming", 72):   Problem("Edit Distance",                                "Medium", "edit-distance"),
    ("dynamic-programming", 91):   Problem("Decode Ways",                                  "Medium", "decode-ways"),
    ("dynamic-programming", 97):   Problem("Interleaving String",                          "Medium", "interleaving-string"),
    ("dynamic-programming", 115):  Problem("Distinct Subsequences",                        "Hard",   "distinct-subsequences"),
    ("dynamic-programming", 139):  Problem("Word Break",                                   "Medium", "word-break"),
    ("dynamic-programming", 152):  Problem("Maximum Product Subarray",                     "Medium", "maximum-product-subarray"),
    ("dynamic-programming", 198):  Problem("House Robber",                                 "Medium", "house-robber"),
    ("dynamic-programming", 213):  Problem("House Robber II",                              "Medium", "house-robber-ii"),
    ("dynamic-programming", 300):  Problem("Longest Increasing Subsequence",               "Medium", "longest-increasing-subsequence"),
    ("dynamic-programming", 309):  Problem("Best Time to Buy And Sell Stock With Cooldown", "Medium", "best-time-to-buy-and-sell-stock-with-cooldown"),
    ("dynamic-programming", 312):  Problem("Burst Balloons",                               "Hard",   "burst-balloons"),
    ("dynamic-programming", 322):  Problem("Coin Change",                                  "Medium", "coin-change"),
    ("dynamic-programming", 329):  Problem("Longest Increasing Path in a Matrix",          "Hard",   "longest-increasing-path-in-a-matrix"),
    ("dynamic-programming", 377):  Problem("Combination Sum IV",                           "Medium", "combination-sum-iv"),
    ("dynamic-programming", 416):  Problem("Partition Equal Subset Sum",                   "Medium", "partition-equal-subset-sum"),
    ("dynamic-programming", 494):  Problem("Target Sum",                                   "Medium", "target-sum"),
    ("dynamic-programming", 518):  Problem("Coin Change II",                               "Medium", "coin-change-ii"),
    ("dynamic-programming", 647):  Problem("Palindromic Substrings",                       "Medium", "palindromic-substrings"),
    ("dynamic-programming", 746):  Problem("Min Cost Climbing Stairs",                     "Easy",   "min-cost-climbing-stairs"),
    ("dynamic-programming", 1143): Problem("Longest Common Subsequence",                   "Medium", "longest-common-subsequence"),

    # ============================== Greedy ==============================
    ("greedy", 45):   Problem("Jump Game II",                          "Medium", "jump-game-ii"),
    ("greedy", 53):   Problem("Maximum Subarray",                      "Medium", "maximum-subarray"),
    ("greedy", 55):   Problem("Jump Game",                             "Medium", "jump-game"),
    ("greedy", 134):  Problem("Gas Station",                           "Medium", "gas-station"),
    ("greedy", 678):  Problem("Valid Parenthesis String",              "Medium", "valid-parenthesis-string"),
    ("greedy", 763):  Problem("Partition Labels",                      "Medium", "partition-labels"),
    ("greedy", 846):  Problem("Hand of Straights",                     "Medium", "hand-of-straights"),
    ("greedy", 1899): Problem("Merge Triplets to Form Target Triplet", "Medium", "merge-triplets-to-form-target-triplet"),

    # ============================== Intervals ==============================
    ("intervals", 56):   Problem("Merge Intervals",                          "Medium", "merge-intervals"),
    ("intervals", 57):   Problem("Insert Interval",                          "Medium", "insert-interval"),
    ("intervals", 252):  Problem("Meeting Rooms",                            "Easy",   "meeting-rooms"),
    ("intervals", 253):  Problem("Meeting Rooms II",                         "Medium", "meeting-rooms-ii"),
    ("intervals", 435):  Problem("Non-overlapping Intervals",                "Medium", "non-overlapping-intervals"),
    ("intervals", 1851): Problem("Minimum Interval to Include Each Query",   "Hard",   "minimum-interval-to-include-each-query"),

    # ============================== Math & Geometry ==============================
    ("math-and-geometry", 43):   Problem("Multiply Strings",   "Medium", "multiply-strings"),
    ("math-and-geometry", 48):   Problem("Rotate Image",       "Medium", "rotate-image"),
    ("math-and-geometry", 50):   Problem("Pow(x, n)",          "Medium", "powx-n"),
    ("math-and-geometry", 54):   Problem("Spiral Matrix",      "Medium", "spiral-matrix"),
    ("math-and-geometry", 66):   Problem("Plus One",           "Easy",   "plus-one"),
    ("math-and-geometry", 73):   Problem("Set Matrix Zeroes",  "Medium", "set-matrix-zeroes"),
    ("math-and-geometry", 202):  Problem("Happy Number",       "Easy",   "happy-number"),
    ("math-and-geometry", 2013): Problem("Detect Squares",     "Medium", "detect-squares"),

    # ============================== Bit Manipulation ==============================
    ("bit-manipulation", 7):   Problem("Reverse Integer",    "Medium", "reverse-integer"),
    ("bit-manipulation", 136): Problem("Single Number",      "Easy",   "single-number"),
    ("bit-manipulation", 190): Problem("Reverse Bits",       "Easy",   "reverse-bits"),
    ("bit-manipulation", 191): Problem("Number of 1 Bits",   "Easy",   "number-of-1-bits"),
    ("bit-manipulation", 268): Problem("Missing Number",     "Easy",   "missing-number"),
    ("bit-manipulation", 338): Problem("Counting Bits",      "Easy",   "counting-bits"),
    ("bit-manipulation", 371): Problem("Sum of Two Integers", "Medium", "sum-of-two-integers"),

    # ============================== Concurrency (extra, not NeetCode 150) ==============================
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


def topic_problems(topic: str) -> list[int]:
    """All problem numbers in scope for a topic — union of folders and metadata."""
    nums: set[int] = set()
    topic_dir = SRC / topic
    if topic_dir.is_dir():
        for child in topic_dir.iterdir():
            if child.is_dir() and child.name.isdigit():
                nums.add(int(child.name))
    for (t, n) in PROBLEMS:
        if t == topic:
            nums.add(n)
    return sorted(nums)


def has_solution(topic: str, num: int, lang: str) -> bool:
    return (SRC / topic / str(num) / f"solution.{lang}").exists()


def language_cell(topic: str, num: int, lang: str) -> str:
    if has_solution(topic, num, lang):
        return f"[solution.{lang}](./{num}/solution.{lang})"
    return "—"


def badge(label: str, message: str, color: str) -> str:
    def esc(s: str) -> str:
        return s.replace("-", "--").replace("_", "__").replace(" ", "_")
    url = f"https://img.shields.io/badge/{esc(label)}-{esc(message)}-{color}"
    return f"![{label}: {message}]({url})"


def sort_key(num: int, prob: Problem | None) -> tuple[int, int]:
    rank = DIFFICULTY_RANK.get(prob.difficulty, 99) if prob else 99
    return (rank, num)


def topic_stats(topic: str, problem_nums: list[int]) -> dict:
    diff_total: Counter = Counter()
    diff_solved: Counter = Counter()
    py = cpp = solved = 0
    for num in problem_nums:
        prob = PROBLEMS.get((topic, num))
        is_solved = has_solution(topic, num, "py") or has_solution(topic, num, "cpp")
        if prob:
            diff_total[prob.difficulty] += 1
            if is_solved:
                diff_solved[prob.difficulty] += 1
        if is_solved:
            solved += 1
        if has_solution(topic, num, "py"):
            py += 1
        if has_solution(topic, num, "cpp"):
            cpp += 1
    return {
        "total": len(problem_nums),
        "solved": solved,
        "py": py,
        "cpp": cpp,
        "diff_total": diff_total,
        "diff_solved": diff_solved,
    }


def build_table(topic: str, problem_nums: list[int]) -> str:
    rows = sorted(
        ((num, PROBLEMS.get((topic, num))) for num in problem_nums),
        key=lambda pair: sort_key(*pair),
    )

    lines = [
        "| # | Problem | Difficulty | Python | C++ |",
        "| --- | --- | --- | --- | --- |",
    ]
    for num, prob in rows:
        py = language_cell(topic, num, "py")
        cpp = language_cell(topic, num, "cpp")
        if prob is None:
            print(f"[WARN] No metadata for ({topic}, {num}) — add it to PROBLEMS")
            title_cell = f"Unknown #{num}"
            diff = "?"
        else:
            title_cell = f"[{prob.title}](https://leetcode.com/problems/{prob.slug}/)"
            diff = prob.difficulty
        lines.append(f"| {num} | {title_cell} | {diff} | {py} | {cpp} |")

    return "\n".join(lines)


def render_topic_header(stats: dict) -> str:
    badges = [badge("solved", f"{stats['solved']}/{stats['total']}", "blue")]
    for diff in ("Easy", "Medium", "Hard"):
        if stats["diff_total"][diff]:
            badges.append(
                badge(
                    diff,
                    f"{stats['diff_solved'][diff]}/{stats['diff_total'][diff]}",
                    DIFFICULTY_COLOR[diff],
                )
            )
    if stats["py"]:
        badges.append(badge("Python", str(stats["py"]), "3776AB"))
    if stats["cpp"]:
        badges.append(badge("C%2B%2B", str(stats["cpp"]), "00599C"))
    return " ".join(badges)


def render_topic_readme(topic: str) -> str:
    problem_nums = topic_problems(topic)
    title = TOPIC_TITLE.get(topic, topic.replace("-", " ").title())
    note = TOPIC_NOTE.get(topic, "")
    extra = TOPIC_EXTRA.get(topic, "")

    parts = [f"# {title}", ""]
    if problem_nums:
        stats = topic_stats(topic, problem_nums)
        parts.append(render_topic_header(stats))
        parts.append("")
    if note:
        parts.append(f"> {note}")
        parts.append("")
    if problem_nums:
        parts.append("## Problems")
        parts.append("")
        parts.append(build_table(topic, problem_nums))
        parts.append("")
    else:
        parts.append("_Nothing in scope yet._")
        parts.append("")
    if extra:
        parts.append(extra)
    return "\n".join(parts).rstrip() + "\n"


def render_root_readme() -> str:
    rows = []
    grand: dict = {
        "total": 0, "solved": 0, "py": 0, "cpp": 0,
        "diff_total": Counter(), "diff_solved": Counter(),
    }
    for topic in TOPIC_ORDER:
        nums = topic_problems(topic)
        stats = topic_stats(topic, nums) if nums else None
        rows.append((topic, stats))
        if stats:
            grand["total"] += stats["total"]
            grand["solved"] += stats["solved"]
            grand["py"] += stats["py"]
            grand["cpp"] += stats["cpp"]
            grand["diff_total"] += stats["diff_total"]
            grand["diff_solved"] += stats["diff_solved"]

    badges = [
        badge("solved", f"{grand['solved']}/{grand['total']}", "blue"),
        badge("Easy",    f"{grand['diff_solved']['Easy']}/{grand['diff_total']['Easy']}",     DIFFICULTY_COLOR["Easy"]),
        badge("Medium",  f"{grand['diff_solved']['Medium']}/{grand['diff_total']['Medium']}", DIFFICULTY_COLOR["Medium"]),
        badge("Hard",    f"{grand['diff_solved']['Hard']}/{grand['diff_total']['Hard']}",     DIFFICULTY_COLOR["Hard"]),
        badge("Python",  str(grand["py"]),  "3776AB"),
        badge("C%2B%2B", str(grand["cpp"]), "00599C"),
    ]

    lines = [
        "# Algorithms & Data Structures",
        "",
        " ".join(badges),
        "",
        "> LeetCode solutions grouped by topic — full [NeetCode 150](https://neetcode.io/practice) checklist plus a few extras.",
        "",
        "## Topics",
        "",
        "| Topic | Progress | Easy | Medium | Hard | Python | C++ |",
        "| --- | --- | --- | --- | --- | --- | --- |",
    ]
    for topic, stats in rows:
        title = TOPIC_TITLE.get(topic, topic)
        if not stats:
            lines.append(f"| [{title}](./{topic}/README.md) | — | — | — | — | — | — |")
            continue
        def cell(s_done, s_total):
            return f"{s_done}/{s_total}" if s_total else "—"
        progress = f"{stats['solved']}/{stats['total']}" if stats["total"] else "—"
        lines.append(
            f"| [{title}](./{topic}/README.md) "
            f"| {progress} "
            f"| {cell(stats['diff_solved']['Easy'], stats['diff_total']['Easy'])} "
            f"| {cell(stats['diff_solved']['Medium'], stats['diff_total']['Medium'])} "
            f"| {cell(stats['diff_solved']['Hard'], stats['diff_total']['Hard'])} "
            f"| {stats['py'] or '—'} "
            f"| {stats['cpp'] or '—'} |"
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
        "Folders with no solution yet contain a `.gitkeep` and show `—` in the table.",
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
