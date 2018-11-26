#include<iostream>
#include<vector>
#include<string>
using namespace std;

template <typename T>
class Matrix
{
private:
    vector<vector<T> > fields;
public:
    Matrix();
    Matrix(int);
    Matrix(int,int);
    void interchange_rows(int,int);
    void interchange_cols(int,int);
    void transpose();
    void increment();
    void decrement();

    friend istream & operator>>(istream & input, Matrix<T> & matrix)
    {
        string row_string;
        for(int i=0;i< matrix.fields.size();i++)
        {
            cin>>row_string;
            for(int j=0;j<matrix.fields[i].size();j++)
            {
                matrix.fields[i][j] = (row_string[j] - 48);
            }
        }
        return input;
    }
    friend ostream & operator<<(ostream & output, const Matrix<T> & matrix)
    {
        for(int i=0;i< matrix.fields.size();i++)
        {
            for(int j=0;j<matrix.fields[i].size();j++)
            {
                cout<<matrix.fields[i][j];
            }
            cout<<endl;
        }
        return output;
    }
};

template <typename T> Matrix<T>::Matrix(int rows)
{
    fields = vector<vector<T> >(rows,vector<T>(rows));
}

template <typename T> Matrix<T>::Matrix(int rows, int columns)
{
    fields = vector<vector<T> >(rows,vector<T>(columns));
}

template <typename T> void Matrix<T>::interchange_rows(int row_a, int row_b)
{
    row_a--;
    row_b--;
    swap(fields[row_a],fields[row_b]);
}
template <typename T> void Matrix<T>::interchange_cols(int col_a, int col_b)
{
    col_a--;
    col_b--;
    for(int i=0;i<fields.size();i++)
    {
        swap(fields[i][col_a],fields[i][col_b]);
    }
}
template <typename T> void Matrix<T>::transpose()
{
    for(int i=0;i<fields.size();i++)
    {
        for(int j=i;j<fields[i].size();j++)
        {
            swap(fields[i][j],fields[j][i]);
        }
    }
}
template <typename T> void Matrix<T>::increment()
{
    for(int i=0;i<fields.size();i++)
    {
        for(int j=0;j<fields[i].size();j++)
        {
            fields[i][j] = (fields[i][j] + 1)%10;
        }
    }
}
template <typename T> void Matrix<T>::decrement()
{
    for(int i=0;i<fields.size();i++)
    {
        for(int j=0;j<fields[i].size();j++)
        {
            fields[i][j] = (fields[i][j] - 1);
            if(fields[i][j]<0) fields[i][j]+=10;
        }
    }
}

int main()
{
    int number_of_cases,
        case_num=1;
    int number_of_commands;
    int matrix_size;
    string command;
    int cmd_para_first,
        cmd_para_second;

    cin>>number_of_cases;
    while(number_of_cases--)
    {
        cin>>matrix_size;

        Matrix<int> matrix(matrix_size);
        cin>>matrix;
        cin>>number_of_commands;
        while(number_of_commands--)
        {
            cin>>command;
            if(command[0] == 'i')
            {
                matrix.increment();
            }
            else if(command[0] == 'd')
            {
                matrix.decrement();
            }
            else if(command[0] == 't')
            {
                matrix.transpose();
            }
            else if(command[0] == 'r')
            {
                cin>>cmd_para_first>>cmd_para_second;
                matrix.interchange_rows(cmd_para_first,cmd_para_second);
            }
            else
            {
                cin>>cmd_para_first>>cmd_para_second;
                matrix.interchange_cols(cmd_para_first,cmd_para_second);
            }
        }

        cout<<"Case #"<<case_num++<<endl;
        cout<<matrix<<endl;
    }
    return 0;
}
