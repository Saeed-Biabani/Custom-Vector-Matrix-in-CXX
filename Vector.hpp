#ifndef _VECTOR_H_
#define _VECTOR_H_

/*  -   -   -   -   -   -   -   -   -   -   -   */
template<class _T>
class Matrix2D;
/*  -   -   -   -   -   -   -   -   -   -   -   */

#include <iostream>
#include <random>
#include <chrono>
#include <math.h>

using namespace std;
using namespace chrono;

template<class _T>
class Vector {
    public:
        typedef size_t size_type;
        typedef const _T* const_iterator;

    private:
        const_iterator _vec;
        size_type vec_size;

    public:
        constexpr Vector() noexcept = default;
        constexpr Vector(initializer_list<_T>) noexcept;
        constexpr Vector(const_iterator, size_type) noexcept;

        constexpr auto Size() const noexcept;
        constexpr auto Begin() const noexcept;
        constexpr auto End() const noexcept;

        constexpr auto STD() const noexcept;
        constexpr auto Mean() const noexcept;
        constexpr auto Max() const noexcept;
        constexpr auto Min() const noexcept;

	    constexpr auto Argmax() const noexcept;

        static auto ZeroInit(size_type) noexcept;
        static auto OneInit(size_type) noexcept;
        static auto RandomInit(size_type) noexcept;
        static auto RangeInit(_T __start, _T __end, _T __step = 1) noexcept;

        auto Batch(size_type) noexcept;

        auto operator [] (int) const noexcept;
        void operator = (const Vector<_T>&) const noexcept;
        auto operator + (const Vector<_T>&) const noexcept;
        auto operator + (const _T&) const noexcept;
        auto operator - (const Vector<_T>&) const noexcept;
        auto operator - (const _T&) const noexcept;
        auto operator * (const Vector<_T>&) const noexcept;
        auto operator * (const _T&) const noexcept;
        auto operator / (const Vector<_T>&) const noexcept;
        auto operator / (const _T&) const noexcept;

        friend auto operator << (ostream &str, const Vector<_T> &x) noexcept {
            auto item = x.Begin();
            cout<<"[ ";
            while (item != x.End()) {
                cout << *item<<' ';
                item++;
            }
            cout<<"]"<<endl;
        }
};


template<class _T>
constexpr Vector<_T>::Vector(initializer_list<_T> _iter) noexcept {
    this->_vec = _iter.begin();
    this->vec_size = _iter.size();
}


template<class _T>
constexpr Vector<_T>::Vector(const_iterator __begin, size_t __l) noexcept {
    this->_vec = __begin;
    this->vec_size = __l;
}


template<class _T>
constexpr auto Vector<_T>::Size() const noexcept { return this->vec_size; }


template<class _T>
constexpr auto Vector<_T>::Begin() const noexcept { return this->_vec; }


template<class _T>
constexpr auto Vector<_T>::End() const noexcept { return this->Begin() + this->Size(); }


template<class _T>
constexpr auto Vector<_T>::STD() const noexcept {
    size_type __l = this->vec_size;
    _T mean = this->Mean();
    _T sum = 0;

    auto item = this->Begin();
    while (item != this->End()) {
        sum += pow(*item - mean, 2);
        item++;
    }
    return sqrt(sum / float(__l));
}


template<class _T>
constexpr auto Vector<_T>::Mean() const noexcept {
    size_type __l = this->vec_size;
    _T sum = 0;

    auto item = this->Begin();
    while (item != this->End()) {
        sum += *item;
        item++;
    }
    return sum / __l;
}


template<class _T>
constexpr auto Vector<_T>::Max() const noexcept {
    size_type __l = this->vec_size;
    _T max = this->_vec[0];

    auto item = this->Begin();
    while (item != this->End()) {
        if (*item > max) {
            max = *item;
        }
        item++;
    }
    return max;
}


template<class _T>
constexpr auto Vector<_T>::Min() const noexcept {
    size_type __l = this->vec_size;
    _T min = this->_vec[0];

    auto item = this->Begin();
    while (item != this->End()) {
        if (*item < min) {
            min = *item;
        }
        item++;
    }
    return min;
}


template<class _T>
constexpr auto Vector<_T>::Argmax() const noexcept {
	_T max = *this->_vec;
	const _T *current = this->_vec;
	size_type indx = 0;

	for (int i = 0; i < this->vec_size; i++) {
		if (*current > max) {
			max = *current;
			indx = i;
		}
		current++;
	}
	return indx;
}


template<class _T>
auto Vector<_T>::ZeroInit(size_type __l) noexcept {
    _T *v = new _T[__l];

    for (int i = 0; i < __l; i++) {
        v[i] = _T(0.f);
    }
    return Vector(v, __l);
}


template<class _T>
auto Vector<_T>::OneInit(size_type __l) noexcept {
    _T *v = new _T[__l];

    for (int i = 0; i < __l; i++) {
        v[i] = _T(1.f);
    }
    return Vector(v, __l);
}


template<class _T>
auto Vector<_T>::RandomInit(size_type __l) noexcept {
    auto seed = system_clock::now().time_since_epoch().count();
    default_random_engine engine(seed);
    uniform_real_distribution<_T> distribution(-1., 1.);

    _T *v = new _T[__l];
    
    for (int i = 0; i < __l; i++) {
        v[i] = distribution(engine);
    }
    return Vector(v, __l);
}

template<class _T>
auto Vector<_T>::RangeInit(_T __start, _T __end, _T __step) noexcept {
	size_type __l = int(((__end - __start) / __step)+0.9999);
    	_T *v = new _T[__l];

	for (size_type i = 0; i <= __l; i++) {
		v[i] = __start;
		__start += __step;
	}
	return Vector(v, __l);
}


template<class _T>
auto Vector<_T>::Batch(size_type __b_size) noexcept {
    size_type __b_count = this->vec_size / __b_size;
    _T **v = new _T*[__b_count];

    auto item  = this->Begin();
    for (int i = 0; i < __b_count; i++) {
        v[i] = new _T[__b_size];
        for (int j = 0; j < __b_size; j++) {
            v[i][j] = *item;
            item++;
        }
    }
    return Matrix2D(v, __b_count, __b_size);
}


template<class _T>
auto Vector<_T>::operator [] (int indx) const noexcept { return this->_vec[indx]; }


template<class _T>
void Vector<_T>::operator = (const Vector<_T>& y) const noexcept {
    this->_vec = y.Begin();
    this->vec_size = y.Size();
}


template<class _T>
auto Vector<_T>::operator + (const Vector<_T>& y) const noexcept {
    size_type __l = y.Size();
    _T *v = new _T[__l];

    const_iterator ref_x = this->Begin();
    const_iterator ref_y = y.Begin();

    _T* ref_v = v;
    while (ref_y != y.End()) {
        *ref_v = (*ref_x + *ref_y);
        ref_y++;
        ref_x++;
        ref_v++;
    }
    return Vector(v, __l);
}


template<class _T>
auto Vector<_T>::operator + (const _T &y) const noexcept {
    size_type __l = this->Size();
    _T *v = new _T[__l];

    const_iterator ref_x = this->Begin();

    _T* ref_v = v;
    while (ref_x != this->End()) {
        *ref_v = (*ref_x + y);
        ref_x++;
        ref_v++;
    }
    return Vector(v, __l);
}


template<class _T>
auto Vector<_T>::operator - (const Vector<_T>& y) const noexcept {
    size_type __l = y.Size();
    _T *v = new _T[__l];

    const_iterator ref_x = this->Begin();
    const_iterator ref_y = y.Begin();

    _T* ref_v = v;
    while (ref_y != y.End()) {
        *ref_v = (*ref_x - *ref_y);
        ref_y++;
        ref_x++;
        ref_v++;
    }
    return Vector(v, __l);
}


template<class _T>
auto Vector<_T>::operator - (const _T &y) const noexcept {
    size_type __l = this->Size();
    _T *v = new _T[__l];

    const_iterator ref_x = this->Begin();

    _T* ref_v = v;
    while (ref_x != this->End()) {
        *ref_v = (*ref_x - y);
        ref_x++;
        ref_v++;
    }
    return Vector(v, __l);
}


template<class _T>
auto Vector<_T>::operator * (const Vector<_T>& y) const noexcept {
    size_type __l = y.Size();
    _T *v = new _T[__l];

    const_iterator ref_x = this->Begin();
    const_iterator ref_y = y.Begin();

    _T* ref_v = v;
    while (ref_y != y.End()) {
        *ref_v = (*ref_x * *ref_y);
        ref_y++;
        ref_x++;
        ref_v++;
    }
    return Vector(v, __l);
}


template<class _T>
auto Vector<_T>::operator * (const _T &y) const noexcept {
    size_type __l = this->Size();
    _T *v = new _T[__l];

    const_iterator ref_x = this->Begin();

    _T* ref_v = v;
    while (ref_x != this->End()) {
        *ref_v = (*ref_x * y);
        ref_x++;
        ref_v++;
    }
    return Vector(v, __l);
}


template<class _T>
auto Vector<_T>::operator / (const Vector<_T>& y) const noexcept {
    size_type __l = y.Size();
    _T *v = new _T[__l];

    const_iterator ref_x = this->Begin();
    const_iterator ref_y = y.Begin();

    _T* ref_v = v;
    while (ref_y != y.End()) {
        *ref_v = (*ref_x / *ref_y);
        ref_y++;
        ref_x++;
        ref_v++;
    }
    return Vector(v, __l);
}


template<class _T>
auto Vector<_T>::operator / (const _T &y) const noexcept {
    size_type __l = this->Size();
    _T *v = new _T[__l];

    const_iterator ref_x = this->Begin();

    _T* ref_v = v;
    while (ref_x != this->End()) {
        *ref_v = (*ref_x / y);
        ref_x++;
        ref_v++;
    }
    return Vector(v, __l);
}
#endif // !_VECTOR_H_
