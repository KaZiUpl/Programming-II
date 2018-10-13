#include<iostream>
#include<string>
using namespace std;

int main()
{
    int number_of_cases,
        case_number = 1;
    int height,
        min_height = 51,
        max_height = 51;

    string case_text;



    cin>>number_of_cases;
    while(case_number <= number_of_cases)
    {
        char tab[102][52];
        for(int i=0;i<102;i++)
        {
            for(int j=0;j<52;j++)
            {
                tab[i][j] = NULL;
            }
        }
        min_height = 51,
        max_height = 51;

        cin>>case_text;
        height = 51;
        if(case_text[0] == 'R') tab[height][0] = '/';
        else if(case_text[0] == 'F') tab[height][0] = '\\';
        else if(case_text[0] == 'C') tab[height][0] = '_';

        for(int i=1;i<case_text.size();i++)
        {
            if(case_text[i-1] == 'R')
            {
                if(case_text[i] == 'C')
                {
                    height--;
                    tab[height][i] = '_';
                }
                else if(case_text[i] == 'R')
                {
                    height--;
                    tab[height][i] = '/';
                }
                else
                {
                    tab[height][i] = '\\';
                }
            }
            else if(case_text[i-1] == 'C')
            {
                if(case_text[i] == 'F')
                {
                    height++;
                    tab[height][i] = '\\';
                }
                else if(case_text[i] == 'C')
                {
                    tab[height][i] = '_';
                }
                else if(case_text[i] == 'R')
                {
                    tab[height][i] = '/';
                }
            }
            else
            {
                if(case_text[i] == 'F')
                {
                    height++;
                    tab[height][i] = '\\';
                }
                else if(case_text[i] == 'C')
                {
                    tab[height][i] = '_';
                }
                else if(case_text[i] == 'R')
                {
                    tab[height][i] = '/';
                }
            }

            if(height > min_height) min_height = height;
            else if(height < max_height) max_height = height;

        }
        for(int i=max_height ; i<=min_height;i++)
        {
            bool character = false;
            int j=52;
            while(character)
            {
                if(tab[i][j] == '/' || tab[i][j] == '_' || tab[i][j] == '\\')
                {
                    tab[i][j+1] = '\n';
                    character = true;
                }
                j--;
            }
            for(j;j>=0;j--)
            {
                if(!(tab[i][j] == '/' || tab[i][j] == '_' || tab[i][j] == '\\'))
                {
                    tab[i][j] = ' ';
                }
            }
        }
        cout<<"Case #"<<case_number<<":"<<endl;
        for(int i=max_height ; i<=min_height;i++)
        {
            cout<<"| ";
            int j;
            for(j=0;j<case_text.size();j++)
            {
                cout<<tab[i][j];
                if(tab[i][j] == '\n') break;
            }
            if(j==case_text.size()) cout<<endl;
        }
        cout<<"+-";
        for(int i=0;i<case_text.size()+1;i++)
        {
            cout<<"-";
        }
        cout<<endl;

        case_number++;

    }

    return 0;
}
