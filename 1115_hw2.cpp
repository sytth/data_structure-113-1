#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque {
public:

    Deque(int capacity) : deque(new T[capacity]), front(0), back(0), n(0), cap(capacity) {}

    ~Deque() {
        delete[] deque;
    }

    // 檢查是否為空
    bool empty() const {
        return n == 0;
    }

    // 檢查是否已滿
    bool full() const {
        return n == cap;
    }

    // return元素數量
    int size() const {
        return n;
    }

    // return最大容量
    int capacity() const {
        return cap;
    }

    // return第一個元素
    const T& first() const {
        if (empty())
            throw runtime_error("Deque is empty");
        return deque[front];
    }

    // return最後一個元素
    const T& last() const {
        if (empty())
            throw runtime_error("Deque is empty");
        return deque[(back - 1 + cap) % cap];
    }

    // 在前端插入元素
    void insertFront(const T& e) {
        if (full())
            throw runtime_error("Deque is full");
        front = (front - 1 + cap) % cap;  // 繞回到前一個位置
        deque[front] = e;
        ++n;
    }

    // 在後端插入元素
    void insertBack(const T& e) {
        if (full()) throw runtime_error("Deque is full");
        deque[back] = e;
        back = (back + 1) % cap;  // 繞回到下一個位置
        ++n;
    }

    // 從前端移除元素
    void removeFront() {
        if (empty()) throw runtime_error("Deque is empty");
        front = (front + 1) % cap;
        --n;
    }

    // 從後端移除元素
    void removeBack() {
        if (empty()) throw runtime_error("Deque is empty");
        back = (back - 1 + cap) % cap;
        --n;
    }

private:
    T* deque;           // 儲存deque元素的陣列
    int front;          // 前端指標
    int back;           // 後端指標
    int n;              // 元素個數
    int cap;            // 固定的容量
};

int main() {
    try {
        Deque<int> dq(5);
        
        dq.insertFront(10);
        dq.insertFront(20);
        dq.insertFront(30);
        dq.insertBack(40);
        dq.insertBack(50);
        
        cout << "Deque size: " << dq.size() << endl;
        cout << "Deque capacity: " << dq.capacity() << endl;
        cout << "First element: " << dq.first() << endl;
        cout << "Last element: " << dq.last() << endl;
        
        dq.removeFront();
        cout << "First element after removeFront: " << dq.first() << endl;
        
        dq.removeBack();
        cout << "Last element after removeBack: " << dq.last() << endl;
        
        dq.removeFront();
        dq.removeFront();
        dq.removeBack();
        dq.removeBack();
        
        cout << "Deque empty: " << boolalpha << dq.empty() << endl;
        
        dq.removeFront();
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
