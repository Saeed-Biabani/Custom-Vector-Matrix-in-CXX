#include <iostream>
#include <fstream>

#include "Vector.hpp"
#include "Matrix2D.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    Vector vec = Vector<float>::RandomInit(100);

    cout<<"Vector : "<<vec;
    cout<<endl<<endl;
    
    auto normalized_vec = (vec - vec.Mean()) / vec.STD();

    cout<<"Normalized Vector Mean : "<<normalized_vec.Mean()<<endl<<endl;
    cout<<"Normalized Vector STD: "<<normalized_vec.STD()<<endl<<endl;

    auto batched_vec = vec.Batch(10); //convert vector to matrix

    cout<<"Matrix : "<<endl;
    cout<<batched_vec;
    cout<<endl;

    auto normalized_mat = (batched_vec - batched_vec.Mean(Axis2D::COL)) / batched_vec.STD(Axis2D::COL);

    cout<<"Normalized Matrix Mean : "<<normalized_mat.Mean(Axis2D::COL);
    cout<<endl<<endl;

    cout<<"Normalized Matrix STD : "<<normalized_mat.STD(Axis2D::COL);
    cout<<endl<<endl;

    return 0;
}