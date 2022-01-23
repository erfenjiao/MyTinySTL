#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

template<typename T>
class print
{
    public:
        void operator() (const T& elem)
        {
            cout << elem << endl;
        }
};

int main()
{
    int ia[6] = {1 , 2 , 3 , 4 , 5 , 6 };
    //vector<int> v = {1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10};
    vector<int> iv(ia , ia+6);

    for_each(iv.begin() , iv.end() , print<int>());
    //最后一个参数作为临时对象传入for_each中，当for_each结束，这个临时对象也就结束了他的生命


}
