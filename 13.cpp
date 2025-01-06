#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template<class T>
class MaxHeap {
public:
    // 建構子：初始化一個空的堆
    MaxHeap() {}

    // 插入元素
    void insert(T value) {
        heap.push_back(value);  // 新元素加到堆的最後
        siftUp(heap.size() - 1);  // 保持最大堆的性質
    }

    // 移除元素後，將尾端元素變成根節點
    T extract() {
        if (heap.empty()) {
            throw runtime_error("stack is empty");
        }
        T rootValue = heap[0];  // 取出根元素
        heap[0] = heap.back();  // 將最後一個元素移到根的位置
        heap.pop_back();  // 刪除最後一個元素
        siftDown(0);
        return rootValue;
    }

    // 返回堆中元素的數量
    int count() {
        return heap.size();
    }

private:
    vector<T> heap; 

    // 插入新元素時，將此元素的位置往上調整，確保子節點不大於父節點
    void siftUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;  // 計算父節點的索引
            if (heap[index] > heap[parentIndex]) {
                swap(heap[index], heap[parentIndex]);  // 如果子節點比父節點大，交換位置
                index = parentIndex;  // 繼續向上檢查
            }
            else {
                break;  // 當不需要交換時，停止
            }
        }
    }

    // 移除根節點後，把最後一個節點拿上來當根節點，再往下調整，確保父節點不小於子節點
    void siftDown(int index) {
        int size = heap.size();
        while (index < size) {
            int leftChild = 2 * index + 1;  // 左子節點的索引
            int rightChild = 2 * index + 2;  // 右子節點的索引
            int largest = index;

            // 比較左子節點和父節點
            if (leftChild < size && heap[leftChild] > heap[largest]) {
                largest = leftChild;
            }

            // 比較右子節點和目前最大的節點
            if (rightChild < size && heap[rightChild] > heap[largest]) {
                largest = rightChild;
            }

            // 如果父節點比子節點大，break
            if (largest == index) {
                break;
            }

            // 交換父節點和最大的子節點
            swap(heap[index], heap[largest]);
            index = largest;  // 繼續向下檢查
        }
    }
};

/*
int main() {
    MaxHeap<int> maxHeap;
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(5);
    maxHeap.insert(30);
    
    cout << "count: " << maxHeap.count() << endl;
    
    cout << "max: " << maxHeap.extract() << endl;
    cout << "max: " << maxHeap.extract() << endl;
    
    cout << "count: " << maxHeap.count() << endl;

    return 0;
}
*/