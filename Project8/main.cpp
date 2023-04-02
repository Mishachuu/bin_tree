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


	struct node
	{
		int value;
		node* left;
		node* right;
		node(int val) : value(val), left(nullptr), right(nullptr){}
		
	};


class Bin_tree {

public:
	Bin_tree() :root(nullptr){}


	~Bin_tree() { destroy(root);}


	bool insert(int val) {
	return insert_shadow(&root, val);
	}


	bool contains(int key) const {
		return contains_shadow( root, key);
	}
	 

	Bin_tree& operator = (const Bin_tree& other) {
		if (this == &other) return *this;
		this->~Bin_tree();
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
	node* root;
	
	Bin_tree(node* other): root(other){}

	Bin_tree(const Bin_tree& other) {
		root = copy(other.root);
	}


	node* copy(const node* tree) {
		if (!tree) {
			return nullptr;
		}
		else {
			node* new_tree = new node(tree->value);
			new_tree->left = copy(tree->left);
			new_tree->right = copy(tree->right);
			return new_tree;
		}

	}


	bool insert_shadow(node** root, int val) {
		if (!*root) {
			*root = new node(val);
			return true;
		}
		if (val < (*root)->value) {
			return insert_shadow(&(*root)->left,val);
		}
		else if (val > (*root)->value) {
			return insert_shadow(&(*root)->right, val);
		}
		return false;
	}


	bool contains_shadow(const node* root, int key)const {
		if (!root) {
			return false;
		}
		if (key == root->value) { return true; }
		else if (key < root->value) {
			return contains_shadow(root->left, key);
		}
		else {
			return contains_shadow(root->right,key);
		}

	}

	bool erase_shadow(node** root,int key) {
		if (!*root) return false;

		if (key < (*root)->value) {
			return erase_shadow(&(*root)->left, key);
		}
		else if (key > (*root)->value) {
			return erase_shadow(&(*root)->right, key);
		}
		
		if ((*root)->left == nullptr && (*root)->right == nullptr) {
			delete *root;
			return true;
		}
		else if ((*root)->left != nullptr) {
			node* tmp = (*root)->left;
			delete *root;
			*root = tmp;
			return true;
		}
		else if ((*root)->right != nullptr) {
			node* tmp = (*root)->right;
			delete *root;
			*root = tmp;
			return true;
		}
		else {
			node* tmp = find_min((*root));
			(*root)->value = tmp->value;
			erase_shadow(&(*root)->right, (*root)->value);
		}
	}

	node* find_min(node* root) {
		while (root->left != nullptr) {
			root = root->left;
		}
		return root;
	}

	void obhod(node* root)const {
		if (root) {
			obhod(root->left);
			cout << root->value<<' ';
			obhod(root->right);
		}
	}

	void destroy(node* tree) {
		if (tree) {
			destroy(tree->left);
			destroy(tree->right);
			delete tree;
		}
	}

};

int Check()
{
	int number = 0;
	while (number <=1)
	{
		while (!(cin >> number) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "ќшибка! ¬ведите целочисленное значение\n";
		}
		if (number <= 1) cout << "ќшибка! ¬ведите целочисленное значение\n";

	}

	return number;
}
int GetKey()
{
	int key = _getch();
	if ((key == 0) || (key == 224))
		key = _getch();
	return key;
}



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
	Bin_tree a;
	for (int i = 0; i < 10; i++) {
		a.insert(i);
	}
	Bin_tree b;
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