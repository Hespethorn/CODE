#include <iostream>
#include <cstring>

class String {
public:
    // 默认构造函数
    String() : _pstr(new char[1]) {
        _pstr[0] = '\0';
    }

    // 带参数的构造函数
    String(const char *pstr) {
        if (pstr == nullptr) {
            _pstr = new char[1];
            _pstr[0] = '\0';
        } else {
            _pstr = new char[strlen(pstr) + 1];
            strcpy(_pstr, pstr);
        }
    }

    // 拷贝构造函数
    String(const String &rhs) {
        _pstr = new char[strlen(rhs._pstr) + 1];
        strcpy(_pstr, rhs._pstr);
    }

    // 赋值运算符重载
    String &operator=(const String &rhs) {
        if (this != &rhs) {
            delete[] _pstr;
            _pstr = new char[strlen(rhs._pstr) + 1];
            strcpy(_pstr, rhs._pstr);
        }
        return *this;
    }

    // 析构函数
    ~String(){
        delete [] _pstr;
    }

    // 打印字符串
    void print() const {
        std::cout << _pstr << std::endl;
    }

    // 获取字符串长度
    size_t length() const {
        return strlen(_pstr);
    }

    // 获取C风格字符串
    const char *c_str() const {
        return _pstr;
    }

private:
    char *_pstr;
};

int main() {
    String str1;
    str1.print(); // 输出空字符串

    String str2 = "Hello, world";
    str2.print(); // 输出 "Hello, world"

    String str3("wangdao");
    str3.print(); // 输出 "wangdao"

    String str4 = str3;
    str4.print(); // 输出 "wangdao"

    str4 = str2;
    str4.print(); // 输出 "Hello, world"

    return 0;
}
