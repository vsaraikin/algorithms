#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Объект с трекингом жизненного цикла — будем видеть когда создаётся и умирает.
struct Resource {
	std::string name;
	Resource(std::string n) : name(std::move(n)) {
		std::cout << "+ create " << name << "\n";
	}
	~Resource() { std::cout << "- destroy " << name << "\n"; }
	void greet() const { std::cout << "  hello from " << name << "\n"; }
};

// =============================================================================
// Пример 1: создание и счётчик
// =============================================================================
void example_basics() {
	std::cout << "\n--- 1. basics ---\n";
	auto p = std::make_shared<Resource>("A");
	std::cout << "use_count = " << p.use_count() << "\n"; // 1
	p->greet();
}

// =============================================================================
// Пример 2: копирование делит владение
// =============================================================================
void example_copy() {
	std::cout << "\n--- 2. copy ---\n";
	auto p = std::make_shared<Resource>("B");
	{
		auto q = p; // count: 1 → 2
		auto r = p; // count: 2 → 3
		std::cout << "use_count = " << p.use_count() << "\n";
	} // q, r умерли → count: 3 → 1
	std::cout << "after scope, use_count = " << p.use_count() << "\n";
}

// =============================================================================
// Пример 3: move передаёт владение без инкремента
// =============================================================================
void example_move() {
	std::cout << "\n--- 3. move ---\n";
	auto a = std::make_shared<Resource>("C");
	auto b = std::move(a); // a опустошается, b владеет
	std::cout << "a is null? " << (a == nullptr) << "\n";
	std::cout << "b use_count = " << b.use_count() << "\n"; // 1, не 2
}

// =============================================================================
// Пример 4: передача в функцию
// =============================================================================
void process(std::shared_ptr<Resource> p) {
	std::cout << "  inside process, count = " << p.use_count() << "\n";
	p->greet();
}

void example_function_pass() {
	std::cout << "\n--- 4. pass to function ---\n";
	auto p = std::make_shared<Resource>("D");
	process(p); // копия параметра → count: 1 → 2 на входе, 2 → 1 на выходе
	std::cout << "after call, count = " << p.use_count() << "\n";
}

// =============================================================================
// Пример 5: возврат из функции (фабрика)
// =============================================================================
std::shared_ptr<Resource> make_resource(const std::string& n) {
	return std::make_shared<Resource>(n);
}

void example_factory() {
	std::cout << "\n--- 5. factory ---\n";
	auto p = make_resource("E");
	std::cout << "got, count = " << p.use_count() << "\n";
}

// =============================================================================
// Пример 6: vector с shared_ptr
// =============================================================================
void example_container() {
	std::cout << "\n--- 6. container ---\n";
	std::vector<std::shared_ptr<Resource>> bag;
	bag.push_back(std::make_shared<Resource>("F"));
	bag.push_back(std::make_shared<Resource>("G"));

	auto external = bag[0]; // делим владение с вектором
	std::cout << "F count = " << external.use_count() << "\n"; // 2

	bag.clear(); // G умирает (count 1→0), F остаётся (count 2→1)
	std::cout << "after clear, F count = " << external.use_count() << "\n";
}

// =============================================================================
// Пример 7: reset
// =============================================================================
void example_reset() {
	std::cout << "\n--- 7. reset ---\n";
	auto p = std::make_shared<Resource>("H");
	p.reset(); // объект умирает здесь
	std::cout << "p empty? " << (p == nullptr) << "\n";

	p.reset(new Resource("H2")); // новый объект
	std::cout << "p has new, count = " << p.use_count() << "\n";
}

// =============================================================================
// Пример 8: weak_ptr — невладеющая ссылка
// =============================================================================
void example_weak() {
	std::cout << "\n--- 8. weak_ptr ---\n";
	std::weak_ptr<Resource> w;
	{
		auto strong = std::make_shared<Resource>("I");
		w = strong; // слабая ссылка, count не меняется
		std::cout << "strong count = " << strong.use_count() << "\n"; // 1
		std::cout << "weak expired? " << w.expired() << "\n";         // 0
	} // strong умирает

	std::cout << "after scope, weak expired? " << w.expired() << "\n"; // 1
	if (auto p = w.lock()) {
		std::cout << "alive\n";
	} else {
		std::cout << "  weak.lock() returned nullptr (objект уже мёртв)\n";
	}
}

// =============================================================================
// Пример 9: цикл и почему нужен weak_ptr
// =============================================================================
struct Node {
	std::string name;
	std::shared_ptr<Node> child;
	std::weak_ptr<Node> parent; // ← weak ломает цикл

	Node(std::string n) : name(std::move(n)) {
		std::cout << "+ Node " << name << "\n";
	}
	~Node() { std::cout << "- Node " << name << "\n"; }
};

void example_no_cycle() {
	std::cout << "\n--- 9. tree with parent (no cycle) ---\n";
	auto root = std::make_shared<Node>("root");
	auto kid = std::make_shared<Node>("kid");
	root->child = kid;
	kid->parent = root; // weak, не shared

	if (auto p = kid->parent.lock()) {
		std::cout << "  kid's parent is " << p->name << "\n";
	}
} // оба умирают, нет утечки

int main() {
	example_basics();
	example_copy();
	example_move();
	example_function_pass();
	example_factory();
	example_container();
	example_reset();
	example_weak();
	example_no_cycle();

	std::cout << "\n=== end of main ===\n";
	return 0;
}
