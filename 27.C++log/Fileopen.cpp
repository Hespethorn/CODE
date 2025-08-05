#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char * argv[]){
    string filepath;
    cout << "请输入文件路径" << endl;
    cin >> filepath;
    
    ifstream fil(filepath);
    if(!fil.is_open()){
        cerr << "error open " << filepath << endl;
        return -1;
    }
    string line;
    while(getline(fil, line)){
        cout << line << endl;
    }
    fil.close();
    return 0;
}

