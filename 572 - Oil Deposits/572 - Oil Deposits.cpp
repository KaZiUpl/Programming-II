#include<iostream>
#include<vector>

using namespace std;

bool drain_pocket(int x, int y, vector<vector<char> > &oil_field)
{
    if(oil_field[x][y] == '*') return false;
    else
    {
        oil_field[x][y] = '*';

        if(x-1 >= 0 && y-1 >= 0) drain_pocket(x-1, y-1, oil_field);

        if(x-1 >= 0) drain_pocket(x-1, y, oil_field);

        if(x-1 >= 0 && y+1 < oil_field[x].size()) drain_pocket(x-1, y+1, oil_field);

        if(y+1 < oil_field[x].size()) drain_pocket(x, y+1, oil_field);

        if(x+1 < oil_field.size() && y+1 < oil_field[x].size()) drain_pocket(x+1, y+1, oil_field);

        if(x+1 < oil_field.size()) drain_pocket(x+1, y, oil_field);

        if(x+1 < oil_field.size() && y-1 >= 0) drain_pocket(x+1, y-1, oil_field);

        if(y-1 >= 0) drain_pocket(x, y-1, oil_field);

        return true;
    }

    /*
    cout<<"KOLEJNE WYWOLANIE"<<endl;
    for(int i=0;i<oil_field.size();i++)
    {
        for(int j=0;j<oil_field[0].size();j++)
        {
            cout<<oil_field[i][j];
        }
        cout<<endl;
    }
    */
}

int main()
{
    int m,n;
    char pocket;
    int number_of_pockets;
    cin>>m;
    while(m != 0)
    {
        cin>>n;
        number_of_pockets = 0;
        vector<vector<char> > oil_field(m,vector<char>(n));
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                cin>>pocket;
                oil_field[i][j] = pocket;
            }
        }

        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(drain_pocket(i,j,oil_field))
                {
                    number_of_pockets++;
                }
            }
        }
        cout<<number_of_pockets<<endl;

        cin>>m;
    }


    return 0;
}
