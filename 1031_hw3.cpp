#include <iostream>
#include <stdexcept>
using namespace std;

/*循環鏈結串列 (Circular Linked List*/

template<typename T>
class DNode {
public:
    T data;        // 節點的數值
    DNode* next;   // 指向下一個節點的指標

    DNode(const T& elem) : data(elem), next(nullptr) {}
};

template<typename T>
class CircleList {
public:
    // 建構子
    CircleList() : cursor(nullptr) {}

    // 解構子
    ~CircleList() {
        while (!empty()) {
            removeFront();
        }
    }

    // 判斷鏈結串列是否為空
    bool empty() const {
        return cursor == nullptr;
    }

    // 取得鏈結串列的前端元素
    const T& front() const {
        if (empty()) {
            throw runtime_error("error, illegal operation");
        }
        return cursor->next->data;
    }

    // 取得鏈結串列的尾端元素
    const T& back() const {
        if (empty()) {
            throw runtime_error("error, illegal operation");
        }
        return cursor->data;
    }

    // 在前端新增節點
    void addFront(const T& e) {
        DNode<T>* newNode = new DNode<T>(e);
        if (empty()) {
            cursor = newNode;
            cursor->next = cursor; // 讓新節點指向自己，形成一個圓形結構
        } else {
            newNode->next = cursor->next;
            cursor->next = newNode;
        }
    }

    // 在尾端新增節點
    void addBack(const T& e) {
        addFront(e);    // 先將節點新增在前端
        cursor = cursor->next; // 然後將 cursor 向後移動，使新增的節點成為尾端
    }

    // 前移 cursor
    void advance() {
        if (empty()) {
            throw runtime_error("error, illegal operation");
        }
        cursor = cursor->next; // 將 cursor 向前移動
    }

    // 刪除前端節點
    void removeFront() {
        if (empty()) {
            throw runtime_error("error, illegal operation");
        }
        DNode<T>* oldNode = cursor->next;
        if (oldNode == cursor) {
            cursor = nullptr;
        } else {
            cursor->next = oldNode->next;
        }
        delete oldNode;
    }

    // 刪除尾端節點
    void removeBack() {
        if (empty()) {
            throw runtime_error("error, illegal operation");
        }
        if (cursor->next == cursor) {
            delete cursor;
            cursor = nullptr;
        }
        else {
            DNode<T>* prev = cursor;
            while (prev->next != cursor) {
                prev = prev->next;
            }
            prev->next = cursor->next;
            delete cursor;
            cursor = prev;
        }
    }

private:
    DNode<T>* cursor;
};

int main() {
    try {
        CircleList<int> clist;

        clist.addFront(10);
        clist.addFront(20);
        clist.addBack(30);
        clist.addBack(40);
        clist.addBack(50);

        // 顯示前端與尾端的元素
        cout << "front: " << clist.front() << endl;
        cout << "back: " << clist.back() << endl;

        // 前移 cursor
        clist.advance();
        cout << "after move: " << clist.front() << endl;

        // 刪除前端
        clist.removeFront();
        cout << "delete front: " << clist.front() << endl;

        // 刪除尾端
        clist.removeBack();
        clist.removeBack();
        cout << "delete back: " << clist.back() << endl;
        clist.removeFront();
        clist.removeFront();
        
        cout << "delete all: " << clist.empty() << endl;
        clist.removeFront(); // error
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
