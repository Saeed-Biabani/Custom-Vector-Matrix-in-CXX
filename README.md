# Custom-Vector-Matrix-in-CXX
## Vector Usage
### Include
```cpp
#include "Vector.hpp"
```
### Initial Vector Manualy
```cpp
Vector<float> vec = {1, 2, 3, 4, 5};
cout<<"Vector : "<<vec;
```
> Vector : [ 1 2 3 4 5 ]

### Initial Vector with '0'
```cpp
// Vector<float>::ZeroInit(array_length);
Vector vec = Vector<float>::ZeroInit(10);
cout<<"Vector : "<<vec;
```
> Vector : [ 0 0 0 0 0 0 0 0 0 0 ]

### Initial Vector with '1'
```cpp
// Vector<float>::OneInit(array_length);
Vector vec = Vector<float>::OneInit(10);
cout<<"Vector : "<<vec;
```
> Vector : [ 1 1 1 1 1 1 1 1 1 1 ]

### Initial Vector with Random Numbers (Normal distribution)
```cpp
// Vector<float>::RandomInit(array_length);
Vector vec = Vector<float>::RandomInit(10);
cout<<"Vector : "<<vec;
```
> Vector : [ 0.723249 -0.354442 0.891144 -0.535483 0.13508 0.296572 0.487943 0.855433 -0.743702 0.60426 ]

### Initial Vector with RangeInit
```cpp
// Vector<float>::RangeInit(start, end, step);
Vector vec = Vector<float>::RangeInit(0, 10, 2);
cout<<"Vector : "<<vec;
```
> Vector : [ 0 2 4 6 8 ]

### Size Method
```cpp
Vector<float> vec = {1, 2, 3, 4 ,5};
cout<<"Vector Size : "<<vec.Size();
```
> Vector Size : 5

### Begin Method
```cpp
Vector<float> vec = {1, 2, 3, 4 ,5};
cout<<"Vector Begin : "<<vec.Begin();
```
> Returns the address of the first element of the vector

### End Method
```cpp
Vector<float> vec = {1, 2, 3, 4 ,5};
cout<<"Vector End : "<<vec.End();
```
> Returns the address of the last element of the vector

### STD (Standard deviation) Method
```cpp
Vector vec = Vector<float>::RandomInit(10);
cout<<"Vector standard deviation : "<<vec.STD();
```
> calculate standard deviation of the vector elements

### Mean Method
```cpp
Vector vec = Vector<float>::RandomInit(10);
cout<<"Vector Mean : "<<vec.Mean();
```
> calculate mean of the vector elements

### Min Method
```cpp
Vector vec = Vector<float>::RandomInit(10);
cout<<"Vector Min : "<<vec.Min();
```
> find min element of the vector

### Max Method
```cpp
Vector vec = Vector<float>::RandomInit(10);
cout<<"Vector Max : "<<vec.Max();
```
> find Max element of the vector

### Argmax Method
```cpp
Vector vec = Vector<float>::RandomInit(10);
cout<<"Vector Argmax : "<<vec.Argmax();
```
> return the index of the max element of the vector

### Batch Method
```cpp
Vector vec = Vector<float>::RandomInit(15);    
cout<<"Vector : "<<vec;

Matrix2D batched_vector = vec.Batch(3);
cout<<"Batched Vector (Matrix2D) : "<<endl<<batched_vector;
```
> Vector : [ -0.954977 -0.293635 0.868507 0.997847 0.815752 0.347206 -0.512109 0.987668 -0.259038 0.352951 0.0504647 0.160784 0.300369 0.297537 0.698983 ]

> Batched Vector (Matrix2D) :

> -0.954977  -0.293635  0.868507  
> 0.997847  0.815752  0.347206  
> -0.512109  0.987668  -0.259038  
> 0.352951  0.0504647  0.160784  
> 0.300369  0.297537  0.698983

### + Operator
```cpp
Vector vec = Vector<float>::RangeInit(0, 10, 2);
Vector sum = vec + 2;
cout<<"sum : "<<sum;
```
> sum : [ 2 4 6 8 10 ]

### + Operator
```cpp
Vector<float> vec_1 = {1, 2, 3, 4};
Vector<float> vec_2 = {9, 8, 7, 6};
Vector sum = vec_1 + vec_2;
cout<<"Vector : "<<sum;
```
> Vector : [ 10 10 10 10 ]

### Other Operators (-, *, /)