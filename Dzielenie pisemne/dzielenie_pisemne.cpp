#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int pierwsza,druga;
    cin>> pierwsza >> druga;
    cout.width(14);
    cout<< fixed << setprecision(3) << double(pierwsza)/double(druga) << endl;
    cout<<"----------"<<endl;
    cout.width(10);
    cout<< setprecision(0) << hex << pierwsza << ":" << oct << druga << endl;

    return 0;
}
