#include<iostream>
#include<cstdlib>
using namespace std;

int fcmp(const void* elem1 , const void* elem2);

int main()
{
    int a[5] = {98 , 55 , 47 , 232 , 92};

    for(int i = 0 ; i < 10 ; i++)
    {
        cout << a[i] << " ";
    }

    qsort(a , sizeof(a)/sizeof(int) , sizeof(int) , fcmp);
}

int fcmp(const void* elem1 , const void* elem2)
{
    const int * i1 = (const int *)elem1;
    const int * i2 = (const int *)elem2;

    if(*i1 < *i2)
    {
        return -1;
    }
    else if(*i1 > *i2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
