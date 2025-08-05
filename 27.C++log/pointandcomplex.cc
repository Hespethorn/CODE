#include <iostream>
using namespace std;

class Point {
public:
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

class Complex {
public:
    double real, imag;

    // 默认构造函数
    Complex(double _real = 0.0, double _imag = 0.0) : real(_real), imag(_imag) {}

    // 接受 Point 类型参数的构造函数
    Complex(const Point& pt) : real(pt.x), imag(pt.y) {}

    // 赋值运算符重载
    Complex& operator=(const Point& pt) {
        real = pt.x;
        imag = pt.y;
        return *this;
    }

    void print() const {
        std::cout << "Complex(" << real << ", " << imag << ")" << std::endl;
    }
};

int main() {
    Point pt(8, 9);
    Complex cx(4, 6);

    // 方式1: 使用构造函数进行隐式转换
    Complex cx1 = pt; // 调用 Complex(const Point&)
    cx1.print();

    // 方式2: 显式调用构造函数
    Complex cx2(pt); // 调用 Complex(const Point&)
    cx2.print();

    // 方式3: 使用赋值运算符重载
    cx = pt; // 调用 Complex& operator=(const Point&)
    cx.print();

    return 0;
}
