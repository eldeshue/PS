// tree �ڷᱸ���� �̿��Ͽ� ������ Ǯ���Ϸ��� �õ���
// tree�� node�� ��: child, ��: sibiling���� ������.
// tree�� �����ϰ�, ���ο� ���ڿ��� ���� �� ���� �񱳸� ���ؼ� leaf�� ��带 �߰�
// ������ ��������δ� �޸� �ʰ��� ���� �ذῡ ������.
// �޸� �ʰ��� �ؼ��ϱ� ���ؼ� ���Ϳ� ���ڿ��� �����ϰ�, tree���� iterator�� �༭ ����
// ������ ������ ���� �ذῡ�� ������.
// 
// ���� ������ ã�ƺ��� �Է����� ���� ���ڿ��� ������ ��, ���λ簡 �Ǵ� ���ڿ��� �����Ͽ� Ǯ��
// ������ ���Ӱ��踸 ���� tree�� ������ �����ߴٴ� ��.
// tree�� �������� ���̱⿡ �����ϸ� �淮ȭ�� �߱��ؾ� ��.

#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::string>::iterator str_vec_itr;

typedef struct Node
{
    str_vec_itr data;

    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    bool is_root = false;
    bool is_leaf = true;
    bool is_end = true;
} Node;

class NotPrefixTree
{
public:
    Node* root;

    NotPrefixTree() // ����ִ� ��Ʈ ��带 ������
    {
        root = new Node;
        root->is_root = true;
    }
    NotPrefixTree(const NotPrefixTree& m) = delete;
    ~NotPrefixTree()
    {
        delete_node(root);
    }
    NotPrefixTree& operator=(const NotPrefixTree& m) = delete;

    static bool ok_prefix(Node* node, const str_vec_itr str)
    {
        if (node->is_root)
        {
            return false;
        }
        if (node->data->length() > str->length())
        {
            if (node->data->substr(0, str->length()) == *str)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (str->substr(0, node->data->length()) == *node->data)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    void set_node(Node* tgt_node, const str_vec_itr new_value)
    {
        if (tgt_node == nullptr)
        {
            return;
        }

        // ���λ����� �ƴ��� �Ǵ�
        // ���λ��̸� return
        // ���λ簡 �ƴϸ� go
        if (!tgt_node->is_root)
        {
            if (!ok_prefix(tgt_node->parent, new_value))
            {
                if (tgt_node->is_end)
                {
                    Node* new_node = new Node;
                    new_node->data = new_value;
                    new_node->parent = tgt_node->parent;
                    //
                    tgt_node->right = new_node;
                    tgt_node->is_end = false;
                }
                else
                {
                    set_node(tgt_node->right, new_value);
                }
            }
        }

        if (!ok_prefix(tgt_node, new_value))
        {
            // ���λ� �ƴ�, ������ ������
            if (tgt_node->is_leaf)
            {
                // ���ο� node �ʱ�ȭ
                Node* new_node = new Node;
                new_node->data = new_value;
                new_node->parent = tgt_node;
                //
                tgt_node->left = new_node;
                tgt_node->is_leaf = false;
            }
            else
            {
                set_node(tgt_node->left, new_value);
            }
        }
    }

    int find_max_depth(Node* node, int depth)
    {
        int l_depth = 0, r_depth = 0;

        if (!node->is_end) // ���� Ʈ��
        {
            r_depth = find_max_depth(node->right, depth);
        }

        if (node->is_leaf) // ��
        {
            return depth;
        }
        else // ���� Ʈ��
        {
            l_depth = find_max_depth(node->left, depth + 1);
        }

        return l_depth > r_depth ? l_depth : r_depth; // ����
    }

    void delete_node(Node* tgt_node)
    {
        if (tgt_node != nullptr)
        {
            if (!tgt_node->is_end)
            {
                delete_node(tgt_node->right);
            }
            if (!tgt_node->is_leaf)
            {
                delete_node(tgt_node->left);
            }
            delete tgt_node;
            tgt_node = nullptr;
        }
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    NotPrefixTree t;

    int N;
    std::cin >> N;
    std::vector<std::string> str_vec(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> str_vec[i];
    }
    for (auto itr = str_vec.begin(); itr != str_vec.end(); ++itr)
    {
        t.set_node(t.root, itr);
    }
    std::cout << t.find_max_depth(t.root, 0);
}