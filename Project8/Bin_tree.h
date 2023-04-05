class Bin_tree {
private:
	struct node
	{
		int value;
		node* left;
		node* right;
		node(int val) : value(val), left(nullptr), right(nullptr) {}

	};

	node* root;

	Bin_tree(node* other) : root(other) {}

	Bin_tree(const Bin_tree& other) {
		root = copy(other.root);
	}


	node* copy(const node* tree);


	bool insert_shadow(node** root, int val);


	bool contains_shadow(const node* root, int key)const;

	bool erase_shadow(node** root, int key);

	node* find_min(node* root);

	void obhod(node* root, int level = 3)const;

	void destroy(node* tree);
public:
	Bin_tree() :root(nullptr) {}


	~Bin_tree() { destroy(root); }


	bool insert(int val) {
		return insert_shadow(&root, val);
	}


	bool contains(int key) const {
		return contains_shadow(root, key);
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


};
