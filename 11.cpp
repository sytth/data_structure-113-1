#include <iostream>
#include <string>

using namespace std;

template<class T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node *left, *right;
    };

    Node *root; // 根節點

    void inorder(Node *cur) {
        if(!cur)
            return;
        inorder(cur->left);        
        cout << cur->data << " ";
        inorder(cur->right);
    }

public:
    BinarySearchTree() : root(nullptr) {}  // 建構子，初始化根節點

    // 插入元素
    void insertElement(T d) {
        Node *newNode = new Node{d, nullptr, nullptr}; // 建立新節點
        if (root == nullptr) {
            root = newNode;  // 如果樹是空的，將新節點設為根
            return;
        }

        Node *cur = root;
        while (cur != nullptr) {
            if (d < cur->data) {
                if (cur->left == nullptr) { // 如果左子節點為空，插入左子節點
                    cur->left = newNode;
                    return;
                }
                cur = cur->left;  // 向左子樹移動
            }
            else {
                if (cur->right == nullptr) { // 如果右子節點為空，插入右子節點
                    cur->right = newNode;
                    return;
                }
                cur = cur->right;  // 向右子樹移動
            }
        }
    }

    void print() {
        inorder(root);
        cout << endl;
    }

    // 搜尋元素
    bool search(T d) {
        Node *cur = root;
        while (cur != nullptr) {
            if (d == cur->data)
                return true;  // 找到目標值
            else if (d < cur->data)
                cur = cur->left;   // 移動到左子樹
            else
                cur = cur->right;  // 移動到右子樹
        }
        return false;  // 沒有找到
    }
 
    // 計算樹的高度
    int height() {
        return height(root);  // 計算根節點的高度
    }

    // 計算節點的高度
    int height(Node *cur) {
        if (cur == nullptr)
            return 0;
        int leftHeight = height(cur->left);   // 計算左子樹高度
        int rightHeight = height(cur->right); // 計算右子樹高度
        return 1 + max(leftHeight, rightHeight); // 返回較大高度+1
    }

};

int main() {
    int data;
    string command;
    BinarySearchTree<int> *bst = new BinarySearchTree<int>();

    while(true) {
        cin >> command;
        if(command == "insert") {
            cin >> data;
            bst->insertElement(data);
        }
        else if(command == "search") {
            cin >> data;
            if(bst->search(data))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }
        else if(command == "height") {
            cout << bst->height() << endl;
        }
        else if(command == "print") {
            bst->print();
        }
        else if(command == "exit") {
            break;
        }
    }
}
