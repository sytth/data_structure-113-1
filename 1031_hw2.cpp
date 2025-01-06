#include <iostream>
using namespace std;

/*雙向鏈結串列 (Doubly Linked List)*/

template<typename T>
class DNode {
public:
    T data;        // 節點的數值
    DNode* prev;   // 指向前一個節點的指標
    DNode* next;   // 指向下一個節點的指標

    DNode(const T& elem) : data(elem), prev(nullptr), next(nullptr) {}
};

template<typename T>
class DLinkedList {
public:
    // 建構子
    DLinkedList() {
        header = new DNode<T>(T());  // 頭節點，不儲存資料
        trailer = new DNode<T>(T()); // 尾節點，不儲存資料
        header->next = trailer; // 頭節點的下一個是尾節點
        trailer->prev = header; // 尾節點的前一個是頭節點
    }

    // 解構子
    ~DLinkedList() {
        while (!empty()) removeFront(); // 刪除所有節點
        delete header;  // 釋放頭節點
        delete trailer; // 釋放尾節點
    }

    // 判斷鏈結串列是否為空
    bool empty() const {
        return (header->next == trailer); // 如果頭節點的下一個是尾節點，則表示為空
    }

    // 取得鏈結串列的前端元素
    const T& front() const {
        return header->next->data; // 返回頭節點之後的第一個節點的資料
    }

    // 取得鏈結串列的尾端元素
    const T& back() const {
        return trailer->prev->data; // 返回尾節點之前的最後一個節點的資料
    }

    // 在前端新增節點
    void addFront(const T& e) {
        add(header->next, e); // 在頭節點之後的節點之前插入新節點
    }

    // 在尾端新增節點
    void addBack(const T& e) {
        add(trailer, e); // 在尾節點之前插入新節點
    }

    // 刪除前端節點
    void removeFront() {
        if (!empty()) remove(header->next); // 刪除頭節點之後的第一個節點
    }

    // 刪除尾端節點
    void removeBack() {
        if (!empty()) remove(trailer->prev); // 刪除尾節點之前的最後一個節點
    }

private:
    DNode<T>* header;      // 頭節點指標
    DNode<T>* trailer;     // 尾節點指標

    // 在指定節點之前新增節點
    void add(DNode<T>* v, const T& e) {
        DNode<T>* u = new DNode<T>(e); 
        u->next = v;
        u->prev = v->prev;
        v->prev->next = u;
        v->prev = u;
    }

    // 刪除指定節點
    void remove(DNode<T>* v) {
        DNode<T>* u = v->prev;
        DNode<T>* w = v->next;
        u->next = w;
        w->prev = u;
        delete v;
    }
};

int main() {
    DLinkedList<int> list;

    list.addFront(10);
    list.addFront(20);
    list.addBack(30);
    list.addBack(40);
    list.addBack(50);
    
    cout << "front: " << list.front() << endl;
    cout << "back: " << list.back() << endl;
    list.removeFront();
    list.removeBack();

    cout << "front: " << list.front() << endl;

    return 0;
}
