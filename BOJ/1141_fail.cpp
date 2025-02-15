// tree 자료구조를 이용하여 문제를 풀이하려고 시도함
// tree의 node는 좌: child, 우: sibiling으로 구현함.
// tree를 구성하고, 새로운 문자열이 들어올 때 마다 비교를 통해서 leaf에 노드를 추가
// 하지만 결론적으로는 메모리 초과로 문제 해결에 실패함.
// 메모리 초과를 해소하기 위해서 벡터에 문자열을 저장하고, tree에는 iterator를 줘서 참조
// 하지만 여전히 문제 해결에는 실패함.
// 
// 이후 정답을 찾아보니 입력으로 받은 문자열을 정렬한 후, 접두사가 되는 문자열을 제거하여 풀이
// 패착은 종속관계만 보고서 tree를 가지고 접근했다는 점.
// tree는 생각보다 무겁기에 가능하면 경량화를 추구해야 함.

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

    NotPrefixTree() // 비어있는 루트 노드를 생성함
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

        // 접두사인지 아닌지 판단
        // 접두사이면 return
        // 접두사가 아니면 go
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
            // 접두사 아님, 조건을 만족함
            if (tgt_node->is_leaf)
            {
                // 새로운 node 초기화
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

        if (!node->is_end) // 우측 트리
        {
            r_depth = find_max_depth(node->right, depth);
        }

        if (node->is_leaf) // 끝
        {
            return depth;
        }
        else // 좌측 트리
        {
            l_depth = find_max_depth(node->left, depth + 1);
        }

        return l_depth > r_depth ? l_depth : r_depth; // 종합
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