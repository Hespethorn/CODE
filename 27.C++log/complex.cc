#include <iostream>
using namespace std;
/* 利用运算符重载，使Complex对象能够进行+、+=、前置++、后置++操作（对坐标进行计算） */
class Complex{
private:
    double real;
    double imag;
public:
    Complex(double ireal, double iimag):real(ireal),imag(iimag){};
    double getreal() const { return real; }
    double getimag() const { return imag; }
    Complex operator+(const Complex & other){
        return Complex(real + other.getreal(), imag + other.getimag());
    }
    Complex operator-(const Complex & other){
        return Complex(real - other.getreal(), imag - other.getimag());
    }
    Complex & operator+=(const Complex & other){
        real += other.getreal();
        imag += other.getimag();
        return *this;
    }
    Complex & operator-=(const Complex & other){
        real -= other.getreal();
        imag -= other.getimag();
        return *this;
    }
    Complex & operator++(){
        ++real;
        ++imag;
        return *this;
    }
    Complex & operator--(){
        --real;
        --imag;
        return *this;
    }
    friend
        ostream & operator<<(ostream& os, const Complex& c){
            os << "(" << c.getreal() << "+" << c.getimag() << "i )";
            return os;
        }
};
int main(int argc, char * argv[]){
    Complex c1(2,3);
    Complex c2(5,5);
    cout << "c1" << c1 << "c2" << c2 << endl;
    cout << "++c1" << ++c1 << endl;
    cout << "--c1" << --c1 << endl;
    Complex c3 = c1 + c2;
    cout << "c1 + c2" << c3 << endl;
    cout << "c3 - c1" << c3 - c1 << endl;
    c3 -= c2;
    cout << "c3 -= c2" << c3 << endl;
    c3 += c2;
    cout << "c3 += c2" << c3 << endl;
    return 0;
}

