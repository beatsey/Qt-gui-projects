#include "cppmath.h"
/**
https://en.wikibooks.org/wiki/Algorithm_Implementation/Linear_Algebra/Tridiagonal_matrix_algorithm

 * n - число уравнений (строк матрицы)
 * c - диагональ, лежащая над главной (нумеруется: [0;n-2])
 * b - главная диагональ матрицы A (нумеруется: [0;n-1])
 * a - диагональ, лежащая под главной (нумеруется: [0;n-2])
 * f - правая часть (столбец)
 * x - решение, массив x будет содержать ответ
 */

void solveMatrix (int n, double *a, double *b, double *c, double *f, double *x){
    double m;
    for (int i = 0; i < n-1; ++i){
            m = a[i]/b[i];
            b[i+1] -=m*c[i];
            f[i+1] -=m*f[i];
    }
    x[n-1] = f[n-1]/b[n-1];

    for (int i = n - 2; i >= 0; --i)
            x[i]=(f[i]-c[i]*x[i+1])/b[i];
}

void solveMatrix (size_t n, double *a, double *b, double *c, std :: vector<Vector2>&f, std :: vector<Vector2>&x){
    double m;
    for (size_t i = 0; i < n-1; ++i){
            m = a[i]/b[i];
            b[i+1] -=m*c[i];
            f[i+1] -=m*f[i];
    }
    x[n-1] = f[n-1]/b[n-1];

    for (int i = static_cast<int>(n) - 2; i >= 0; --i){
        Vector2 &vec=x[static_cast<size_t>(i)];
        vec=f[static_cast<size_t>(i)]-c[i]*x[static_cast<size_t>(i)+1];
        vec/=b[i];
    }
}

