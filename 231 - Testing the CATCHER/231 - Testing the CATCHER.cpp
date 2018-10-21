#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int max_val(int first, int second)
{
    if(first > second) return first;
    else return second;
}


int main()
{
    int case_number = 1,
        height;
    vector<int> rocket_heights,rocket_heights_sorted;

    bool end_of_input = false,
        minus_one = false;

    while(!end_of_input)
    {
        cin>>height;
        if(height != -1 && minus_one)
        {
            minus_one = false;
            rocket_heights.clear();
        }
        if(!end_of_input && height != -1) rocket_heights.push_back(height);
        else if(height == -1 && minus_one) end_of_input = true;
        else if(height == -1)
        {
            minus_one = true;

            rocket_heights_sorted = rocket_heights;
            sort(rocket_heights_sorted.begin(),rocket_heights_sorted.end());
            reverse(rocket_heights_sorted.begin(),rocket_heights_sorted.end());

            vector<vector<int> > tab(rocket_heights.size()+1,vector<int>(rocket_heights_sorted.size()+1));

            for(int i=0;i<tab.size();i++)
            {
               tab[i][0] = 0;
               tab[0][i] = 0;
            }
            for(int i=1;i<tab.size();i++)
            {
                for(int j=1;j<tab[i].size();j++)
                {
                    if(rocket_heights[i-1] == rocket_heights_sorted[j-1]) tab[i][j] = tab[i-1][j-1]+1;
                    else tab[i][j] = max_val(tab[i][j-1],tab[i-1][j]);
                }
            }
            cout<<"Test #"<<case_number++<<":"<<endl;
            cout<<"  maximum possible interceptions: "<<tab[tab.size()-1][tab.size()-1]<<endl;
        }
    }

    return 0;
}
