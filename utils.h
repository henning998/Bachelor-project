#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string>
#include <cassert>
#include "nr3.h"

using namespace std;

namespace utils {
    void print(MatDoub_I &A, const string &text = "") {
        cout << text << "  Matrix " << A.nrows() << "x" << A.ncols() << ":" << endl;
        for (int m = 0; m < A.nrows(); m++) {
            for (int n = 0; n < A.ncols(); n++)
                cout << setw(15) << A[m][n] << "\t";
            cout << endl;
        }
        cout << endl;
    }

    void printDiag(MatDoub_I &mat, const string &text = "") {
        cout << text << "  MatrixDiag " << mat.nrows() << "x" << mat.ncols() << ":" << endl;
        double nmax = mat.nrows() < mat.nrows() ? mat.nrows() : mat.nrows();
        for (int n = 0; n < nmax; n++)
            cout << setw(15) << mat[n][n] << "\t";
        cout << endl;
    }

    void print(VecDoub_I &vec, const string &text = "") {
        cout << text << "  Vector " << vec.size() << "D:" << endl;
        for (int m = 0; m < vec.size(); m++) {
            cout << setw(15) << vec[m];
        }
        cout << endl;
    }

    Doub sum(VecDoub_I &V){
        Doub s = 0;
        for (int i = 0; i < V.size(); i++)
            s += V[i];
        return s;
    }

    Doub norm(VecDoub_I &V){
        Doub s = 0;
        for (int i = 0; i < V.size(); i++)
            s += V[i] * V[i];
        return sqrt(s);
    }

    VecDoub fill(int m, Doub v) {
        VecDoub V(m);
        for (int i = 0; i < m; i++)
            V[i] = v;
        return V;
    }

    VecDoub zeros(int m) {
        return fill(m, 0);
    }

    VecDoub ones(int m) {
        return fill(m, 1);
    }

    MatDoub fill(int m, int n, Doub v) {
        MatDoub A(m, n);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                A[i][j] = v;
        return A;
    }

    MatDoub zeros(int m, int n) {
        return fill(m, n, 0);
    }

    MatDoub ones(int m, int n) {
        return fill(m, n, 1);
    }

    MatDoub diag(int m, Doub v) {
        MatDoub A = zeros(m, m);
        for (int i = 0; i < m; i++)
            A[i][i] = v;
        return A;
    }

    MatDoub eye(int m) {
        return diag(m, 1);
    }

    MatDoub diag(VecDoub &V) {
        int m = V.size();
        MatDoub M = zeros(m, m);
        for (int i = 0; i < m; i++)
            M[i][i] = V[i];
        return M;
    }

    VecDoub diag(MatDoub &A) {
        int m = A.nrows();
        assert(m == A.ncols());
        VecDoub V(m);
        for (int i = 0; i < m; i++)
            V[i] = A[i][i];
        return V;
    }

    MatDoub Transpose(const MatDoub &Mat) {
        MatDoub res(Mat.ncols(), Mat.nrows());
        for (int n = 0; n < res.nrows(); n++) {
            for (int m = 0; m < res.ncols(); m++) {
                res[n][m] = Mat[m][n];
            }
        }
        return res;
    }

    MatDoub T(const MatDoub &Mat) {
        return Transpose(Mat);
    }
}

MatDoub operator*(const MatDoub &A1, const MatDoub &A2) {
    assert(A1.ncols() == A2.nrows());
    MatDoub res(A1.nrows(), A2.ncols());
    for (int n = 0; n < A1.nrows(); n++) {
        for (int m = 0; m < A2.ncols(); m++) {
            double temp = 0;
            for (int i = 0; i < A1.ncols(); i++) {
                temp += A1[n][i] * A2[i][m];
            }
            res[n][m] = temp;
        }
    }
    return res;
}

VecDoub operator*(const MatDoub &A, const VecDoub &b) {
    assert(A.ncols() == b.size());
    VecDoub res(A.nrows());
    for (int n = 0; n < A.nrows(); n++) {
        double temp = 0;
        for (int m = 0; m < A.ncols(); m++) {
            temp += A[n][m] * b[m];
        }
        res[n] = temp;
    }
    return res;
}


VecDoub operator+(VecDoub_I &a, VecDoub_I &b) {
    assert(a.size() == b.size());
    VecDoub c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[i] = a[i] + b[i];
    return c;
}

VecDoub operator-(VecDoub_I &a, VecDoub_I &b) {
    assert(a.size() == b.size());
    VecDoub c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[i] = a[i] - b[i];
    return c;
}

VecDoub operator*(VecDoub_I &a, VecDoub_I &b) {
    assert(a.size() == b.size());
    VecDoub c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[i] = a[i] * b[i];
    return c;
}

VecDoub operator/(VecDoub_I &a, VecDoub_I &b) {
    assert(a.size() == b.size());
    VecDoub c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[i] = a[i] / b[i];
    return c;
}

VecDoub operator+(VecDoub_I &a, Doub b) {
    VecDoub c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[i] = a[i] + b;
    return c;
}

VecDoub operator+(Doub a, VecDoub_I &b) {
    return b + a;
}

VecDoub operator-(VecDoub_I &a) {
    VecDoub c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[i] = -a[i];
    return c;
}

VecDoub operator-(VecDoub_I &a, Doub b) {
    VecDoub c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[i] = a[i] - b;
    return c;
}

VecDoub operator*(VecDoub_I &a, Doub b) {
    VecDoub c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[i] = a[i] * b;
    return c;
}

VecDoub operator*(Doub a, VecDoub_I &b) {
    return b * a;
}

VecDoub operator/(VecDoub_I &a, Doub b) {
    VecDoub c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[i] = a[i] / b;
    return c;
}

VecDoub operator/(Doub a, VecDoub_I &b) {
    VecDoub c(b.size());
    for (int i = 0; i < b.size(); i++)
        c[i] = a / b[i];
    return c;
}

#endif