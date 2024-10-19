#include <iostream>
#include <cmath>
using namespace std;

class quadraticEq {
private:
    double a, b, c; // Coefficients of the quadratic equation

public:
    // Default constructor
    quadraticEq() : a(0), b(0), c(0) {}

    // Parameterized constructor
    quadraticEq(double aVal, double bVal, double cVal) : a(aVal), b(bVal), c(cVal) {}

    // Overloading the + operator
    quadraticEq operator+(const quadraticEq& eq) const {
        return quadraticEq(a + eq.a, b + eq.b, c + eq.c);
    }

    // Overloading the - operator
    quadraticEq operator-(const quadraticEq& eq) const {
        return quadraticEq(a - eq.a, b - eq.b, c - eq.c);
    }

    // Overloading the == operator
    bool operator==(const quadraticEq& eq) const {
        return (a == eq.a && b == eq.b && c == eq.c);
    }

    // Overloading the != operator
    bool operator!=(const quadraticEq& eq) const {
        return !(*this == eq);
    }

    // Function to determine the type of roots and print them
    void printRoots() const {
        double discriminant = b * b - 4 * a * c;

        if (discriminant > 0) {
            double root1 = (-b + sqrt(discriminant)) / (2 * a);
            double root2 = (-b - sqrt(discriminant)) / (2 * a);
            cout << "Two distinct real roots: " << root1 << " and " << root2 << endl;
        } else if (discriminant == 0) {
            double root = -b / (2 * a);
            cout << "One repeated real root: " << root << endl;
        } else {
            double realPart = -b / (2 * a);
            double imaginaryPart = sqrt(-discriminant) / (2 * a);
            cout << "Two complex roots: " << realPart << " + " << imaginaryPart << "i and "
                 << realPart << " - " << imaginaryPart << "i" << endl;
        }
    }

    // Overloading the stream extraction operator >>
    friend istream& operator>>(istream& input, quadraticEq& eq) {
        cout << "Enter coefficients a, b, and c: ";
        input >> eq.a >> eq.b >> eq.c;
        return input;
    }

    // Overloading the stream insertion operator <<
    friend ostream& operator<<(ostream& output, const quadraticEq& eq) {
        output << eq.a << "x^2 + " << eq.b << "x + " << eq.c;
        return output;
    }
};

int main() {
    quadraticEq eq1, eq2;

    // Input two quadratic equations
    cout << "Enter the first quadratic equation coefficients:" << endl;
    cin >> eq1;
    cout << "Enter the second quadratic equation coefficients:" << endl;
    cin >> eq2;

    // Test operator +
    quadraticEq sum = eq1 + eq2;
    cout << "Sum of the two equations: " << sum << endl;

    // Test operator -
    quadraticEq diff = eq1 - eq2;
    cout << "Difference of the two equations: " << diff << endl;

    // Test operator ==
    if (eq1 == eq2) {
        cout << "The equations are equal." << endl;
    } else {
        cout << "The equations are not equal." << endl;
    }

    // Test operator !=
    if (eq1 != eq2) {
        cout << "The equations are not equal." << endl;
    } else {
        cout << "The equations are equal." << endl;
    }

    // Test printing the roots of eq1
    cout << "Roots of the first equation: " << endl;
    eq1.printRoots();

    // Test printing the roots of eq2
    cout << "Roots of the second equation: " << endl;
    eq2.printRoots();

    return 0;
}
