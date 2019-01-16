#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int find_god(int student,vector<int> &religions)
{
    if(student != religions[student])
    {
        religions[student] = find_god(religions[student],religions);
        return religions[student];
    }
    else
    {
        return student;
    }
}

bool is_it_the_same_god(int &student_a, int &student_b, vector<int> &religions)
{
    student_a = find_god(student_a,religions);
    student_b = find_god(student_b,religions);

    if(student_a != student_b)
    {
        religions[student_a] = student_b;
        return false;
    }
    else return true;

}

int main()
{
    int number_of_students,number_of_pairs;
    int case_number = 1;
    int number_of_religions;

    while(cin>>number_of_students>>number_of_pairs && (number_of_students || number_of_pairs))
    {
        number_of_religions = number_of_students;
        vector<int> religions(number_of_students+1);
        for(int i=1;i<number_of_students+1;i++) // for every student make then the 'god' of their religion
        {
            religions[i] = i;
        }

        for(int i=0;i<number_of_pairs;i++)
        {
            int a,b;
            cin>>a>>b;

            if(!is_it_the_same_god(a,b, religions))
            {
                number_of_religions--;
            }
        }

        cout<<"Case "<<case_number++<<": "<<number_of_religions<<endl;
    }
}
