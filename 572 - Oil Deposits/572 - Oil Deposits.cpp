#include<iostream>
#include<vector>

using namespace std;

void drain_pocket(int y, int x, vector<vector<char> > &oil_field)
{
    oil_field[y][x] = '*';
    // upper
    if(y-1 >= 0)
    {
        if(x-1 > 0 && oil_field[y-1][x-1]=='@') drain_pocket(y-1,x-1,oil_field);
        if(oil_field[y-1][x]=='@') drain_pocket(y-1,x,oil_field);
        if(x+1 < oil_field[0].size() && oil_field[y-1][x+1]=='@') drain_pocket(y-1,x,oil_field);
    }

    // smae level
    if(x-1 > 0 && oil_field[y][x-1]=='@') drain_pocket(y,x-1,oil_field);
    if(x+1 < oil_field[0].size() && oil_field[y][x+1]=='@') drain_pocket(y,x+1,oil_field);

    // lower
    if(y+1 < oil_field.size())
    {
        if(x-1 > 0 && oil_field[y+1][x-1]=='@') drain_pocket(y+1,x-1,oil_field);
        if(oil_field[y+1][x]=='@') drain_pocket(y+1,x,oil_field);
        if(x+1 < oil_field[0].size() && oil_field[y+1][x+1]=='@') drain_pocket(y+1,x+1,oil_field);
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
void flag_pocket(int y, int x, vector<vector<char> > &oil_field)
{
    if(oil_field[y][x] == '*') return;
    oil_field[y][x] = '#';
    cout<<"KOLEJNE WYWOLANIE "<<y<<" "<<x<<endl;
    for(int i=0;i<oil_field.size();i++)
    {
        for(int j=0;j<oil_field[0].size();j++)
        {
            cout<<oil_field[i][j];
        }
        cout<<endl;
    }


    bool flag = false;
    // upper
    if(y-1 >= 0)
    {
        if(x-1 > 0 && oil_field[y-1][x-1]=='@') flag = true;
        if(oil_field[y-1][x]=='@') flag = true;
        if(x+1 < oil_field[0].size() && oil_field[y-1][x+1]=='@') flag = true;
        else {cout<<"ASDSADSADSADSADSAD"<<endl;}
    }

    // smae level
    if(x-1 > 0 && oil_field[y][x-1]=='@') flag = true;
    if(x+1 < oil_field[0].size() && oil_field[y][x+1]=='@') flag = true;

    // lower
    if(y+1 < oil_field.size())
    {
        if(x-1 >= 0 && oil_field[y+1][x-1]=='@') flag = true;
        if(oil_field[y+1][x]=='@') flag = true;
        if(x+1 < oil_field[0].size() && oil_field[y+1][x+1]=='@') flag = true;
    }
    if(flag == false)
    {
        cout<<"WYCHODZE PRZEDWCZESNIE"<<endl;
        return;
    }

    if(y-1 >= 0)
    {
        if(x-1 > 0 && oil_field[y-1][x-1]=='@') flag_pocket(y-1,x-1,oil_field);
        if(oil_field[y-1][x]=='@' && oil_field[y-1][x]!='*') flag_pocket(y-1,x,oil_field);
        if(x+1 < oil_field[0].size() && oil_field[y-1][x+1]=='@') flag_pocket(y-1,x,oil_field);
    }

    // smae level
    if(x-1 >= 0 && oil_field[y][x-1]=='@') flag_pocket(y,x-1,oil_field);
    if(x+1 < oil_field[0].size() && oil_field[y][x+1]=='@') flag_pocket(y,x+1,oil_field);

    // lower
    if(y+1 < oil_field.size())
    {
        if(x-1 > 0 && oil_field[y+1][x-1]=='@') flag_pocket(y+1,x-1,oil_field);
        if(oil_field[y+1][x]=='@' && oil_field[y+1][x]!='*') flag_pocket(y+1,x,oil_field);
        if(x+1 < oil_field[0].size() && oil_field[y+1][x+1]=='@') flag_pocket(y+1,x+1,oil_field);
    }




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


        flag_pocket(4,4,oil_field);

        /*
        int x=-1,y=-1;
        do
        {
            x = -1;
            for(int i=0;i<m;i++)
            {
                for(int j=0;j<n;j++)
                {
                    if(oil_field[i][j] == '@')
                    {
                        y = i;
                        x = j;
                        break;
                    }
                }
            }
            if(x != -1)
            {
                cout<<"Wywoluje dla: "<<y<<" "<<x<<endl;
                flag_pocket(y,x,oil_field);
                number_of_pockets++;
            }



        }while(x != -1);

        cout<<number_of_pockets<<endl;
        */
        cin>>m;
    }


    return 0;
}
