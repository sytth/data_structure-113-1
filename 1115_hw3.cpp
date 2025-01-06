#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Queue {
public:
    Queue(int capacity = 10) : cap(capacity), n(0), frontIndex(0), backIndex(0) {
        queue = new T[cap];  // 動態分配陣列
    }

    ~Queue() {
        delete[] queue;  // 釋放動態分配的記憶體
    }

    bool empty() const {
        return n == 0;
    }

    bool full() const {
        return n == cap;
    }

    int size() const {
        return n;
    }

    int capacity() const {
        return cap;
    }

    void enqueue(const T& e) {
        if (full()) {
            throw overflow_error("Queue is full");
        }
        queue[backIndex] = e;  // 在尾端插入元素
        backIndex = (backIndex + 1) % cap;  // 環狀處理
        ++n;
    }

    void dequeue() {
        if (empty()) {
            throw underflow_error("Queue is empty");
        }
        frontIndex = (frontIndex + 1) % cap;  // 環狀處理
        --n;
    }

    const T& front() const {
        if (empty()) {
            throw underflow_error("Queue is empty");
        }
        return queue[frontIndex];  // 返回前端元素
    }

    const T& back() const {
        if (empty()) {
            throw underflow_error("Queue is empty");
        }
        return queue[(backIndex - 1 + cap) % cap];  // 返回尾端元素，處理環狀情況
    }

private:
    T* queue;                     // 動態分配的陣列儲存queue的元素
    int cap;                      // queue的最大容量
    int n;                        // queue中的元素數量
    int frontIndex;               // 指向queue的前端元素
    int backIndex;                // 指向queue的尾端元素
};

int main() {
    try {
        Queue<int> q(5);
        
        // 插入元素
        q.enqueue(10);
        q.enqueue(20);
        q.enqueue(30);
        q.enqueue(40);
        q.enqueue(50);

        cout << "Queue size: " << q.size() << endl;
        cout << "Queue capacity: " << q.capacity() << endl;
        cout << "Front element: " << q.front() << endl;
        cout << "Back element: " << q.back() << endl;
        q.dequeue();
        cout << "Front element after dequeue: " << q.front() << endl;
        q.enqueue(60);
        cout << "Back element after enqueue: " << q.back() << endl;

        q.dequeue();
        q.dequeue();
        q.dequeue();
        q.dequeue();
        q.dequeue();
        cout << "Queue empty: " << boolalpha << q.empty() << endl;

        q.dequeue();
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
