#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int getIntegerInput(){
    int value;
    while(true){
        cout << "请输入整数字符" << endl;
        string input;
        getline(cin, input);
        istringstream iss(input);
        if(iss >> value && iss.eof()){
            return value;
        }else{
            cerr << "无用字符" << endl ;
        }
    }
}
int main() {
    int number = getIntegerInput();
    cout << "您输入的有效整数是: " << number << endl;
    return 0;
}
