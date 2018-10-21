#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int max_val(int first, int second)
{
    if(first > second) return first;
    else return second;
}

int main()
{
    int number_of_events,
        date_num;

    cin>>number_of_events;

    vector<int> main_pattern(number_of_events+1);

    int counter = 1;
    for(int i=1;i<number_of_events+1;i++)
    {
        cin>>date_num;
        main_pattern[date_num] = counter++;
    }

    while(cin>>date_num)
    {
        vector<int> student_pattern(number_of_events+1);
        student_pattern[date_num] = 1;

        counter = 2;
        for(int i=1;i<number_of_events;i++)
        {
            cin>>date_num;
            student_pattern[date_num] = counter++;
        }

        vector< vector<int> > tab(number_of_events+1,vector<int>(number_of_events+1));

        for(int i=0;i<tab.size();i++)
        {
            tab[i][0] = 0;
            tab[0][i] = 0;
        }
        for(int i=1;i<tab.size();i++)
        {
            for(int j=1;j<tab[i].size();j++)
                {
                    if(student_pattern[i] == main_pattern[j]) tab[i][j] = tab[i-1][j-1]+1;
                    else tab[i][j] = max_val(tab[i][j-1],tab[i-1][j]);
                }
        }
        cout<<tab[number_of_events][number_of_events]<<endl;
    }

    return 0;
}
