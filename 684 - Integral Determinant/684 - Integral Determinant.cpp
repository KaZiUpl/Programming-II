#include<iostream>
#include<vector>
#include<string>
using namespace std;

template <typename T>
class Matrix
{
protected:
    int rows,
        columns;
    vector<vector<T> > fields;
public:
    Matrix() {};
    Matrix(int,int);
    void interchange_rows(int,int);
    void interchange_cols(int,int);
    void transpose();
    void increment();
    void decrement();

    friend istream & operator>>(istream & input, Matrix<T> & matrix)
    {
        for(int i=0;i< matrix.fields.size();i++)
        {
            for(int j=0;j<matrix.fields[i].size();j++)
            {
                cin>>matrix.fields[i][j];
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
                cout<<matrix.fields[i][j]<<" ";
            }
            cout<<endl;
        }
        return output;
    }
};
template <typename T> Matrix<T>::Matrix(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
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


template <typename T>
class Square_matrix : public Matrix<T>
{
public:
    Square_matrix() {};
    Square_matrix(int);
    int determinant();
};

template <typename T> Square_matrix<T>::Square_matrix(int size_of_matrix)
{
    this->rows  = size_of_matrix;
    this->columns  = size_of_matrix;
    this->fields = vector<vector<T> >(size_of_matrix,vector<T>(size_of_matrix));
}

template <typename T> Square_matrix<T>::determinant()
{

}


int main()
{
    int size_of_matrix;
    cin>>size_of_matrix;
    while(size_of_matrix > 0)
    {
        Square_matrix <int> matrix(size_of_matrix);



        cin>>size_of_matrix;
    }
    if(size_of_matrix == 0)
    {
        cout<<"*";
    }
    return 0;
}
