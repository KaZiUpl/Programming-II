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
    friend ostream & operator<<(ostream & output, Matrix<T> & matrix)
    {
        for(int i=0;i< matrix.fields.size();i++)
        {
            for(int j=0;j<matrix.fields[i].size();j++)
            {
                cout<<matrix.fields[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};

template <typename T> Matrix<T>::Matrix(int rows)
{
    this->fields = vector<vector<T> >(rows,vector<T>(rows));
}

template <typename T> Matrix<T>::Matrix(int rows, int columns)
{
    this->fields = vector<vector<T> >(rows,vector<T>(columns));
}

template <typename T> void Matrix<T>::interchange_rows(int row_a, int row_b)
{
    swap(this->fields[row_a],this->fields[row_b]);
}
template <typename T> void Matrix<T>::interchange_cols(int col_a, int col_b)
{
    vector<T> help(this->fields[0].size());
}
template <typename T> void Matrix<T>::transpose()
{

}

int main()
{
    int number_of_cases,
        case_num=1;
    int matrix_size;

    cin>>number_of_cases;
    while(number_of_cases--)
    {
        cin>>matrix_size;

        Matrix<int> matrix(matrix_size);
        cin>>matrix;
        cout<<matrix;





        cout<<"Case #"<<case_num++<<endl;
    }
    return 0;
}
