#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class CircularArraySequence {
private:
    T* data;
    int capacity;
    int size;
    int frontIndex;
    int backIndex;

    // 動態擴展陣列大小
    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        
        // 將舊陣列中的元素按順序複製到新陣列
        for (int i = 0; i < size; ++i) {
            newData[i] = data[(frontIndex + i) % capacity];
        }
        
        delete[] data;
        data = newData;
        capacity = newCapacity;
        frontIndex = 0;
        backIndex = size;
    }

public:
    // 建構子
    CircularArraySequence(int initialCapacity = 10)
        : capacity(initialCapacity), size(0), frontIndex(0), backIndex(0) {
        data = new T[capacity];
    }

    // 解構子
    ~CircularArraySequence() {
        delete[] data;
    }

    // check序列是否為空
    bool empty() const {
        return size == 0;
    }

    // 獲取序列中元素的數量
    int getSize() const {
        return size;
    }

    // 獲取序列中某個位置的元素
    T& at(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[(frontIndex + index) % capacity];
    }

    // 插入元素
    void insert(int index, const T& value) {
        if (index < 0 || index > size) {
            throw out_of_range("Index out of range");
        }

        if (size == capacity) {
            resize();
        }

        if (index < size / 2) {
            frontIndex = (frontIndex - 1 + capacity) % capacity;
            for (int i = 0; i < index; ++i) {
                data[(frontIndex + i) % capacity] = data[(frontIndex + i + 1) % capacity];
            }
        } else {
            for (int i = size; i > index; --i) {
                data[(frontIndex + i) % capacity] = data[(frontIndex + i - 1) % capacity];
            }
            backIndex = (backIndex + 1) % capacity;
        }

        data[(frontIndex + index) % capacity] = value;
        ++size;
    }

    // 刪除序列中某個位置的元素
    void erase(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }

        if (index < size / 2) {
            for (int i = index; i > 0; --i) {
                data[(frontIndex + i) % capacity] = data[(frontIndex + i - 1) % capacity];
            }
            frontIndex = (frontIndex + 1) % capacity;
        } else {
            for (int i = index; i < size - 1; ++i) {
                data[(frontIndex + i) % capacity] = data[(frontIndex + i + 1) % capacity];
            }
            backIndex = (backIndex - 1 + capacity) % capacity;
        }

        --size;
    }

    // 在開頭插入元素
    void insertFront(const T& value) {
        insert(0, value);
    }

    // 在尾端插入元素
    void insertBack(const T& value) {
        insert(size, value);
    }

    // 刪除序列的第一個元素
    void eraseFront() {
        erase(0);
    }

    // 刪除序列的最後一個元素
    void eraseBack() {
        erase(size - 1);
    }
};

int main() {
    CircularArraySequence<int> seq;

    seq.insertBack(4);
    seq.insertBack(5);
    seq.insertFront(3);
    seq.insert(1, 6);

    cout << "sequence: ";
    for (int i = 0; i < seq.getSize(); ++i) {
        cout << seq.at(i) << " ";
    }
    cout << endl;

    seq.eraseFront();
    seq.eraseBack();

    cout << "sequence: ";
    for (int i = 0; i < seq.getSize(); ++i) {
        cout << seq.at(i) << " ";
    }
    cout << endl;

    return 0;
}
