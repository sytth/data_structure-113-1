#include <iostream>
using namespace std;

template <typename T>
class Sequence {
public:
    virtual int size() const = 0;
    virtual const T& at(int index) const = 0;

    int indexOfElement(const T& e) const {
        for (int i = 0; i < size(); ++i) {
            if (at(i) == e) {
                return i;
            }
        }
        return -1;
    }

    int positionOfElement(const T& e) const {
        int index = indexOfElement(e);
        if (index != -1) {
            return index + 1;
        }
        return -1;
    }
    virtual ~Sequence() {}
};

template <typename T>
class ArraySequence : public Sequence<T> {
private:
    T* data;
    int n;
public:
    ArraySequence(T* arr, int size) : data(arr), n(size) {}

    // 覆寫size()函式
    int size() const override {
        return n;
    }

    // 覆寫at()函式
    const T& at(int index) const override {
        if (index < 0 || index >= n) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
};

int main() {
    int arr[] = {3, 5, 7, 9, 5};
    ArraySequence<int> seq(arr, 5);

    cout << "Index of 5: " << seq.indexOfElement(5) << endl;
    cout << "Position of 5: " << seq.positionOfElement(5) << endl;
    cout << "Index of 8: " << seq.indexOfElement(8) << endl;
    cout << "Position of 8: " << seq.positionOfElement(8) << endl;

    return 0;
}
