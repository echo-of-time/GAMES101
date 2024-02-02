#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include<iostream>

using std::cout;

int main(){

    // Basic Example of cpp
    std::cout << "Example of cpp \n";
    float a = 1.0, b = 2.0;
    std::cout << a << std::endl;
    std::cout << a/b << std::endl;
    std::cout << std::sqrt(b) << std::endl;
    std::cout << std::acos(-1) << std::endl;
    std::cout << std::sin(30.0/180.0*acos(-1)) << std::endl;

    // Example of vector
    std::cout << "Example of vector \n";
    // vector definition
    Eigen::Vector3f v(1.0f,2.0f,3.0f);
    Eigen::Vector3f w(1.0f,0.0f,0.0f);
    // vector output
    std::cout << "Example of output \n";
    std::cout << v << std::endl;
    // vector add
    std::cout << "Example of add \n";
    std::cout << v + w << std::endl;
    // vector scalar multiply
    std::cout << "Example of scalar multiply \n";
    std::cout << v * 3.0f << std::endl;
    std::cout << 2.0f * v << std::endl;

    // Example of matrix
    std::cout << "Example of matrix \n";
    // matrix definition
    Eigen::Matrix3f i,j;
    i << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
    j << 2.0, 3.0, 1.0, 4.0, 6.0, 5.0, 9.0, 7.0, 8.0;
    // matrix output
    std::cout << "Example of output \n";
    std::cout << i << std::endl;
    // matrix add i + j
    std::cout << "Example of matrix add \n";
    std::cout << i + j << '\n';
    // matrix scalar multiply i * 2.0
    std::cout << "Example of scalar multiply \n";
    std::cout << i * 2.0 << '\n';
    // matrix multiply i * j
    std::cout << "Example of matrix multiply \n";
    std::cout << i * j << '\n';
    // matrix multiply vector i * v
    std::cout << "Example of matrix multiply vector \n";
    std::cout << i * v << '\n';

    // pa0_3.1
    cout << "This is the process of pa0_3.1\n";
    // build point p(2,1)
    Eigen::Vector3f p(2.0, 1.0, 0.0);
    // float prepare
    float sqrt2 = std::sqrt(2);
    // build Rotation matrix r, Translation matrix t, compound matrix c
    Eigen::Matrix3f r, t, c;
    r << sqrt2, -sqrt2, 0, sqrt2, sqrt2, 0, 0, 0, 1;
    t << 1, 0, 1, 0, 1, 2, 0, 0, 1;
    c = t * r;
    // print result
    cout << "result after p(2,1) transfered:\n" << c * p << '\n';
    return 0;
}