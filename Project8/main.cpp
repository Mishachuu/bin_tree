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
#include <ostream>
#include <iomanip>
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
	int number=-1;
	while (number<=0)
	{
		while (!(cin >> number) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "ќшибка! ¬ведите целочисленное значение\n";
		}
		if (number <= 0) cout << "ќшибка! ¬ведите целочисленное значение\n";

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

void create_time(int size) {
	system("cls");
	Bin_tree tree;
	clock_t start, end;
	double average_time = 0;
	for (int i = 0; i < 100; i++) {
		start = clock();
		for (int j = 0; j < size; j++) {
			tree.insert(int(lcg()));
		}
		end = clock();
		average_time += (double(end - start)) / (double(CLOCKS_PER_SEC));
	}
	average_time /= 100;
	cout << endl << "Time of create  " << size << " elements: " << average_time;
}


void search_time(int size) {
	Bin_tree tree;
	clock_t start, end;
	double average_time = 0;
	for (int i = 0; i < size; i++)
		tree.insert(int(lcg()));

	for (int i = 0; i < 1000; i++) {
		int val = int(lcg());
		while (tree.contains(val) == false) val = int(lcg());
		start = clock();
		tree.contains(val);
		end = clock();
		average_time += (double(end - start)) / (double(CLOCKS_PER_SEC));
	}
	average_time /= 1000;
	cout << endl << "Time of search element " << size << average_time;
}


void add_del_time(int size) {
	Bin_tree insert_tree;
	clock_t start, end;
	double average_time = 0;
	for (int j = 0; j < size; j++) {
		insert_tree.insert(int(lcg()));
	}
	for (int i = 0; i < 1000; i++) {
		int val = int(lcg());
		while (insert_tree.contains(val) == true) val = int(lcg());
		start = clock();
		insert_tree.insert(val);
		end = clock();
		average_time += (double(end - start)) / (double(CLOCKS_PER_SEC));
	}
	average_time /= 1000;
	cout << endl << "Time of insert " << size << average_time;
	average_time = 0;
	Bin_tree erase_tree;
	for (int j = 0; j < size; j++)
		erase_tree.insert(int(lcg()));
	for (int i = 0; i < 1000; i++)
	{
		int val = int(lcg());
		while (erase_tree.contains(val) == false) val = int(lcg());
		start = clock();
		erase_tree.erase(val);
		end = clock();
		average_time += (double(end - start)) / (double(CLOCKS_PER_SEC));
	}
	average_time /= 1000;
	cout << endl << "Time of erase " << size << average_time;
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


void menu_time() {
	int size;
	cout << "What size to calculate?\n\n"
		"1 - 1000\n"
		"2 - 10000\n"
		"3 - 100000\n";
	int param = Check();
	while (param > 3 || param <= 0)
	{
		cout << "Incorrect value" << endl << "Operation є";
		param = Check();
	}
	system("cls");
	switch (param)
	{
	case 1:
		size = 1000;
		break;
	case 2:
		size = 10000;
		break;
	case 3:
		size = 100000;
		break;
	}
	cout << "What time to calculate?\n\n"
		"1 - create tree\n"
		"2 - search element\n"
		"3 - delete and add\n";
	int n = Check();
	while (n > 4 || n <= 0)
	{
		cout << "Incorrect value";
		n = Check();
	}
	switch (n)
	{
	case 1:
		create_time(size);
		break;
	case 2:
		search_time(size);
		break;
	case 3:
		add_del_time(size);
		break;
	}
}


void print_tree(Bin_tree& tree) {
	tree.print();
}


void add_element(Bin_tree& tree) {
	system("cls");
	cout << "enter element";
	int elem = Check();
	tree.insert(elem);
}


void delete_elem(Bin_tree& tree) {
	system("cls");
	tree.print();
	cout << "write key";
	int key = Check();
	if (tree.erase(key)) {
		cout << "Element removed";
	}
	else {
		cout << "Element not removed";
	}
}


void check_elem(Bin_tree& tree) {
	system("cls");
	tree.print();
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


void padding_vector() {
	system("cls");
	vector<int> mass;
	cout << "how many items do you want to add?\n";
	int size = Check();
	for (int i = 0; i < size; i++) {
		int val = Check();
		mass.push_back(val);
	}
	system("cls");
	cout << "your vector:";
	for (int i : mass) {
		cout << i;
	}
	cout << "\nyour vector from duplicate:";
	vector<int>dubl = find_duplicates(mass);
	for (int i : dubl) {
		cout << i;
	}
}


int main() {
	setlocale(LC_ALL, "");
	Bin_tree tree;
	while (true) {
		int m = menu();
		if (m == 27) break;
		switch (m)
		{
		case '1':
			add_element(tree);
			break;
		case '2':
			check_elem(tree);
			break;
		case '3':
			delete_elem(tree);
			break;
		case '4':
			print_tree(tree);
			break;
		case '5':
			padding_vector();
			break;
		case '6':
			menu_time();
			break;
		case 27:
			break;
		}
	}
	return 0;
}

//Time of create  1000 elements: 0.00055 Time of create  10000 elements: 0.00403 Time of create  100000 elements: 0.03944
//Time of search element 1000 0.000184 Time of search element 10000 0.002761