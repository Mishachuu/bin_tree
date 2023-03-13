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
#include <vector>
using namespace std;


	struct bin_tree
	{
		int value;
		bin_tree* left;
		bin_tree* right;
		bin_tree(int val) : value(val), left(nullptr), right(nullptr){}
		
	};


class Set {


private:


	bin_tree* root;

public:
	Set() :root(nullptr){}
	Set(bin_tree* other): root(other){}

	Set(const Set& other) {
		root = copy(other.root);
	}


	~Set() { destroy(root);}


	Set& operator = (const Set& other) {
		if (this == &other) return *this;
		this->~Set();
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


	bool insert(int val) {
		bin_tree* tree =root;
		if (!root) {
			root = new bin_tree(val);
			return true;
		}
		while (tree) {
			if (val < tree->value) {
				if (tree->left == nullptr) {
					tree->left = new bin_tree(val);
					return true;
				}
				tree = tree->left;
			}
			else if (val > tree->value) {
				if (tree->right == nullptr) {
					tree->right = new bin_tree(val);
					return true;
				}
				tree = tree->right;
			}
			else {
				return false;
			}
		}
	}


	bool contains(int key) {
		bin_tree* tree = root;
		while (tree) {
			if (key < tree->value) {
				tree = tree->left;
			}
			else if (key > tree->value) {
				tree = tree->right;
			}
			else if (key == tree->value) {
				return true;
			}
		}
		return false;
	}

	bool erase(int key) {
		bin_tree* tree = root;
		if (!tree) { return false; }
		while (tree) {
			if (key < tree->value) {
				tree = tree->left;
			}
			else if (key > tree->value) {
				tree = tree->right;
			}
			else if (key == tree->value) {
				if (tree->left == nullptr && tree->right == nullptr) {
					destroy(tree);
				}
				else if (tree->left != nullptr) {
					bin_tree* tmp = tree;
					tree = tree->left;
					delete tmp;
					return true;
				}
				else if (tree->right != nullptr) {
					bin_tree* tmp = tree;
					tree = tree->right;
					delete tmp;
					return true;
				}
				else {
					bin_tree* tmp = find_min(tree);
					tree->value = tmp->value;
					tree = root->right;
					erase(tmp->value);
					return true;
				}
			}
		}
		return false;
	}

	bin_tree* find_min(bin_tree* root) {
		while (root->left != nullptr) {
			root = root->left;
		}
		return root;
	}

	void print() {
		bin_tree* tree = root;
		if (!root) {
			cout << tree->value;


		}
	}


	void destroy(bin_tree* tree) {
		if (tree) {
			destroy(tree->left);
			destroy(tree->right);
			delete tree;
		}
	}
	iterator_set begin();
	iterator_set end();
};


class iterator_set {
	bin_tree* current;
public:
	iterator_set(bin_tree* cur):current(cur){}
	void left() {
		if (current != nullptr) current=current->left;
		else { cout << "»тератор достиг конца"; }
	}
	void right() {
		if (current != nullptr) current=current->right;
		else{ cout << "»тератор достиг конца"; }
	}
	int operator*() const{
		return current->value;
	}
	bool operator!=(const iterator_set& other) {
		if (this->current != other.current) return true;
		return false;
	}
	iterator_set begin() {
		bin_tree* cur = current;
		while (cur->left != nullptr) {
			cur = cur->left;
		}
		return iterator_set(cur);
	}
	iterator_set end() {
		return(iterator_set(nullptr));
	}
};

vector<int> findDuplicates(const vector<int>& vec) {
	Set unique;
	
	Set duplicates;
	for (int i : vec) {
		if (unique.contains(i) == false) {
			unique.insert(i);
		}
		else {
			 duplicates.insert(i);
		}
	}
	vector<int> result;
	for (iterator_set it = duplicates.begin(); it != duplicates.end();it.right()) {
		result.push_back(*(it));
	}
	return result;
}
int main() {
	Set a;
	for (int i = 0; i < 10; i++) {
		a.insert(i);
	}
	Set b;
	for (int i = 10; i < 20; i++) {
		b.insert(i);
	}
	a = b;
	cout<< a.contains(2);
	cout << a.contains(15);
	cout << a.erase(15);
	return 0;
}