/* ласс должен предоставл€ть, как минимум, следующие функции :

конструктор копировани€;
деструктор;
оператор присваивани€;
void print() Ц печать содержимого;**
bool insert(int key) Ц вставка элемента;**
bool contains(int key) - проверка наличи€ элемента;**
bool erase(int key) Ц удаление элемента;*!
¬ариант 3: дл€ заданного std::vector<int> верните новый std::vector<int>,
содержащий все повтор€ющиес€ элементы (дл€ вектора {3 2 2 4} результат должен быть {2} )

*/
#include<iostream>
#include <conio.h>
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


	Set(const Set& other) {
		root = copy(other.root);
	}


	~Set() { destroy(root);}


	Set& operator = (const Set& other) {
		if (this == &other) return *this;
		root = copy(other.root);
		return *this;

	}


	bin_tree* copy(const bin_tree* tree) {
		if (!tree) {
			return nullptr;
		}
		else {
			bin_tree* new_tree = new bin_tree(tree->value);
			new_tree->left = copy(tree->left);
			new_tree->right = copy(tree->right);
			return new_tree;
		}

	}


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
			destroy(tree);
			return true;
		}
		else if(tree->left!=nullptr) {
			bin_tree* tmp = tree;
			tree = tree->left;
			delete tmp;
		}
		else if ((tree->right != nullptr)) {
			bin_tree* tmp = tree;
			tree = tree->right;
			delete tmp;
		}
		else {
			//тут должен быть код:)
		}
	}


	void print(bin_tree*tree) {
		if (tree) {
			print(tree->left);
			cout <<tree->value ;
			print(tree->right);
			
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