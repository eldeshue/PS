// tree의 부모 찾기
// 근데 사실 트리를 구현하고, 이를 순회할 필요가 없던게 아닌가 싶음.
// 입력으로 받는 두 값은 사실 둘 중 하나는 child고 나머지 하나는 parent인데
// 문제가 입력으로 주는 값들의 구조상 이미 있던 값이 부모임이 명확함.

/*
// try 1.
// tree 구현 과정에서 이미 잘못을 범햇음.
// DFS로 문제를 풀려고 했는데,
// 애초부터 접근이 잘못됨.
#include <iostream>
#include <vector>
#include <stack>
#include <set>

typedef struct node
{
	int value;
	std::vector<node*> children;
} node;

std::stack<int> prevIndex_stack;
std::stack<node*> prevNode_stack;
std::set<int> dict;

class MyTree {
private:
	int value = 1;
	std::vector<node*> children;
public:
	MyTree() {};
	~MyTree();

	void set_child(int parent_val, int child_val);
	int get_parent(int tgt_val);
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	dict.insert(1);
	MyTree tree;

	int nNode, input1, input2, p_val, c_val;
	std::cin >> nNode;
	for (int i = 0; i < nNode - 1; ++i)
	{
		std::cin >> input1 >> input2;
		// swap, smaller one must be the parent
		if (dict.find(input1) != dict.end())
		{
			p_val = input1;
			c_val = input2;
			dict.insert(input2);
		}
		else // input1 is a value of the new node
		{
			p_val = input2;
			c_val = input1;
			dict.insert(input1);
		}

		tree.set_child(p_val, c_val);
	}

	for (int i = 2; i <= nNode; ++i) // 각 순회가 O(n)이고, n-1번 반복하므로
	{								 // O(n^2)라서 시간 초과임.
		std::cout << tree.get_parent(i) <<"\n";
	}
}

void erase_recurse(node* cur_node)
{
	for (auto& elem : cur_node->children)
	{
		erase_recurse(elem);
	}

	cur_node->children.clear();
	return;
}

MyTree::~MyTree()
{
	for (auto& elem : children)
	{
		erase_recurse(elem);
	}
	children.clear();
}

void set_node(node* cur_node, int parent_val, int child_val)
{
	if (parent_val == cur_node->value)
	{
		// set new node
		node* temp = new node;
		temp->value = child_val;
		cur_node->children.push_back(temp); // jobs done

		// clear the stacks
		while (!prevIndex_stack.empty())
		{
			prevIndex_stack.pop();
			prevNode_stack.pop();
		}
		// exit 
		return;
	}
	else if (cur_node->children.empty() ||  // leaf 노드거나
		(prevIndex_stack.top() == cur_node->children.size())) // 너비 탐색을 마쳤다면
	{
		// back tracking, 부모 노드로 돌아감.
		node* parent_node = prevNode_stack.top();
		prevIndex_stack.pop();
		prevNode_stack.pop();
		return set_node(parent_node, parent_val, child_val);
	}
	else
	{
		// proceed
		int next_index = prevIndex_stack.top()++;
		prevIndex_stack.push(0);
		prevNode_stack.push(cur_node);
		return set_node(cur_node->children[next_index], parent_val, child_val);
	}
}
void MyTree::set_child(int parent_val, int child_val)
{
	prevIndex_stack.push(0);
	prevNode_stack.push((node*)this);

	return set_node((node*)this, parent_val, child_val);
}

int get_node(node* cur_node, int tgt_val)
{
	if (cur_node->value == tgt_val) // found, stop.
	{
		// get result, value of the parent node
		int result = prevNode_stack.top()->value;
		// clear the stacks
		while (!prevIndex_stack.empty())
		{
			prevIndex_stack.pop();
			prevNode_stack.pop();
		}
		// exit
		return result;
	}
	else if (cur_node->children.empty() ||
		(cur_node->children.size() == prevIndex_stack.top())) // back tracking.
	{
		node* parent_node = prevNode_stack.top();
		prevIndex_stack.pop();
		prevNode_stack.pop();
		return get_node(parent_node, tgt_val);
	}
	else // proceed.
	{
		int next_index = prevIndex_stack.top()++;
		prevIndex_stack.push(0);
		prevNode_stack.push(cur_node);
		return get_node(cur_node->children[next_index], tgt_val);
	}
}
int MyTree::get_parent(int tgt_val)
{
	prevIndex_stack.push(0);
	prevNode_stack.push((node*)this);

	return get_node((node*)this, tgt_val);
}

/*
// try 2
// 굳이 tree를 구현하지 말고, 야매로 풀기.
// 입출력 순서에 따라서 문제가 실패할 가능성이 다분함.
#include <iostream>
#include <set>

#define MAX 100001
int array[MAX];
std::set<int> tree;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
	std::cin >> N;
	tree.insert(1);
	int input1, input2, index, parent;
	for (int i = 0; i < N - 1; ++i)
	{
		std::cin >> input1 >> input2;
		if (tree.find(input1) != tree.end())
		{
			tree.insert(input2);
			parent = input1;
			index = input2;
		}
		else
		{
			tree.insert(input1);
			parent = input2;
			index = input1;
		}
		array[index] = parent;
	}

	for (int i = 2; i <= N; ++i)
	{
		std::cout << array[i] << "\n";
	}
}
*/
