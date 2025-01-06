#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

// Array
template<class T>
class BinaryTreeInArray {
private:
    T *array;             // 儲存二元樹節點的陣列
    int height;           // 樹的高度
    int numOfElement;     // 樹中節點的數量
    
    // 調整陣列大小
    void resize(int size) {
        T *temp = new T[numOfElement];  // 暫存原有的元素
        int j;
        // 複製到暫存陣列
        for(j = 0; j < numOfElement; j++)
            temp[j] = array[j];
        delete[] array;
        array = new T[static_cast<int>(pow(2, height + 1)) - 1];  // 增加陣列大小

        // 複製回原陣列
        for(j = 0; j < numOfElement; j++)
            array[j] = temp[j];
        height++;               // 現有高度增加
        delete[] temp;          // 釋放暫存陣列
    }

public:
    // 建構子
    BinaryTreeInArray() : array(nullptr), height(0), numOfElement(0) {}

    // 新增元素
    void addElementAsCompleteTree(T data) {
        int cap = pow(2, height) - 1;  // 計算當前層數可以容納的節點數量
        if(numOfElement + 1 > cap)
            resize((cap + 1) * 2 - 1); // 若容量不足，則擴展陣列
        array[numOfElement] = data;    // 新增元素到最後一個位置
        numOfElement++;                // 節點數量增加
    }

    // 中序 Inorder Traversal)：左->根->右
    void displayInorder(int index = 0) {
        if (index >= numOfElement)
            return;   
        displayInorder(2 * index + 1);       // 遍歷左子樹
        cout << array[index] << " ";         // 輸出根節點
        displayInorder(2 * index + 2);       // 遍歷右子樹
    }

    // 先序 Preorder Traversal：根->左->右
    void displayPreorder(int index = 0) {
        if (index >= numOfElement) 
            return;
        cout << array[index] << " ";         // 輸出根節點
        displayPreorder(2 * index + 1);      // 遍歷左子樹
        displayPreorder(2 * index + 2);      // 遍歷右子樹
    }

    // 後序 Postorder Traversal：左->右->根
    void displayPostorder(int index = 0) {
        if (index >= numOfElement)
            return;
        displayPostorder(2 * index + 1);     // 遍歷左子樹
        displayPostorder(2 * index + 2);     // 遍歷右子樹
        cout << array[index] << " ";         // 輸出根節點
    }
};

// Linked List
template<class T>
class BinaryTreeInLinkedList {
private:
    // 節點結構
    class TreeNode {
    public:
        TreeNode(T d) : data(d), left(nullptr), right(nullptr) {}  // 建構子
        TreeNode *left, *right;  // 左右子節點
        T data;                  // 節點儲存的資料
    };

    TreeNode *root;   // 樹的根節點
    int numOfElement; // 樹中節點的數量


public:
    // 建構子
    BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}

    // 新增元素
    void addElementAsCompleteTree(T data) {
        TreeNode* newNode = new TreeNode(data);  // 建立新節點
        if (root == nullptr) {
            root = newNode;  // 若根節點為空，則將新節點設為根節點
        }
        else {
            queue<TreeNode*> q;  // 使用queue來追蹤插入位置
            q.push(root);
            while (!q.empty()) {
                TreeNode* temp = q.front();
                q.pop();
                if (temp->left == nullptr) {     // 左子節點為空，插入新節點
                    temp->left = newNode;
                    break;
                }
                else {
                    q.push(temp->left);         // 將左子節點加入queue
                }
                if (temp->right == nullptr) {    // 右子節點為空，插入新節點
                    temp->right = newNode;
                    break;
                }
                else {
                    q.push(temp->right);        // 將右子節點加入queue
                }
            }
        }
        numOfElement++;  // 節點數量增加
    }

    // 中序遍歷 Inorder Traversal：左->根->右
    void displayInorder(TreeNode* node) {
        if (node == nullptr)
            return;
        displayInorder(node->left);  // 遍歷左子樹
        cout << node->data << " ";   // 輸出根節點
        displayInorder(node->right); // 遍歷右子樹
    }
    void displayInorder() {
        displayInorder(root);
    }

    // 先序遍歷 (Preorder Traversal)：根->左->右
    void displayPreorder(TreeNode* node) {
        if (node == nullptr)
            return;
        cout << node->data << " ";   // 輸出根節點
        displayPreorder(node->left); // 遍歷左子樹
        displayPreorder(node->right);// 遍歷右子樹
    }
    void displayPreorder() {
        displayPreorder(root);
    }

    // 後序遍歷 (Postorder Traversal)：左->右->根
    void displayPostorder(TreeNode* node) {
        if (node == nullptr)
            return;
        displayPostorder(node->left); // 遍歷左子樹
        displayPostorder(node->right);// 遍歷右子樹
        cout << node->data << " ";    // 輸出根節點
    }
    void displayPostorder() {
        displayPostorder(root);
    }
};

int main()
{
    BinaryTreeInArray<int> *b = new BinaryTreeInArray<int>;          // 用陣列儲存的二元樹
    BinaryTreeInLinkedList<int> *tree = new BinaryTreeInLinkedList<int>; // 用鏈結串列儲存的二元樹
    int j, n;
    cin >> n;  // 輸入節點數量
    for(j = 0; j < n; j++) {
        b->addElementAsCompleteTree(j);     // 將元素加入 array
        tree->addElementAsCompleteTree(j);  // 將元素加入 linked list
    }
    b->displayInorder();
    cout << endl;
    tree->displayInorder();
    cout << endl;
    b->displayPreorder();
    cout << endl;
    tree->displayPreorder();
    cout << endl;
    b->displayPostorder();
    cout << endl;
    tree->displayPostorder();
    cout << endl;
    return 0;
}
