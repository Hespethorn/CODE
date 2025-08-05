#include <iostream>
using namespace std;
/* 利用运算符重载，使Point对象能够进行+、+=、前置++、后置++操作（对坐标进行计算） */
class Point{
private:
    int x;
    int y;
public:
    Point(int ix, int iy):x(ix),y(iy){};
    int getX() const { return x; }
    int getY() const { return y; }
    Point  operator+(const Point & other){
        return Point(x + other.getX(), y + other.getY());
    }
    Point & operator+=(const Point & other){
        x += other.getX();
        y += other.getY();
        return *this;
    }
    Point & operator++(){
        ++x;
        ++y;
        return *this;
    }
    Point operator++(int){
        Point temp(*this);
        ++(*this);
        return temp;
    }
    friend
        ostream & operator<<(ostream& os, const Point& p){
            os << "(" << p.getX() << " , " << p.getY() << ")";
            return os;
        }
};
int main(int argc, char * argv[]){
    Point p2(2,3);
    Point p3(7,5);
    cout << "p2" << p2 << endl;
    cout << "p2++" << p2++ << endl;
    cout << "++p2" << ++p2 << endl;
    cout << "p2 + p3" << p2 + p3<< endl;
    p2 += p3;
    cout << "p2 += p3" << p2 << endl;
    return 0;
}

