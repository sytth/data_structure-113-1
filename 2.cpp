#include <iostream>
#include <cstdlib>

using namespace std;

template<class T>
class Memory
{
private:
    T *p;
    int rows,cols;

public:
    Memory(int r, int c) : rows(r) ,cols(c){
        p = new T[rows*cols];
    }

    ~Memory(){
        delete[] p;
    }

    T& operator()(int row, int col) {
        return p[row * cols + col];
    }
    
    void memory_address() const{
        for(int j = 0;j < rows;j ++){
            for(int k = 0;k < cols;k ++){
                cout << (void*)(&p[j * cols + k]) << " ";
            }
        }
    }
};


int main()
{
    Memory<int> array(5, 10);

    int j, k;
    for(j = 0;j < 5;j ++){
        for(k = 0;k < 10;k ++){
            array(j,k) = j * 10 + k;
        }
    }

    array.memory_address();

    return 0;
}
