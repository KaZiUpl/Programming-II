#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return abs(a);
    else
        return gcd(abs(b), abs(a % b));
}
int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}

template <typename T>
class Matrix
{
  protected:
    int rows,
        columns;
    vector<vector<T> > fields;

  public:
    Matrix(){};
    Matrix(int, int);
    void interchange_rows(int, int);
    void interchange_cols(int, int);
    void multiply_row(int,int);
    void divide_row(int,int);
    void add_row_a_to_row_b(int,int,int);
    void transpose();
    void increment();
    void decrement();

    friend istream &operator>>(istream &input, Matrix<T> &matrix)
    {
        for (int i = 0; i < matrix.rows; i++)
        {
            for (int j = 0; j < matrix.columns; j++)
            {
                cin >> matrix.fields[i][j];
            }
        }
        return input;
    }
    friend ostream &operator<<(ostream &output, const Matrix<T> &matrix)
    {
        for (int i = 0; i < matrix.rows; i++)
        {
            for (int j = 0; j < matrix.columns; j++)
            {
                cout << matrix.fields[i][j] << " ";
            }
            cout << endl;
        }
        return output;
    }
};
template <typename T>
Matrix<T>::Matrix(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
    fields = vector<vector<T> >(rows, vector<T>(columns));
}
template <typename T>
void Matrix<T>::interchange_rows(int row_a, int row_b)
{
    row_a--;
    row_b--;
    swap(fields[row_a], fields[row_b]);
}
template <typename T>
void Matrix<T>::interchange_cols(int col_a, int col_b)
{
    col_a--;
    col_b--;
    for (int i = 0; i < fields.size(); i++)
    {
        swap(fields[i][col_a], fields[i][col_b]);
    }
}
template <typename T>
void Matrix<T>::multiply_row(int row_num,int scalar)
{
    row_num--;
    for(int i=0;i<columns;i++)
    {
        fields[row_num][i] = scalar * fields[row_num][i];
    }
}
template <typename T>
void Matrix<T>::divide_row(int row_num,int scalar)
{
    row_num--;
    for(int i=0;i<columns;i++)
    {
        fields[row_num][i] = fields[row_num][i]/scalar;
    }
}
template <typename T>
void Matrix<T>::add_row_a_to_row_b(int row_a,int row_b, int scalar)
{
    row_a--;
    row_b--;
    for(int i=0;i<columns;i++)
    {
        fields[row_b][i] += scalar*fields[row_a][i];
    }
}

template <typename T>
void Matrix<T>::transpose()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = i; j < columns; j++)
        {
            swap(fields[i][j], fields[j][i]);
        }
    }
}
template <typename T>
void Matrix<T>::increment()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            fields[i][j] = (fields[i][j] + 1) % 10;
        }
    }
}
template <typename T>
void Matrix<T>::decrement()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            fields[i][j] = (fields[i][j] - 1);
            if (fields[i][j] < 0)
                fields[i][j] += 10;
        }
    }
}

template <typename T>
class Square_matrix : public Matrix<T>
{
    private:
    int gcd_of_row(int);
    int lcm_of_column(int);
  public:
    Square_matrix(){};
    Square_matrix(int);
    int determinant();



    friend int main();
};

template <typename T>
Square_matrix<T>::Square_matrix(int size_of_matrix)
{
    this->rows = size_of_matrix;
    this->columns = size_of_matrix;
    this->fields = vector<vector<T> >(size_of_matrix, vector<T>(size_of_matrix));
}

template <typename T>
int Square_matrix<T>::gcd_of_row(int row_num)
{
    row_num--;
    if(this->rows == 1) return this->fields[row_num][0];

    int result = gcd(this->fields[row_num][0],this->fields[row_num][1]);

    if(this->rows == 2) return result;

    for(int i=2;i<this->columns;i++)
    {
        result = gcd(result,this->fields[row_num][i]);
    }
    return result;
}
template <typename T>
int Square_matrix<T>::lcm_of_column(int col_num)
{
    col_num--;
    if(this->columns == 1) return this->fields[0][0];

    int result = lcm(this->fields[0][col_num],this->fields[1][col_num]);

    if(this->columns == 2) return result;

    for(int i=2;i<this->rows;i++)
    {
        result = lcm(result,this->fields[i][col_num]);
    }

    return result;
}

template <typename T>
Square_matrix<T>::determinant()
{
    int scalar; // variable for storing a multiplying a determinant
}

int main()
{
    int size_of_matrix;
    cin >> size_of_matrix;
    while (size_of_matrix > 0)
    {
        Square_matrix<int> matrix(size_of_matrix);
        cin >> matrix;

        cout << matrix;

        cout << matrix.gcd_of_row(1)<<endl;
        cout << matrix.lcm_of_column(1)<<endl;



        cin >> size_of_matrix;
    }
    if (size_of_matrix == 0)
    {
        cout << "*";
    }
    return 0;
}
