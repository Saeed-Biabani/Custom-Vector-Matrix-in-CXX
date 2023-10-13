#ifndef _MATRIX2D_H_
#define _MATRIX2D_H_

/*  -   -   -   -   -   -   -   -   -   -   -   */
template<class _T>
class Vector;
/*  -   -   -   -   -   -   -   -   -   -   -   */

#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

enum Axis2D {
    ALL,
    COL
};

template<class _T>
class Matrix2D {
    public:
        typedef size_t size_type;
        typedef _T** _iterator;

    private:
        _iterator _mat;
        size_type _row;
        size_type _col;
        
        // mutable _iterator _mat;
        // mutable size_type _row;
        // mutable size_type _col;

        auto calc_mean_for_whole_matrix() const noexcept;
        auto calc_mean_for_each_col() const noexcept;
        auto calc_std_for_whole_matrix() const noexcept;
        auto calc_std_for_each_col() const noexcept;
        auto find_min_whole_matrix() const noexcept;
        auto find_min_for_each_col() const noexcept;
        auto find_max_whole_matrix() const noexcept;
        auto find_max_for_each_col() const noexcept;


    public:
        constexpr Matrix2D() noexcept = default;
        constexpr Matrix2D(_iterator, size_type, size_type) noexcept;

        static auto ZeroInit(size_type, size_type) noexcept;
        static auto OneInit(size_type, size_type) noexcept;
        static auto RandomInit(size_type, size_type) noexcept;

        constexpr _iterator Begin() const noexcept { return this->_mat; }
        constexpr size_type Row() const noexcept { return this->_row; }
        constexpr size_type Col() const noexcept { return this->_col; }

        constexpr auto Mean(Axis2D) const noexcept;
        constexpr auto STD(Axis2D) const noexcept;
        constexpr auto Min(Axis2D) const noexcept;
        constexpr auto Max(Axis2D) const noexcept;

        constexpr auto T() const noexcept;

        void operator = (const Matrix2D<_T>&) const noexcept;
        _T operator () (const int, const int) const noexcept;
        auto operator - (const Matrix2D<_T>&) const noexcept;
        auto operator - (const Vector<_T>&) const noexcept;
        auto operator - (const _T&) const noexcept;
        auto operator + (const Matrix2D<_T>&) const noexcept;
        auto operator + (const Vector<_T>&) const noexcept;
        auto operator + (const _T&) const noexcept;
        auto operator * (const Matrix2D<_T>&) const noexcept;
        auto operator * (const Vector<_T>&) const noexcept;
        auto operator * (const _T&) const noexcept;
        auto operator / (const Matrix2D<_T>&) const noexcept;
        auto operator / (const Vector<_T>&) const noexcept;
        auto operator / (const _T&) const noexcept;

        friend auto operator << (const ostream& stream, const Matrix2D<_T>& mat) noexcept {
            for (int i = 0; i < mat.Row(); i++) {
                for (int j = 0; j < mat.Col(); j++) {
                    cout<<mat(i, j)<<"  ";
                }
                cout<<endl;
            }
        }
};


template<class _T>
constexpr Matrix2D<_T>::Matrix2D(_iterator _mat, size_type __r, size_type __c) noexcept {
    this->_mat = _mat;
    this->_row = __r;
    this->_col = __c;
}


// Initializers ----------------------------------------------------------------
template<class _T>
auto Matrix2D<_T>::ZeroInit(size_type __r, size_type __c) noexcept {
    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new _T[__c];
        for (int j = 0; j < __c; j++) {
            v[i][j] = _T(0);
        }
    }
    return Matrix2D(v, __r, __c);
}


template<class _T>
auto Matrix2D<_T>::OneInit(size_type __r, size_type __c) noexcept {
    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new _T[__c];
        for (int j = 0; j < __c; j++) {
            v[i][j] = _T(1);
        }
    }
    return Matrix2D(v, __r, __c);
}


template<class _T>
auto Matrix2D<_T>::RandomInit(size_type __r, size_type __c) noexcept {
    auto seed = system_clock::now().time_since_epoch().count();
    default_random_engine engine(seed);
    uniform_real_distribution<_T> distribution(-1., 1.);
    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new _T[__c];
        for (int j = 0; j < __c; j++) {
            v[i][j] = distribution(engine);
        }
    }
    return Matrix2D(v, __r, __c);
}

// Statistics ----------------------------------------------------------------
template<class _T>
auto Matrix2D<_T>::calc_mean_for_whole_matrix() const noexcept {
    _T *sum = new _T[1];

    sum[0] = 0;
    for (int i = 0; i < this->_row; i++) {
        for (int j = 0; j < this->_col; j++) {
            sum[0] += this->_mat[i][j];
        }
    }
    sum[0] /= (this->_row * this->_col);
    return Vector(sum, 1);
}


template<class _T>
auto Matrix2D<_T>::calc_mean_for_each_col() const noexcept {
    _T *sum = new _T[this->_col];

    for (int i = 0; i < this->_col; i++) {
        sum[i] = 0;
        for (int j = 0; j < this->_row; j++) {
            sum[i] += this->_mat[j][i];
        }
        sum[i] /= this->_row;
    }
    return Vector<_T>(sum, this->_col);
}


template<class _T>
constexpr auto Matrix2D<_T>::Mean(Axis2D axis) const noexcept {
    switch (axis) {
        case Axis2D::ALL : return this->calc_mean_for_whole_matrix();
        case Axis2D::COL : return this->calc_mean_for_each_col();
        default : return Vector<_T>();
    }
}


template<class _T>
auto Matrix2D<_T>::calc_std_for_whole_matrix() const noexcept {
    auto mean = this->Mean(Axis2D::ALL)[0];
    _T *sum = new _T[1];

    sum[0] = 0;
    for (int i = 0; i < this->_row; i++) {
        for (int j = 0; j < this->_col; j++) {
            sum[0] += pow(this->_mat[i][j] - mean, 2);
        }
    }
    sum[0] = sqrt(sum[0] / (this->_row * this->_col));
    return Vector(sum, 1);
}


template<class _T>
auto Matrix2D<_T>::calc_std_for_each_col() const noexcept {
    auto mean = this->Mean(Axis2D::COL);
    size_type __l = mean.Size();
    _T *sum = new _T[__l];

    for (int i = 0; i < this->_col; i++) {
        sum[i] = 0;
        for (int j = 0; j < this->_row; j++) {
            sum[i] += pow(this->_mat[j][i] - mean[i], 2);
        }
        sum[i] = sqrt(sum[i] / this->_row);
    }
    return Vector(sum, __l);
}


template<class _T>
constexpr auto Matrix2D<_T>::STD(Axis2D axis) const noexcept {
    switch (axis) {
        case Axis2D::ALL : return this->calc_std_for_whole_matrix();
        case Axis2D::COL : return this->calc_std_for_each_col();
        default : return Vector<_T>();
    }
}


template<class _T>
auto Matrix2D<_T>::find_max_whole_matrix() const noexcept {
    _T *max = new _T[1];

    max[0] = this->_mat[0][0];
    for (int i = 0; i < this->_row; i++) {
        for (int j = 0; j < this->_col; j++) {
            if (this->_mat[i][j] > max[0]) {
                max[0] = this->_mat[i][j];
            }
        }
    }
    return Vector(max, 1);
}


template<class _T>
auto Matrix2D<_T>::find_max_for_each_col() const noexcept {
    size_type __l = this->_col;
    _T *max = new _T[__l];

    for (int i = 0; i < this->_col; i++) {
        max[i] = this->_mat[0][i];
        for (int j = 0; j < this->_row; j++) {
            if (this->_mat[j][i] > max[i]) {
                max[i] = this->_mat[j][i];
            }
        }
    }
    return Vector(max, __l);
}


template<class _T>
constexpr auto Matrix2D<_T>::Max(Axis2D axis) const noexcept {
    switch (axis) {
        case Axis2D::ALL : return this->find_max_whole_matrix();
        case Axis2D::COL : return this->find_max_for_each_col();
        default : return Vector<_T>();
    }
}


template<class _T>
auto Matrix2D<_T>::find_min_whole_matrix() const noexcept {
    _T *min = new _T[1];

    min[0] = this->_mat[0][0];
    for (int i = 0; i < this->_row; i++) {
        for (int j = 0; j < this->_col; j++) {
            if (this->_mat[i][j] < min[0]) {
                min[0] = this->_mat[i][j];
            }
        }
    }
    return Vector(min, 1);
}


template<class _T>
auto Matrix2D<_T>::find_min_for_each_col() const noexcept {
    size_type __l = this->_col;
    _T *min = new _T[__l];

    for (int i = 0; i < this->_col; i++) {
        min[i] = this->_mat[0][i];
        for (int j = 0; j < this->_row; j++) {
            if (this->_mat[j][i] < min[i]) {
                min[i] = this->_mat[j][i];
            }
        }
    }
    return Vector(min, __l);
}


template<class _T>
constexpr auto Matrix2D<_T>::Min(Axis2D axis) const noexcept {
    switch (axis) {
        case Axis2D::ALL : return this->find_min_whole_matrix();
        case Axis2D::COL : return this->find_min_for_each_col();
        default : return Vector<_T>();
    }
}

// Transpose ----------------------------------------------------------------
template<class _T>
constexpr auto Matrix2D<_T>::T() const noexcept {
    size_type __r = this->_row, __c = this->_col;
    _T **v = new _T*[__c];

    for (int i = 0; i < __c; i++) {
        v[i] = new _T[__r];
        for (int j = 0; j < __r; j++) {
            v[i][j] = this->_mat[j][i];
        }
    }
    return Matrix2D(v, this->_col, this->_row);
}

// Operators ----------------------------------------------------------------
template<class _T>
void Matrix2D<_T>::operator = (const Matrix2D<_T> &y) const noexcept {
    this->_mat = y.Begin();
    this->_row = y.Row();
    this->_col = y.Col();
}


template<class _T>
_T Matrix2D<_T>::operator () (const int i, const int j) const noexcept {
    return this->_mat[i][j];
}


template<class _T>
auto Matrix2D<_T>::operator - (const Matrix2D<_T> &y) const noexcept {
    size_type __r = this->_row, __c = this->_col;
    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new float[__c];
        for (int j = 0; j < __c; j++) {
            v[i][j] = this->_mat[i][j] - y(i, j);
        }
    }
    return Matrix2D(v, __r, __c);
}


template<class _T>
auto Matrix2D<_T>::operator - (const Vector<_T> &y) const noexcept {
    size_type __r = this->_row, __c = this->_col;
    size_type __l = y.Size();


    if (__l == 1) {
        return this->operator-(y[0]);
    }

    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new float[__c];
    }

    for (int i = 0; i < __c; i++) {
        for (int j = 0; j < __r; j++) {
            v[j][i] = this->_mat[j][i] - y[i];
        }
    }
    return Matrix2D(v, __r, __c);
}


template<class _T>
auto Matrix2D<_T>::operator - (const _T &y) const noexcept {
    size_type __r = this->_row, __c = this->_col;
    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new float[__c];
        for (int j = 0; j < __c; j++) {
            v[i][j] = this->_mat[i][j] - y;
        }
    }
    return Matrix2D(v, __r, __c);
}


template<class _T>
auto Matrix2D<_T>::operator + (const Matrix2D<_T> &y) const noexcept {
    size_type __r = this->_row, __c = this->_col;
    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new float[__c];
        for (int j = 0; j < __c; j++) {
            v[i][j] = this->_mat[i][j] + y(i, j);
        }
    }
    return Matrix2D(v, __r, __c);
}


template<class _T>
auto Matrix2D<_T>::operator + (const Vector<_T> &y) const noexcept {
    size_type __r = this->_row, __c = this->_col;
    size_type __l = y.Size();


    if (__l == 1) {
        return this->operator+(y[0]);
    }

    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new float[__c];
    }

    for (int i = 0; i < __c; i++) {
        for (int j = 0; j < __r; j++) {
            v[j][i] = this->_mat[j][i] + y[i];
        }
    }
    return Matrix2D(v, __r, __c);
}


template<class _T>
auto Matrix2D<_T>::operator + (const _T &y) const noexcept {
    size_type __r = this->_row, __c = this->_col;
    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new float[__c];
        for (int j = 0; j < __c; j++) {
            v[i][j] = this->_mat[i][j] + y;
        }
    }
    return Matrix2D(v, __r, __c);
}


template<class _T>
auto Matrix2D<_T>::operator / (const Matrix2D<_T> &y) const noexcept {
    size_type __r = this->_row, __c = this->_col;
    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new float[__c];
        for (int j = 0; j < __c; j++) {
            v[i][j] = this->_mat[i][j] / y(i, j);
        }
    }
    return Matrix2D(v, __r, __c);
}


template<class _T>
auto Matrix2D<_T>::operator / (const Vector<_T> &y) const noexcept {
    size_type __r = this->_row, __c = this->_col;
    size_type __l = y.Size();


    if (__l == 1) {
        return this->operator/(y[0]);
    }

    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new float[__c];
    }

    for (int i = 0; i < __c; i++) {
        for (int j = 0; j < __r; j++) {
            v[j][i] = this->_mat[j][i] / y[i];
        }
    }
    return Matrix2D(v, __r, __c);
}


template<class _T>
auto Matrix2D<_T>::operator / (const _T &y) const noexcept {
    size_type __r = this->_row, __c = this->_col;
    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new float[__c];
        for (int j = 0; j < __c; j++) {
            v[i][j] = this->_mat[i][j] / y;
        }
    }
    return Matrix2D(v, __r, __c);
}


template<class _T>
auto Matrix2D<_T>::operator * (const Matrix2D<_T> &y) const noexcept {
    size_type _x_r = this->_row, _x_c = this->_col;
    size_type _y_r = y.Row(), _y_c = y.Col();

    _T **v = new _T*[_x_r];

    for (int i = 0; i < _x_r; i++) {
        v[i] = new float[_y_c];
        for (int j = 0; j < _y_c; j++) {
            v[i][j] = 0;
            for (int k = 0; k < _y_r; k++) {
                v[i][j] += (this->_mat[i][k] * y(k, j));
            }
        }
    }
    return Matrix2D(v, _x_r, _y_c);
}


template<class _T>
auto Matrix2D<_T>::operator * (const Vector<_T> &y) const noexcept {
    size_type __r = this->_row, __c = this->_col;
    size_type __l = y.Size();


    if (__l == 1) {
        return this->operator*(y[0]);
    }

    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new float[__c];
    }

    for (int i = 0; i < __c; i++) {
        for (int j = 0; j < __r; j++) {
            v[j][i] = this->_mat[j][i] * y[i];
        }
    }
    return Matrix2D(v, __r, __c);
}


template<class _T>
auto Matrix2D<_T>::operator * (const _T &y) const noexcept {
    size_type __r = this->_row, __c = this->_col;
    _T **v = new _T*[__r];

    for (int i = 0; i < __r; i++) {
        v[i] = new float[__c];
        for (int j = 0; j < __c; j++) {
            v[i][j] = this->_mat[i][j] * y;
        }
    }
    return Matrix2D(v, __r, __c);
}




#endif // !_MATRIX2D_H_