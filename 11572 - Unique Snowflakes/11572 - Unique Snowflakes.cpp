#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void try_to_add_snowflake_to_package(int snowflake_number,vector<int>  &package)
{
    if(package.size() > 0 && (snowflake_number < package[0] || snowflake_number > package[package.size()-1]))
    {
        package.push_back(snowflake_number);
        return;
    }
    for(int i=0;i<package.size();i++)
    {
        if(package[i] == snowflake_number)
        {
            return;
        }
    }
    package.push_back(snowflake_number);
}

int main()
{
    int number_of_cases,
        number_of_snowflakes;
    int snowflake_number;


    cin>>number_of_cases;
    while(number_of_cases--)
    {
        cin>>number_of_snowflakes;
        vector<int> snowflakes_package;
        for(int i=0; i<number_of_snowflakes ; i++)
        {
            cin>>snowflake_number;

            try_to_add_snowflake_to_package(snowflake_number,snowflakes_package);

            sort(snowflakes_package.begin(),snowflakes_package.end());
        }
        cout<<snowflakes_package.size()<<endl;
    }


    return 0;
}
