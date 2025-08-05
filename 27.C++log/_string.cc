#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// string的构造
void test1()
{
//string(size_type count, char ch);//生成一个string对象，该对象包含count个ch字符
    string s6 { 95, 'a' };
    cout << "s6=" << s6 << endl;
    // 上下是有区别的 上面把97当作a来处理
    string s7 ( 97, 'a' );
    cout << "s7=" << s7 << endl;
//string(InputIt first, InputIt last);//以区间[first, last)内的字符创建一个string对象
//iterator ---> 迭代器
    // begin() 函数获取首位置的迭代器
    // auto自动推导类型
    auto itBegin = s7.begin();
    // 完整类型
    string::iterator itEnd = s7.end();
    
    string s8 { itBegin, itEnd };
    cout << "s8=" << s8 << endl;
}

void test2()
{
    string str { "abcdef" };
//      const CharT* data() const;
//  const CHarT* c_str() const; //获取出C++字符串保存的字符串内容，以C风格字符串作为返回值
    const char * pstr = str.c_str();
    cout << pstr << endl;

//  bool empty() const; //判空
    cout << str.empty() << endl;// false  
                                
//  size_type size() const;//获取字符数
//  size_type length() const;
    cout << "size:" << str.size() << endl;  

//  void push_back(CharT ch);  //字符串结尾追加字符
    str.push_back('g');
    cout << "str=" << str << endl;

//  //在字符串的末尾添加内容，返回修改后的字符串
//  basic_string& append(size_type count, CharT ch); //添加count个字符
    str.append(3,'x');
    cout << "str=" << str << endl;

//  basic_string& append(const basic_string& str);  //添加字符串
    string s1 { "hello" };
    str.append(s1);
    cout << "str=" << str << endl;

//  basic_string & append(const basic_string& str,  //从原字符串末尾添加str从pos位置的count个字符
//                       size_type pos,size_type count);
//  basic_string& append(const charT* s);      //添加C风格字符串
  
//  //查找子串
//  size_type find( const basic_string& str,
//  size_type pos = 0 ) const;  //从C++字符串的pos位开始查找C++字符串str
    int index = str.find("xxx");
    cout << "index:" << index << endl;

    int index2 = str.find("zzz");
    cout << "index2:" << index2 << endl;
//  size_type find( CharT ch, size_type pos = 0 ) const;      //从C++字符串的pos位开始查找字符ch
//  size_type find( const CharT* s, size_type pos, size_type count ) const;  //从C++字符串的pos位开始，去查找C字符串的前count个字符

    // 字符串的截取
    string s2 = str.substr(1,3);
    cout << "s2:" << s2 << endl;

    string s3 = str.substr(1);
    cout << "s3:" << s3 << endl;
    
}

void test3()
{
    string s1 { "ab" };
    string s2 { "cd" };
    string s3 = s1 + s2;
    cout << "s3=" << s3 << endl;
    string s4 = s3 + "hello";
    cout << "s4=" << s4 << endl;
}

void test4()
{
    string str { "abcdef" };
    // 遍历方式一: 通过下标访问运算符[]
    for(int i = 0; i < str.size(); ++i)
    {
        cout << str[i] << " ";
    }
    cout << endl;
    cout << "--------" << endl;
    // 通过string中的at(index)
    for(int i = 0; i < str.size(); ++i)
    {
        cout << str.at(i) << " ";
    }
    cout << endl;

    // 使用增强for循环进行遍历 (迭代)
    cout << "--------" << endl;
    for(char element : str)
    {
        cout << element << " ";
    }
    cout << endl;
    cout << "--------" << endl;
    // 在这里会把str中的字符copy一份
    // 如果不想copy操作 可以使用引用
    for(char & element : str)
    {
        element += 1;
    }
    cout << "修改后:" << endl;
    for(auto element : str)
    {
        cout << element << " ";
    }

}

void test5()
{
    string str {"abcd"};
    // 通过迭代器方式进行遍历操作
    auto itBegin = str.begin();
    for(;itBegin != str.end(); ++itBegin)
    {
        // 可以像指针一样进行解引用
        cout << *itBegin << " ";
    }
    cout << endl;
}

int main(int argc, char * argv[])
{
    test1();
    /* test2(); */
    /* test3(); */
    /* test4(); */
    /* test5(); */
    return 0;
}


