//
//  Matrix.h
//  Created by Swapnil Dhanwal on 13/06/2017.
//  Copyright © 2017 Swapnil Dhanwal. All rights reserved.
//

#ifndef Matrix_h
#define Matrix_h

#include <ostream>
#include <type_traits>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

template<typename t>
class Matrix
{
private:
    
public:
    
    int m;
    int n;
    t **array;
    
    //CONSTRUCTORS
    
    Matrix()
    {
        
        this->m = 0;
        this->n = 0;
        array = new t*[m];
        for (int i = 0; i < m; i++)
        {
            
            array[i] = new t[n];
            for (int j = 0; j < n; j++)
            {
                
                array[i][j] = t();
                
            }
                        
        }
        
    }
    
    Matrix(int m, int n)
    {
        
        this->m = m;
        this->n = n;
        array = new t*[m];
        for (int i = 0; i < m; i++)
        {
            
            array[i] = new t[n];
            for (int j = 0; j < n; j++)
            {
                
                array[i][j] = t();
                
            }
            
        }
        
    }
    
    Matrix(t **a)
    {
        
        int rows = sizeof(a)/sizeof(a[0]);
        int columns = sizeof(a[0])/sizeof(a[0][0]);
        m = rows;
        n = columns;
        array = new t*[m];
        for (int i = 0; i < m; i++)
        {
            
            array[i] = new t[n];
            for (int j = 0; j < n; j++)
            {
                
                array[i][j] = a[i][j];
                
            }
            
        }
        
    }
    
    Matrix(string filepath)
    {
        
        ifstream ifile;
        ifile.open(filepath);
        int rows = 0, columns = 0;
        char prev = ' ';
        try
        {
            
            while(!ifile.eof())
            {
                
                char c = ifile.get();
                if ((prev == ' ' && c == '\n') || (prev == ' ' && c == ' ') || (prev == ' ' && c == EOF))
                {
                    
                    throw 1;
                    
                }
                    
                if ((prev == c && prev == '\n') || (prev == ' ' && c == '\n'))
                {
                    
                    break;
                    
                }
                if (c == EOF)
                {
                    
                    if (rows == 0)
                    {
                        rows++;
                    }
                    break;
                    
                }
                else
                {
                    
                    if (c == ',')
                    {
                        
                        columns++;
                        
                    }
                    if (c == '\n')
                    {
                        
                        rows++;
                        
                    }
                    
                }
                prev = c;
                
            }
            columns = (columns)/rows + 1;
            ifile.close();
            
            this->m = rows;
            this->n = columns;
            array = new t*[m];
            for (int i = 0; i < m; i++)
            {
                
                array[i] = new t[n];
                for (int j = 0; j < n; j++)
                {
                    
                    array[i][j] = t();
                    
                }
                
            }
            
            ifile.open(filepath);
            prev = ' ';
            int i = 0, j = 0;
            string numString = "";
            while(!ifile.eof())
            {
                
                char c = ifile.get();
                if ((prev == c && prev == '\n') || (prev == ' ' && c == '\n'))
                {
                    
                    break;
                    
                }
                if (c == EOF)
                {
                    
                    break;
                    
                }
                else
                {
                    
                    if (c == ',')
                    {
                        
                        double num = stod(numString);
                        array[i][j] = num;
                        numString = "";
                        j = (j+1)%(columns);
                        
                    }
                    if (c == '\n')
                    {
                        
                        double num = stod(numString);
                        array[i][j] = num;
                        numString = "";
                        i = (i+1)%rows;
                        j = 0;
                        
                    }
                    else if (c != ' ' && c != ',')
                    {
                        
                        numString += c;
                        
                    }
                    
                }
                prev = c;
                
            }
            
        }
        catch (int e)
        {
            
            if (e == 1)
            {
             
                cout<<"Please remove trailing and leading spaces in your csv"<<"\n";
                
            }
            
        }
        
    }
    
    Matrix(vector<vector<t>> a)
    {
        
        try
        {
            
            int m = (int)a.size();
            int n = (int)a[0].size();
            this->m = m;
            this->n = n;
            array = new t*[m];
            for (int i = 0; i < m; i++)
            {
                
                array[i] = new t[n];
                for (int j = 0; j < n; j++)
                {
                    
                    array[i][j] = a[i][j];
                    
                }
                
            }
            
        }
        catch (int e)
        {
            
            cout<<"An error occurred\n";
            
        }

        
    }
    
    Matrix<t> (Matrix<t> const &mat)
    {
        
        this->m = mat.m;
        this->n = mat.n;
        array = new t*[m];
        for (int i = 0; i < m; i++)
        {
            
            array[i] = new t[n];
            
        }
        for (int i = 0; i < m; i++)
        {
            
            for (int j = 0; j < n; j++)
            {
                
                array[i][j] = mat.array[i][j];
                
            }
            
        }
        
    }
    
    //DESTRUCTOR
    
    ~Matrix()
    {
        
        if (array)
        {
            
            delete array;
            m = 0;
            n = 0;
            array = NULL;
            
        }
        
        
    }
    
    //OPERATIONS ON THE MATRIX
    
    Matrix<double> sumRow()
    {
        
        Matrix<double> result(1, n);
        for (int i = 0; i < m; i++)
        {
            
            for (int j = 0; j < n; j++)
            {
                
                result[0][j] += array[i][j];
                
            }
            
        }
        return result;
        
    }
    
    double meanRow(int row)
    {
        
        double mean = 0;
        for (int j = 0; j < n; j++)
        {
            
            mean += array[row][j];
            
        }
        return mean/n;
        
    }
    
    double meanCol(int col)
    {
        
        double mean = 0;
        for (int i = 0; i < m; i++)
        {
            
            mean += array[i][col];
            
        }
        return mean/m;
        
    }
    
    double stdRow(int row)
    {
        
        double mean = meanRow(row);
        double std = 0;
        for (int j = 0; j < n; j++)
        {
            
            std += (array[row][j] - mean)*(array[row][j] - mean);
            
        }
        std /= n;
        return sqrt(std);
        
    }
    
    double stdCol(int col)
    {
        
        double mean = meanCol(col);
        double std = 0;
        for (int i = 0; i < m; i++)
        {
            
            std += (array[i][col] - mean)*(array[i][col] - mean);
            
        }
        std /= m;
        return sqrt(std);
        
    }
    
    void normalise()
    {
        double means[n];
        double stds[n];
        for (int j = 0; j < n; j++)
        {
            
            means[j] = meanCol(j);
            stds[j] = stdCol(j);
            
        }
        for (int i = 0; i < m; i++)
        {
            
            for (int j = 0; j < n; j++)
            {
                
                array[i][j] = (array[i][j] - means[j])/stds[j];
                
            }
            
        }
    }
    
    t max()
    {
        
        try
        {
            
            if (!is_same<t, int>::value && !is_same<t, double>::value && !is_same<t, float>::value && !is_same<t, long>::value && !is_same<t, long long>::value)
            {
                
                throw 1;
                
            }
            double Max = INT_MIN;
            for (int i = 0; i < m; i++)
            {
                
                for (int j = 0; j < n; j++)
                {
                    
                    Max = this->array[i][j] >= Max ? this->array[i][j] : Max;
                    
                }
                
            }
            return Max;
        
        }
        catch (int e)
        {
            
            if (e == 1)
            {
                
                cout<<"Cannot find max of non-numerical value\n";
                
            }
            else
            {
                
                cout<<"An error occurred";
                
            }
            
        }
        
        
    }
    
    t min()
    {
        
        try
        {
            
            if (!is_same<t, int>::value && !is_same<t, double>::value && !is_same<t, float>::value && !is_same<t, long>::value && !is_same<t, long long>::value)
            {
                
                throw 1;
                
            }
            double Min = INT_MAX;
            for (int i = 0; i < m; i++)
            {
                
                for (int j = 0; j < n; j++)
                {
                    
                    Min = array[i][j] <= Min ? array[i][j] : Min;
                    
                }
                
            }
            return Min;
            
        }
        catch (int e)
        {
            
            if (e == 1)
            {
                
                cout<<"Cannot find max of non-numerical value\n";
                
            }
            else
            {
                
                cout<<"An error occurred";
                
            }

            
        }
        
        
    }
    
    void print()
    {
        
        for (int i = 0; i < m; i++)
        {
            
            for (int j = 0; j < n; j++)
            {
                
                cout<<this->array[i][j]<<" ";
                
            }
            i == m-1 ? cout<<"" : cout<<"\n";
            
        }
        
    }
    
    //GETTERS FOR ROWS AND COLUMNS
    
    Matrix<t> r(int i)
    {
        
        try
        {
            
            if (i >= m)
            {
                
                throw "Out of bounds";
                
            }
            else
            {
                
                Matrix<t> result(1, n);
                for (int j = 0; j < n; j++)
                {
                    
                    result->array[0][j] = array[i][j];
                    
                }
                return result;
                
            }

            
        }
        catch (string e)
        {
            
            cout<<e<<"\n";
            
        }
        return Matrix<t>();
    }
    
    Matrix<t> r(int low, int high)
    {
        try
        {
            
            if (low < 0 || high >= m)
            {
                
                throw 1;
                
            }
            else
            {
                
                Matrix<t> result(high-low+1, n);
                for (int i = 0; i < high-low+1; i++)
                {
                    
                    for (int j = 0; j < n; j++)
                    {
                        
                        result[i][j] = array[low+i][j];
                        
                    }
                    
                }
                return result;
                
            }
            
        }
        catch (int e)
        {
            
            if (e == 1)
            {
                
                cout<<"Out of bounds\n";
                
            }
            
        }
        return Matrix<t>();
        
    }
    
    Matrix<t> c(int j)
    {
        
        try
        {
            
            if (j >= n)
            {
                
                throw "Out of bounds";
                
            }
            else
            {
                
                Matrix<t> result(m, 1);
                for (int i = 0; i < this->m; i++)
                {
                    
                    result[i][0] = array[i][j];
                    
                }
                return result;
                
            }
            
            
        }
        catch (string e)
        {
            
            cout<<e<<"\n";
            
        }
        return Matrix<t>();
        
    }
    
    Matrix<t> c(int low, int high)
    {
        
        try
        {
            if (low < 0 || high >= n)
            {
                
                throw 1;
                
            }
            Matrix<t> result(m, high-low+1);
            for (int i = 0; i < m; i++)
            {
                
                for (int j = 0; j < high-low+1; j++)
                {
                    
                    result[i][j] = array[i][j+low];
                    
                }
                
            }
            return result;
            
        }
        catch(int e)
        {
            
            if (e == 1)
            {
                
                cout<<"Out of bounds\n";
                
            }
            
        }
        return Matrix<t>();
        
    }
    
    Matrix<t> transpose()
    {
        
        Matrix<t> result(n, m);
        for (int i = 0; i < n; i++)
        {
            
            for (int j = 0; j < m; j++)
            {
                
                result[i][j] = array[j][i];
                
            }
            
        }
        return result;
        
    }
    
    //IMPLICIT LEFT OPERAND OPERATORS
    
    t* operator [] (int m)
    {
        
        return this->array[m];
        
    }
    
    void operator = (Matrix<t> mat)
    {
        
        for (int i = 0; i < m; i++)
        {
            
            delete[] array[i];
            array[i] = NULL;
            
        }
        
        m = 0;
        n = 0;
        
        m = mat.m;
        n = mat.n;
        
        array = new t*[m];
        for (int i = 0; i < m; i++)
        {
            
            array[i] = new t[n];
            
        }
        
        for (int i = 0; i < m; i++)
        {
            
            for (int j = 0; j < n; j++)
            {
                
                    
                array[i][j] = mat.array[i][j];
            
                
            }
            
        }
        
    }
    
    bool operator == (Matrix<t> mat)
    {
        
        if (m == mat.m && n == mat.n)
        {
            
            for (int i = 0; i < m; i++)
            {
                
                for (int j = 0; j < n; j++)
                {
                    
                    if (array[i][j] != mat[i][j])
                    {
                        
                        return 0;
                        
                    }
                    
                }
                
            }
            return 1;
            
        }
        return 0;
        
    }
    
    void operator += (Matrix<t> a)
    {
        
        try
        {
            
            if (m == a.m && n == a.n)
            {
                
                for (int i = 0; i < a.m; i++)
                {
                    
                    for (int j = 0; j < a.n; j++)
                    {
                        
                        array[i][j] += a[i][j];
                        
                    }
                    
                }
                
            }
            else
            {
                
                throw 1;
                
            }
            
        }
        catch (int e)
        {
            
            
            
        }
        
    }
    
    void operator += (double a)
    {
        
        try
        {
            
            if (is_same<t, double>::value)
            {
                
                for (int i = 0; i < m; i++)
                {
                    
                    for (int j = 0; j < n; j++)
                    {
                        
                        array[i][j] += a;
                        
                    }
                    
                }
                
            }
            else
            {
                
                throw 1;
                
            }
            
        }
        catch (int e)
        {
            
            
            
        }
        
    }
    
    void operator -= (Matrix<t> a)
    {
        
        try
        {
            
            if (m == a.m && n == a.n)
            {
                
                for (int i = 0; i < a.m; i++)
                {
                    
                    for (int j = 0; j < a.n; j++)
                    {
                        
                        array[i][j] -= a[i][j];
                        
                    }
                    
                }
                
            }
            else
            {
                
                throw 1;
                
            }
            
        }
        catch (int e)
        {
            
            
            
        }
        
    }
    
    void operator -= (double a)
    {
        
        try
        {
            
            if (is_same<t, double>::value)
            {
                
                for (int i = 0; i < m; i++)
                {
                    
                    for (int j = 0; j < n; j++)
                    {
                        
                        array[i][j] -= a;
                        
                    }
                    
                }
                
            }
            else
            {
                
                throw 1;
                
            }
            
        }
        catch (int e)
        {
            
            
            
        }
        
    }
    
    void operator *= (double a)
    {
        
        try
        {
            
            if (is_same<t, double>::value)
            {
                
                for (int i = 0; i < m; i++)
                {
                    
                    for (int j = 0; j < n; j++)
                    {
                        
                        array[i][j] *= a;
                        
                    }
                    
                }
                
            }
            else
            {
                
                throw 1;
                
            }
            
        }
        catch (int e)
        {
            
            
            
        }
        
    }
    
    void operator /= (double a)
    {
        
        try
        {
            
            if (is_same<t, double>::value)
            {
                
                for (int i = 0; i < m; i++)
                {
                    
                    for (int j = 0; j < n; j++)
                    {
                        
                        array[i][j] /= a;
                        
                    }
                    
                }
                
            }
            else
            {
                
                throw 1;
                
            }
            
        }
        catch (int e)
        {
            
            
            
        }
        
    }
    
    Matrix<t> dot(Matrix<t> b)
    {
        
        try
        {
            
            if (b.m == m && b.n == n)
            {
                
                Matrix<t> result(m, n);
                for (int i = 0; i < m; i++)
                {
                    
                    for (int j = 0; j < n; j++)
                    {
                        
                        result[i][j] = array[i][j]*b[i][j];
                        
                    }
                    
                }
                return result;
                
            }
            else
            {
                
                throw 1;
                
            }
            
        }
        catch (int e)
        {
            
            if (e == 1)
            {
                
                cout<<"Incompatible dimensions\n";
                
            }
            
        }
        return Matrix<t>();
        
    }
    
    Matrix<t> operator & (Matrix<t> b)
    {
        
        try
        {
            
            if (m != b.m)
            {
                
                throw 1;
                
            }
            else
            {
                
                Matrix<t> result(m, n + b.n);
                for (int i = 0; i < m; i++)
                {
                    
                    for (int j = 0; j < n; j++)
                    {
                        
                        result[i][j] = array[i][j];
                        
                    }
                    
                }
                for (int i = 0; i < m; i++)
                {
                    
                    for (int j = 0; j < b.n; j++)
                    {
                        
                        result[i][n+j] = b[i][j];
                        
                    }
                    
                }
                return result;
                
            }
            
        }
        catch (int e)
        {
            
            if (e == 1)
            {
                
                cout<<"Incompatible dimensions\n";
                return Matrix<t>();
                
            }
            
        }
        return Matrix<t>();
        
    }
    
};

template<typename t>
Matrix<t> operator + (Matrix<t> a, Matrix<t> b)
{
    
    try
    {
        
        if (a.m == b.m && a.n == b.n)
        {
            
            Matrix<t> result(a.m, a.n);
            for (int i = 0; i < a.m; i++)
            {
                
                for (int j = 0; j < a.n; j++)
                {
                    
                    result[i][j] = a[i][j] + b[i][j];
                    
                }
                
            }
            return result;
            
        }
        else
        {
            
            throw 1;
            
        }
        
    }
    catch (int e)
    {
        
        
        
    }
    return Matrix<t>();
    
}

template<typename t>
Matrix<t> operator + (Matrix<t> a, double b)
{
    
    try
    {
        
        if (is_same<t, double>::value)
        {
            
            Matrix<t> result(a.m, a.n);
            for (int i = 0; i < a.m; i++)
            {
                
                for (int j = 0; j < a.n; j++)
                {
                    
                    result[i][j] = a[i][j] + b;
                    
                }
                
            }
            return result;
            
        }
        else
        {
            
            throw 1;
            
        }
        
    }
    catch (int e)
    {
        
        cout<<"Incompatible types\n";
        
    }
    return Matrix<t>();
    
}


template<typename t>
Matrix<t> operator - (Matrix<t> a, Matrix<t> b)
{
    
    try
    {
        
        if (a.m == b.m && a.n == b.n)
        {
            
            Matrix<t> result(a.m, a.n);
            for (int i = 0; i < a.m; i++)
            {
                
                for (int j = 0; j < a.n; j++)
                {
                    
                    result[i][j] = a[i][j] - b[i][j];
                    
                }
                
            }
            return result;
            
        }
        else
        {
            
            throw 1;
            
        }
        
    }
    catch (int e)
    {
        
        
        
    }
    return Matrix<t>();
    
}

template<typename t>
Matrix<t> operator - (Matrix<t> a, double b)
{
    
    try
    {
        
        if (is_same<t, double>::value)
        {
            
            Matrix<t> result(a.m, a.n);
            for (int i = 0; i < a.m; i++)
            {
                
                for (int j = 0; j < a.n; j++)
                {
                    
                    result[i][j] = a[i][j] - b;
                    
                }
                
            }
            return result;
            
        }
        else
        {
            
            throw 1;
            
        }
        
    }
    catch (int e)
    {
        
        
        
    }
    return Matrix<t>();
    
}


template<typename t>
Matrix<t> operator * (Matrix<t> a, Matrix<t> b)
{
    
    try
    {
        
        if (is_same<t, string>::value)
        {
            
            throw 1;
            
        }
        else if (a.n != b.m)
        {
            
            throw 2;
            
        }
        else
        {
            
            Matrix<t> result(a.m, b.n);
            int K = a.n = b.m;
            int m = a.m;
            int n = b.n;
            for (int i = 0; i < m; i++)
            {
                
                for (int j = 0; j < n; j++)
                {
                    
                    int sum = 0;
                    for (int k = 0; k < K; k++)
                    {
                        
                        sum += a[i][k]*b[k][j];
                        
                    }
                    result.array[i][j] = sum;
                    
                }
                
            }
            return result;
        }
        
    }
    catch (int e)
    {
        
        if (e == 1)
        {
            
            cout<<"Matrix's type is not compatible with the multiply operation\n";
            
        }
        else if (e == 2)
        {
            
            cout<<"Matix dimensions not compatible\n";
            
        }
        
    }
    return Matrix<t>();
}


template<typename t>
ostream &operator << (ostream &os, Matrix<t> matrix)
{
    
    matrix.print();
    return os;
    
}

class eye : public Matrix<double>
{
    
public:
    
    eye(int m) : Matrix<double>(m, m)
    {
        
        for (int i = 0; i < m; i++)
        {
            
            this->array[i][i] = 1;
            
        }
        
    }
};

class ones : public Matrix<double>
{
    
public:
    
    ones(int m, int n) : Matrix<double>(m, n)
    {
        
        for (int i = 0; i < m; i++)
        {
            
            for (int j = 0; j < n; j++)
            {
                
                this->array[i][j] = 1;
                
            }
            
        }
        
    }
    
    
};

class zeros : public Matrix<double>
{
    
    
public:
    
    zeros(int m, int n) : Matrix<double>(m, n)
    {
        
        for (int i = 0; i < m; i++)
        {
            
            for (int j = 0; j < n; j++)
            {
                
                this->array[i][j] = 0;
                
            }
            
        }
        
    }
    
    
};

#endif /* Matrix_h */
