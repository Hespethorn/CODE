#include <iostream>
using namespace std;

class Data
{
public:
    Data(int data):_data(data){};
    int getData() const{
        return _data;
    };
private:
    int _data;
};

class MiddleLayer
{
public:
    MiddleLayer(Data * p):_pdata(p){};
    ~MiddleLayer(){ 
        cout << "Data delete" << endl;
        delete _pdata; 
    }
    Data * getMiddleLayer() const{
        return _pdata;
    }
private:
    Data * _pdata;
};

class ThirdLayer
{
public:
    ThirdLayer(MiddleLayer * pm):_pml(pm){};
    MiddleLayer * getMiddleLayer () const {
        return _pml;
    }
private:
    MiddleLayer * _pml;
};

int main(int argc, char * argv[]){
    Data* pData = new Data(42);
    MiddleLayer middleLayer(pData);
    ThirdLayer thirdLayer(&middleLayer);

    cout << thirdLayer.getMiddleLayer()->getMiddleLayer()->getData() << endl;
    return 0;
}

