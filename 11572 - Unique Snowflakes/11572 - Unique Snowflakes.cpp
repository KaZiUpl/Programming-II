#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main()
{
    int number_of_cases,
        number_of_snowflakes;
    int snowflake_number;
    int biggest_package;


    cin>>number_of_cases;
    while(number_of_cases--)
    {
        cin>>number_of_snowflakes;
        set<int> snowflakes_package;
        vector<int> snowflakes;
        biggest_package = 0;

        for(int i=0; i<number_of_snowflakes ; i++)
        {
            cin>>snowflake_number;
            snowflakes.push_back(snowflake_number);
        }

        int start_index = 0,
            end_index = 0;

        while(end_index < number_of_snowflakes)
        {
            // adding as long as snowflakes are unique
            while(end_index < number_of_snowflakes && !snowflakes_package.count(snowflakes[end_index]))
            {
                snowflakes_package.insert(snowflakes[end_index]);
                end_index++;
            }
            // checking if package is bigger than the biggest found
            if(end_index - start_index > biggest_package)
            {
                biggest_package = end_index - start_index;
            }

            // deleting snowflake that is not unique
            snowflakes_package.erase(snowflakes[start_index]);
            // moving start index forward and praying that now snowflake will be unique
            start_index++;
        }

        cout<<biggest_package<<endl;
    }


    return 0;
}
