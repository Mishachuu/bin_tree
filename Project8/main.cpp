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

public:
	Set() :root(nullptr){}


	~Set() { destroy(root);}


	bool insert(int val) {
	return insert_shadow(&root, val);
	}


	bool contains(int key) const {
		return contains_shadow( root, key);
	}
	 

	Set& operator = (const Set& other) {
		if (this == &other) return *this;
		this->~Set();
		root = copy(other.root);
		return *this;

	}


	bool erase(int key) {
		return erase_shadow(&root, key);
	}

	void print() {
		obhod(root);
		cout << endl;
	}


private:
	bin_tree* root;
	
	Set(bin_tree* other): root(other){}

	Set(const Set& other) {
		root = copy(other.root);
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


	bool insert_shadow(bin_tree** node, int val) {
		if (!*node) {
			*node = new bin_tree(val);
			return true;
		}
		if (val < (*node)->value) {
			return insert_shadow(&(*node)->left,val);
		}
		else if (val > (*node)->value) {
			return insert_shadow(&(*node)->right, val);
		}
		return false;
	}


	bool contains_shadow(const bin_tree* node, int key)const {
		if (!node) {
			return false;
		}
		if (key == node->value) { return true; }
		else if (key < node->value) {
			return contains_shadow(node->left, key);
		}
		else {
			return contains_shadow(node->right,key);
		}

	}

	bool erase_shadow(bin_tree** node,int key) {
		if (!*node) return false;

		if (key < (*node)->value) {
			return erase_shadow(&(*node)->left, key);
		}
		else if (key > (*node)->value) {
			return erase_shadow(&(*node)->right, key);
		}
		
		if ((*node)->left == nullptr && (*node)->right == nullptr) {
			delete *node;
		}
		else if ((*node)->left != nullptr) {
			bin_tree* tmp = (*node)->left;
			delete *node;
			*node = tmp;
		}
		else if ((*node)->right != nullptr) {
			bin_tree* tmp = (*node)->right;
			delete *node;
			*node = tmp;
		}
		else {
			bin_tree* tmp = find_min((*node));
			(*node)->value = tmp->value;
			erase_shadow(&(*node)->right, (*node)->value);
		}
	}

	bin_tree* find_min(bin_tree* root) {
		while (root->left != nullptr) {
			root = root->left;
		}
		return root;
	}

	void obhod(bin_tree* root)const {
		if (root) {
			obhod(root->left);
			cout << root->value<<' ';
			obhod(root->right);
		}
	}

	void destroy(bin_tree* tree) {
		if (tree) {
			destroy(tree->left);
			destroy(tree->right);
			delete tree;
		}
	}

};




/*vector<int> findDuplicates(const vector<int>& vec) {
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
}*/
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
	a.print();
	cout << a.contains(15)<<' ';
	cout << a.insert(21) << ' ';
	cout<<a.erase(12) << ' ';
	a.print();
	return 0;
}