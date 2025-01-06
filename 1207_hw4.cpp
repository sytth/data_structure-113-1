#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

// 計算 vector 中所有元素的總和
template <typename T>
T sum(const vector<T>& v) {
    T total = T();
    for (auto it = v.begin(); it != v.end(); ++it) {
        total += *it;
    }
    return total;
}

int main() {
    vector<int> v1 = {1, 2, 3, 4, 5};
    cout << "Sum of v1: " << sum(v1) << endl;

    vector<double> v2 = {1.1, 2.2, 3.3, 4.4, 5.5};
    cout << "Sum of v2: " << sum(v2) << endl;
    vector<int> v3 = {};
    cout << "Sum of v3: " << sum(v3) << endl;

    vector<float> v4 = {-1.0f, 2.5f, -3.5f, 4.0f};
    cout << "Sum of v4: " << sum(v4) << endl;

    return 0;
}
