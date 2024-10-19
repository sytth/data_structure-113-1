#include <iostream>
#include <cmath>
using namespace std;

class quadraticEq {
    private:
        double a,b,c;
    
    public:
        // Constructor
        quadraticEq(): a(0),b(0),c(0){}
        quadraticEq(double vul_a, double vul_b, double vul_c): a(vul_a), b(vul_b), c(vul_c){}
   
        // Overloading +
        quadraticEq operator+(const quadraticEq& eq) const {
            return quadraticEq(a + eq.a, b + eq.b, c + eq.c);
        }

        // Overloading -
        quadraticEq operator-(const quadraticEq& eq) const {
            return quadraticEq(a - eq.a, b - eq.b, c - eq.c);
        }

        // Overloading == (T or F)
        bool operator==(const quadraticEq& eq) const {
            return (a == eq.a && b == eq.b && c == eq.c);
        }

        // Overloading != (T or F)
        bool operator!=(const quadraticEq& eq) const {
            return !(*this == eq);
        }

        // Overloading cin
        friend istream& operator>>(istream& input, quadraticEq& eq) {
            input >> eq.a >> eq.b >> eq.c;
            return input;
        }

        // Overloading cout
        friend ostream& operator<<(ostream& output, const quadraticEq& eq) {
            if(eq.a != 0){
                output << eq.a << "x^2";
            }

            if(eq.b > 0 ){
                output << " + " << eq.b << "x";
            }
            else if (eq.b < 0){
                output << " " << eq.b << "x";
            }

            if(eq.c > 0 && (eq.a !=0 || eq.b !=0)){
                output << " + " << eq.c;
            }
            else if (eq.c < 0 || (eq.c > 0 && eq.a ==0 && eq.b ==0)){
                output << " " << eq.c;
            }
            
            return output;
        }

        // cout root
        void printf_root() const{
            double judge = b*b - 4*a*c;
            // 2 real roots
            if (judge > 0){
                double root1 = (-b + sqrt(judge)) / (2*a);
                double root2 = (-b - sqrt(judge)) / (2*a);
                cout << "Two distinct real roots: " << root1 << " and " << root2 << endl;
            }
            else if (judge == 0){
                double root = -b / (2*a);
                cout << "One repeated real root: " << root << endl;
            }
            else {
                double realpart = -b / (2*a);
                double complexpart = sqrt(-judge) / (2*a);
                cout << "Two complex roots: " << realpart << "+" << complexpart << "i and " << realpart << "-" << complexpart << "i" << endl;
            }
        }
};

int main(){
    quadraticEq eq1, eq2;

    cout << "Please cin a b c of eq1 and eq2" << endl;
    cin >> eq1 >> eq2;        // 輸入a、b、c

    quadraticEq sum = eq1 + eq2;
    cout << "sum : " << sum << endl;

    quadraticEq diff = eq1 - eq2;
    cout << "difference : " << diff << endl;

    cout << "test == : ";
    if (eq1 == eq2) {
        cout << "The equations are equal." << endl;
    } else {
        cout << "The equations are not equal." << endl;
    }

    cout << "test != : ";
    if (eq1 != eq2) {
        cout << "The equations are not equal." << endl;
    } else {
        cout << "The equations are equal." << endl;
    }

    cout << "Roots of eq1 : ";
    eq1.printf_root();

    cout << "Roors of eq2 : ";
    eq2.printf_root();

    return 0;
}


