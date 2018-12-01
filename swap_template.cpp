#include <iostream>

using namespace std;

template <typename T, typename Y> void swop(T &first, Y &second)
{
    first -= second;
    second += first;
    first = second - first;
}

int main()
{
    int b;
    double a;
    while(cin>>a>>b)
    {
        swop(a,b);
        cout<<a<<" "<<b<<endl;
    }

    return 0;
}
