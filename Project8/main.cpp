/* ласс должен предоставл€ть, как минимум, следующие функции :

конструктор копировани€;
деструктор;
оператор присваивани€;
void print() Ц печать содержимого;
bool insert(int key) Ц вставка элемента;
bool contains(int key) - проверка наличи€ элемента;
bool erase(int key) Ц удаление элемента;
¬ариант 3: дл€ заданного std::vector<int> верните новый std::vector<int>,
содержащий все повтор€ющиес€ элементы (дл€ вектора {3 2 2 4} результат должен быть {2} )

*/
using namespace std;


class Set {


private:


	struct bin_tree
	{
		int value;
		bin_tree* left;
		bin_tree* right;
		bin_tree(int val) : value(val), left(nullptr), right(nullptr){}
		
	};
	bin_tree* root;


	Set() :root(nullptr){}


	~Set() { destroy(root);}


	bool insert(bin_tree* tree, int val) {
		if (!tree) {
			tree = new bin_tree(val);
			return true;
		}
		if (val < tree->value) {
			insert(tree->left, val);
		}
		else if (val > tree->value) {
			 insert(tree->right, val);
		}
		return true;
	}


	bool contains(bin_tree* tree, int key) {
		if (!tree) return false;
		if (key > tree->value) {
			return contains(tree->right, key);
		}
		else if (key < tree->value) {
			return insert(tree->left, key);
			}
		return true;
	}


	bool erase(bin_tree* tree, int key) {
		if (!tree) { return false; }
		if (key > tree->value) {
			erase(tree->right, key);
		}
		if (key < tree->value) {
			erase(tree->left, key);
		}
		if (tree->left == nullptr && tree->right == nullptr) {
			
		}
	}


	void destroy(bin_tree* tree) {
		if (!tree) {
			destroy(tree->left);
			destroy(tree->right);
			delete tree;
		}
	}
};