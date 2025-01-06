#include <iostream>
#include <stdexcept>

using namespace std;

// StackEmpty
class StackEmpty : public runtime_error {
public:
    StackEmpty(const string& err) : runtime_error(err) {}
};

template <typename T>
struct Node {
    T data;
    Node* next;
    
    Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
};

// Singly linked list
template <typename T>
class SLinkedList {
public:
    SLinkedList() : head(nullptr) {}
    ~SLinkedList() { while (!empty()) removeFront(); }
    
    bool empty() const { return head == nullptr; }
    
    const T& front() const { return head->data; }
    
    void addFront(const T& e) {
        Node<T>* v = new Node<T>(e, head);
        head = v;
    }
    
    void removeFront() {
        Node<T>* old = head;
        head = old->next;
        delete old;
    }

private:
    Node<T>* head;
};

template <typename T>
class LinkedStack {
public:
    LinkedStack() : S(), n(0) {}  // 建構子，初始化stack為空

    int size() const {   // stack的大小
        return n;
    }  
    
    bool empty() const {   // 檢查stack是否為空
        return n == 0;
    }
    
    const T& top() const throw(StackEmpty) {  // 返回stack頂部的元素
        if (empty())
            throw StackEmpty("stack is empty");
        return S.front();
    }
    
    void push(const T& e) {  // 將元素推入stack
        S.addFront(e);
        ++n;
    }
    
    void pop() throw(StackEmpty) {  // 移除stack頂部的元素
        if (empty())
            throw StackEmpty("stack is empty");
        S.removeFront();
        --n;
    }

private:
    SLinkedList<T> S;
    int n;             // 元素個數
};

int main() {
    try {
        LinkedStack<int> stack;
        
        stack.push(10);
        stack.push(20);
        stack.push(30);
        
        cout << "top: " << stack.top() << endl;
        cout << "count: " << stack.size() << endl;
        
        stack.pop();
        cout << "top: " << stack.top() << endl;
        cout << "count: " << stack.size() << endl;
        
        stack.pop();
        stack.pop();
        
        cout << "stack empty: " << boolalpha << stack.empty() << endl;
        
        stack.pop();
    } catch (const StackEmpty& e) {
        cerr << "error: " << e.what() << endl;
    }

    return 0;
}
