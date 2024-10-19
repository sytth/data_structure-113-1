#include <iostream>
using namespace std;

class A {
    public:
        int x;
        A(): x(0){};
};
class B : public A {
    public:
        int x;
        B(): x(0){};
};
class C : public B {
    public:
        int x;
        C(): x(0){};

        void set_A_x(){
            A::x = 20;
            cout << "A_x=" <<A::x << endl;
        }
};


int main(){
    C number;
    number.set_A_x();

    return 0;
}
