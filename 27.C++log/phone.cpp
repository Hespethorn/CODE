#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class PersonInfo
{
public:
    PersonInfo() = default;
    void setName(const string & name){
        m_name = name;
    };
    void setPhones(const vector<string> & phones){
        m_phones = phones;
    }
    void print() const{
        cout << "Name: " << m_name << " Phone: ";
        for (const auto& phone : m_phones) {
            std::cout << phone << " ";
        }
        cout << endl;
    }

private:
    // 人名
    string m_name;
    // 电话号码 一个人可能有多个
    vector<string> m_phones;
};

int main(int argc, char * argv[]){
    string filepath = "./phone.txt";
    ifstream fileStream(filepath);
    if(!fileStream.is_open()){
        cerr << "错误打开文件";
        return -1;
    }
    vector<PersonInfo> personInfos;
    string line;
    while(getline(fileStream, line)){
        istringstream iss(line);
        string name;
        iss >> name;
        PersonInfo person;
        person.setName(name);
        vector<string> phones;
        string phone;
        while(iss >> phone){
            phones.push_back(phone);
        }
        person.setPhones(phones);
        personInfos.push_back(person);
    }
    fileStream.close();
    for(const auto & person : personInfos){
        person.print();
    }
    return 0;
}

