// 트리 순회 문제
// 전위 중위 후위 순회한 결과를 출력

#include <iostream>

typedef struct node
{
	char c;
	node* left = nullptr;
	node* right = nullptr;

	bool is_leaf()
	{
		if (left == nullptr && right == nullptr)
		{
			return true;
		}
		return false;
	}
}node;

class MyBinaryTree
{
private:
	// data
	char c;
	node* left;
	node* right;

public:
	MyBinaryTree(char root_val, char left_val, char right_val);
	~MyBinaryTree();

	void get(char tgt, node*& result); // 전위 순회로 검색

	void trav_pre();	// 전위 순회
	void trav_in();		// 중위 순회
	void trav_post();	// 후위 순회
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int numNode;
	std::cin >> numNode;
	char t, l, r;
	std::cin >> t >> l >> r;
	MyBinaryTree tree(t, l, r);
	for (int i = 0; i < numNode - 1; ++i)
	{
		std::cin >> t >> l >> r;
		node* target_node = nullptr; 
		tree.get(t, target_node);
		if (l != '.')
		{
			target_node->left = new node;
			target_node->left->c = l;
		}
		if (r != '.')
		{
			target_node->right = new node;
			target_node->right->c = r;
		}
	}

	tree.trav_pre();
	std::cout << "\n";
	tree.trav_in();
	std::cout << "\n";
	tree.trav_post();

	/*
	// test code
	MyBinaryTree test('A', 'B', 'C');
	node* test_node = (node*)(&test);
	test_node->left->left = new node;
	test_node->left->left->c = 'D';
	test.trav_pre();
	*/
}

MyBinaryTree::MyBinaryTree(char root_val, char left_val, char right_val) : c(root_val)
{
	if (left_val != '.')
	{
		left = new node;
		left->c = left_val;
	}
	else
	{
		left = nullptr;
	}
	if (right_val != '.')
	{
		right = new node;
		right->c = right_val;
	}
	else
	{
		right = nullptr;
	}
}

void erase_recursively(node* tgt)
{
	if (tgt->left != nullptr)
	{
		erase_recursively(tgt->left);

	}
	if (tgt->right != nullptr)
	{
		erase_recursively(tgt->right);
	}
	delete tgt;
}

MyBinaryTree::~MyBinaryTree()
{
	if (left != nullptr)
	{
		erase_recursively(left);
	}
	if (right != nullptr)
	{
		erase_recursively(right);
	}

}

void find_recurse(char tgt, node* cur_node, node*& result)
{ // preorder traversal
	if (cur_node->c == tgt)
	{
		result = cur_node;
	}

	if(cur_node->left != nullptr)
	find_recurse(tgt, cur_node->left, result);
	if(cur_node->right != nullptr)
	find_recurse(tgt, cur_node->right, result);
}

void MyBinaryTree::get(char tgt, node*& result)
{
	find_recurse(tgt, (node*)this, result);
}

void print_pre(node* cur_node)
{
	std::cout << cur_node->c;

	if(cur_node->left != nullptr)
	print_pre(cur_node->left);
	if(cur_node->right != nullptr)
	print_pre(cur_node->right);
}
void MyBinaryTree::trav_pre()
{
	std::cout << c;

	if(left != nullptr)
	print_pre(left);
	if(right != nullptr)
	print_pre(right);
}

void print_in(node* cur_node)
{
	if(cur_node->left != nullptr)
	print_in(cur_node->left);

	std::cout << cur_node->c;

	if(cur_node->right != nullptr)
	print_in(cur_node->right);
}
void MyBinaryTree::trav_in()
{
	if(left != nullptr)
	print_in(left);

	std::cout << c;

	if(right != nullptr)
	print_in(right);
}

void print_post(node* cur_node)
{
	if(cur_node->left != nullptr)
	print_post(cur_node->left);
	if(cur_node->right != nullptr)
	print_post(cur_node->right);

	std::cout << cur_node->c;
}
void MyBinaryTree::trav_post()
{
	if(left != nullptr)
	print_post(left);
	if(right != nullptr)
	print_post(right);

	std::cout << c;
}
