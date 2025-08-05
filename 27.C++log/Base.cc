#include <iostream>
using namespace std;
class Base{
private:
    int value;
public:
    Base(int val):value(val){};
    Base operator+(const Base & other){
        return Base(this->value + other.value);
    }
    bool operator==(int val){
        return this->value == val;
    }
};
int main(int argc, char * argv[]){
    int i=2;
    int j=7;

    Base x(i);
    Base y(j);
    cout << (x + y == j + i) << endl;
    return 0;
}

