# Linear-Algebra
Matrix.h is an implementation of matrices and operations on them, in C++. I have attempted to make it as close as possible to its Octave counterpart. Matrices are zero-indexed

## Usage

### 1. Initialisation with zeros:
```c++
Matrix<double> X(int m, int n); //m is the number of rows and n, columns.
```
Or
```c++
Matrix<double> X = zeros(int m, int n);
```

### 2. Initialise with ones:
```c++
Matrix<double> X = ones(int m, int n);
```

### 3. Initialise with a .csv. The filepath should be in the current working directory of your IDE. Note : remove leading zeros and tabs - to be fixed in a future implementation
```c++
Matrix<double> X("test.csv");
```

### 4. Initialise with a vector.
```c++
Matrix<double> X(new vector<vector<double>> {{1, 2, 3}, {4, 5, 6}};
```

## Supported Operations

### 1. Access values
Print values or the matrix itself using cout.
```c++
Matrix<double> X("test.csv");
cout<<X[0][1]<<"\n";
cout<<X<<"\n"
```

### 2. Arithmetic
Addition, sutraction and multiplication is supported for both scalars and matrices.
```c++
Matrix<double> X("test.csv");
Matrix<double> Y = ones(X.m, X.n);
X = X+Y;
X += Y;
X -= Y;
X = X*Y;
X += 5;
Y /= 2;
```

### 3. Transformations
Currently supports transpose (inverse and adjoint to be added). Get row or column vector from matrix, or sub-matrix or arbitrary size.
```c++
Matrix<double> X("test.csv");
X = X.transpose();
Matrix<double> Y = X.r(1) //Get 1th row-vector
Y = X.r(1, 4) //Get matrix from 1th to rth row
//Similar operations for retrieving column vector
```

### 4. Aggregate functions
Get sum, mean, standard deviation of row/column.
```
Matrix<double> X("test.csv");
double m = X.meanRow(3);
m = X.stdRow(2);
//simlilar operations for columns
```
