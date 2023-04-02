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

size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

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


int get_key()
{
	int key = _getch();
	if ((key == 0) || (key == 224))
		key = _getch();
	return key;
}

int menu(){
	cout << "\nWhat are you want to do?\n\n"
		"1 - add an element\n"
		"2 - check an element\n"
		"3 - delete an element\n"
		"4 - print\n"
		"5 - exercise\n"
		"6 - exercise time\n\n"
		"go out: Esc\n";


	while (true)
	{
		int key = get_key();
		if ((key == 27) || (key > '0' && key <= '6'))
			return key;
	}
}



void print_tree(Bin_tree& tree) {
	tree.print();
}


void add_element(Bin_tree& tree) {
	int elem = Check();
	tree.insert(elem);
}
void delete_elem(Bin_tree& tree) {
	int key = Check();
	if (tree.erase(key)) {
		cout << "Element removed";
	}
	else {
		cout << "Element not removed";
	}
}

void check_elem(Bin_tree& tree) {
	int key = Check();
	if (tree.contains(key)) {
		cout << "Found!";
	}
	else {
		cout << "Not Found";
	}
}

vector<int> find_duplicates(const vector<int>& vec) {
	Bin_tree tree;
	vector<int> duplicates;

	for (int i : vec) {
		if (tree.contains(i)) {
			if (find(duplicates.begin(), duplicates.end(), i) == duplicates.end()) {
				duplicates.push_back(i);
			}
		}
		else {
			tree.insert(i);
		}
	}
	return duplicates;
}


int main() {
	Bin_tree tree;
	vector<int> mas = { 3,2,2,2,3,1,4,7,9,0,3,3,3 };
	vector<int> dubl = find_duplicates(mas);
	for (int i : dubl) {
		cout << i;
	}
	//int m = menu();
	//while (true) {
	//	switch (m)
	//	{
	//	case 1:
	//		add_element(tree);
	//		break;
	//	case 2:
	//		check_elem(tree);
	//		break;
	//	case 3:
	//		delete_elem(tree);
	//		break;
	//	case 4:
	//		cout << "1";
	//		print_tree(tree);
	//		break;
	//	case 5:

	//		break;
	//	case 6:

	//		break;
	//	case 27:
	//		break;
	//	}
	//}
	return 0;
}