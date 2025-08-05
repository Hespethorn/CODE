#include <iostream>
#include <cassert>
using namespace std;
class Stack {
private:
    static const int MAX_SIZE = 3;
    int arr[MAX_SIZE];
    int topIndex;
public:
	Stack (): topIndex(-1) {}
    bool empty(){
        return topIndex == -1;
    }	//判断栈是否为空
    bool full(){
        return topIndex == MAX_SIZE - 1;
    }	//判断栈是否已满
    void push(int value){
        if(!full()){
            arr[++ topIndex] = value;
        }else{
            cerr << "Stack overflow_error" <<endl;
        }
    } //元素入栈
    void pop(){
        if(!empty()){
            -- topIndex;
        }else{
            cerr << "Stack underflow_error" << endl;
        }
    }     //元素出栈
    int  top(){
        if(!empty()){
            return arr[topIndex];
        }else{
            cerr << "Stack is empty" << endl;
            return -1;
        }
    }		//获取栈顶元素
};
void test(){
    Stack stack;

    //测试空
    assert(stack.empty() == true);
    assert(stack.full() == false);

    stack.push(1);
    assert(stack.top() == 1);
    assert(stack.empty() == false);
    stack.push(5);
    stack.push(2);
    assert(stack.full() == true);
    stack.push(5);
    assert(stack.top() == 2);
    stack.pop();
    assert(stack.top() == 5);
    stack.pop();
    stack.pop();
    assert(stack.empty() == true);
}
int main(int argc, char * argv[]){
    test();
    cout << "All tests passed successfully." << endl;
    return 0;
}

