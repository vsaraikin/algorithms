#include "../../../lib/cpp/node.cpp"
#include <cassert>
#include <stack>
#include <vector>

// =============================================================================
// DFS на бинарном дереве — 3 классических порядка обхода.
//
// pre-order:   корень → left → right
// in-order:    left → корень → right
// post-order:  left → right → корень
//
// Каждый порядок отвечает разным задачам:
//   pre-order:   копирование дерева, prefix-выражения, обход родитель→дети
//   in-order:    отсортированный обход BST, проверка BST
//   post-order:  удаление дерева, подсчёт размера/высоты, "сначала дети"
// =============================================================================

// -----------------------------------------------------------------------------
// 1. Рекурсивный DFS — самый компактный и читаемый.
// -----------------------------------------------------------------------------

void preorderRec(TreeNode* root, std::vector<int>& out) {
	if (!root) return;
	out.push_back(root->val);          // корень
	preorderRec(root->left, out);      // left
	preorderRec(root->right, out);     // right
}

void inorderRec(TreeNode* root, std::vector<int>& out) {
	if (!root) return;
	inorderRec(root->left, out);       // left
	out.push_back(root->val);          // корень
	inorderRec(root->right, out);      // right
}

void postorderRec(TreeNode* root, std::vector<int>& out) {
	if (!root) return;
	postorderRec(root->left, out);     // left
	postorderRec(root->right, out);    // right
	out.push_back(root->val);          // корень
}

// -----------------------------------------------------------------------------
// 2. Итеративный DFS через std::stack.
//    Нужен когда дерево очень глубокое и есть риск stack overflow.
// -----------------------------------------------------------------------------

// Pre-order итеративно: push правого первым, потом левого (LIFO).
std::vector<int> preorderIter(TreeNode* root) {
	std::vector<int> out;
	if (!root) return out;
	std::stack<TreeNode*> st;
	st.push(root);
	while (!st.empty()) {
		TreeNode* n = st.top(); st.pop();
		out.push_back(n->val);
		if (n->right) st.push(n->right);   // правый под левым в стеке
		if (n->left) st.push(n->left);     // левый сверху → выйдет первым
	}
	return out;
}

// In-order итеративно: спускаемся по левой ветви до конца, потом обрабатываем
// узел, потом идём в правое поддерево.
std::vector<int> inorderIter(TreeNode* root) {
	std::vector<int> out;
	std::stack<TreeNode*> st;
	TreeNode* cur = root;
	while (cur || !st.empty()) {
		while (cur) {                       // спустились по left'ам
			st.push(cur);
			cur = cur->left;
		}
		cur = st.top(); st.pop();
		out.push_back(cur->val);            // обработали узел
		cur = cur->right;                   // в правое поддерево
	}
	return out;
}

// Post-order итеративно: трюк через "обратный pre-order".
// Pre-order: корень → left → right.
// Если делать корень → right → left, потом reverse результата →
// получим left → right → корень = post-order.
std::vector<int> postorderIter(TreeNode* root) {
	std::vector<int> out;
	if (!root) return out;
	std::stack<TreeNode*> st;
	st.push(root);
	while (!st.empty()) {
		TreeNode* n = st.top(); st.pop();
		out.push_back(n->val);
		if (n->left) st.push(n->left);     // меняем порядок push
		if (n->right) st.push(n->right);
	}
	std::reverse(out.begin(), out.end());
	return out;
}

// -----------------------------------------------------------------------------
// 3. DFS с возвратом значения наверх — "bottom-up" pattern.
//    Используется для подсчёта высоты, размера, агрегаций по поддеревьям.
// -----------------------------------------------------------------------------

int height(TreeNode* root) {
	if (!root) return 0;
	return 1 + std::max(height(root->left), height(root->right));
}

int countNodes(TreeNode* root) {
	if (!root) return 0;
	return 1 + countNodes(root->left) + countNodes(root->right);
}

int sumNodes(TreeNode* root) {
	if (!root) return 0;
	return root->val + sumNodes(root->left) + sumNodes(root->right);
}

// -----------------------------------------------------------------------------
// 4. DFS с прокидыванием контекста ВНИЗ — "top-down" pattern.
//    Передаём накопленное значение в рекурсию.
// -----------------------------------------------------------------------------

// Сумма всех путей от корня до листьев, интерпретируемых как цифры числа.
// Например для [1,2,3] → 1*10+2=12 и 1*10+3=13 → сумма 25.
int sumPaths(TreeNode* root, int current = 0) {
	if (!root) return 0;
	current = current * 10 + root->val;
	if (!root->left && !root->right) return current;     // лист
	return sumPaths(root->left, current) + sumPaths(root->right, current);
}

// -----------------------------------------------------------------------------
// 5. DFS с глобальным/общим состоянием — pattern "обновляем максимум".
//    Подходит когда ответ зависит от ВСЕХ путей, а не только корневых.
//    Пример: diameter (124, 543).
// -----------------------------------------------------------------------------

class Diameter {
  public:
	int diameterOfBinaryTree(TreeNode* root) {
		best = 0;
		depth(root);
		return best;
	}

  private:
	int best;

	int depth(TreeNode* root) {
		if (!root) return 0;
		int l = depth(root->left);
		int r = depth(root->right);
		best = std::max(best, l + r);       // путь через текущий узел
		return 1 + std::max(l, r);          // высота для родителя
	}
};

// =============================================================================
// Tests
// =============================================================================

int main() {
	// Дерево:
	//        1
	//       / \
	//      2   3
	//     / \
	//    4   5

	TreeNode n4(4), n5(5);
	TreeNode n2(2, &n4, &n5), n3(3);
	TreeNode root(1, &n2, &n3);

	{
		std::vector<int> out;
		preorderRec(&root, out);
		assert(out == (std::vector<int>{1, 2, 4, 5, 3}));
	}

	{
		std::vector<int> out;
		inorderRec(&root, out);
		assert(out == (std::vector<int>{4, 2, 5, 1, 3}));
	}

	{
		std::vector<int> out;
		postorderRec(&root, out);
		assert(out == (std::vector<int>{4, 5, 2, 3, 1}));
	}

	assert(preorderIter(&root) == (std::vector<int>{1, 2, 4, 5, 3}));
	assert(inorderIter(&root) == (std::vector<int>{4, 2, 5, 1, 3}));
	assert(postorderIter(&root) == (std::vector<int>{4, 5, 2, 3, 1}));

	assert(height(&root) == 3);
	assert(countNodes(&root) == 5);
	assert(sumNodes(&root) == 15);

	// Пути как числа: 124, 125, 13. Сумма = 262
	assert(sumPaths(&root) == 262);

	// Диаметр: 4 → 2 → 5 = 2 ребра, или 4 → 2 → 1 → 3 = 3 ребра
	Diameter d;
	assert(d.diameterOfBinaryTree(&root) == 3);

	return 0;
}
