/*
    Edited example from dlib optimization to test lgbfs
*/
#include "./dlib/optimization.h"
#include "./dlib/global_optimization.h"
#include <iostream>

using namespace std;
using namespace dlib;


// Represents input to objective functions
typedef matrix<double,0,1> column_vector;

//---------------------------------------------
//Rosenbrock's function to test optimization on
double rosen (const column_vector& m)
{
    const double x = m(0); 
    const double y = m(1);

    // compute Rosenbrock's function and return the result
    return 100.0*pow(y - x*x,2) + pow(1 - x,2);
}

// This is a helper function used while optimizing the rosen() function.  
const column_vector rosen_derivative (const column_vector& m)
/*!
    ensures
        - returns the gradient vector for the rosen function
!*/
{
    const double x = m(0);
    const double y = m(1);

    // make us a column vector of length 2
    column_vector res(2);

    // now compute the gradient vector
    res(0) = -400*x*(y-x*x) - 2*(1-x); // derivative of rosen() with respect to x
    res(1) = 200*(y-x*x);              // derivative of rosen() with respect to y
    return res;
}

// This function computes the Hessian matrix for the rosen() fuction.  This is
// the matrix of second derivatives.
matrix<double> rosen_hessian (const column_vector& m)
{
    const double x = m(0);
    const double y = m(1);

    matrix<double> res(2,2);

    //second derivatives 
    res(0,0) = 1200*x*x - 400*y + 2; // second derivative with respect to x
    res(1,0) = res(0,1) = -400*x;   // derivative with respect to x and y
    res(1,1) = 200;                 // second derivative with respect to y
    return res;
}

class rosen_model 
{
public:
    typedef ::column_vector column_vector;
    typedef matrix<double> general_matrix;

    double operator() (
        const column_vector& x
    ) const { return rosen(x); }

    void get_derivative_and_hessian (
        const column_vector& x,
        column_vector& der,
        general_matrix& hess
    ) const
    {
        der = rosen_derivative(x);
        hess = rosen_hessian(x);
    }
};
//-------------------------------------------------

int main() try
{
    //After find_min finishes, starting_point contains optimum point.
    column_vector starting_point = {4, 8};

    //#fixme: Remove .be_verbose() when actually deploying
    cout << "lbfgs with known derivative: " << endl;
    starting_point = {0.8, 1.3};
    find_min(lbfgs_search_strategy(10), 
             objective_delta_stop_strategy(1e-7).be_verbose(),rosen, rosen_derivative, starting_point, -1);
    cout << endl << "rosen solution: \n" << starting_point << endl;

    //Lbfgs but when we don't know the derivative of the provided function
    cout << "lbfgs with approx. derivative" << endl;
    starting_point = {-94, 5.2};
    find_min_using_approximate_derivatives(lbfgs_search_strategy(10),
                                           objective_delta_stop_strategy(1e-7),
                                           rosen, starting_point, -1);
    cout << "rosen solution: \n"<< starting_point << endl;
}
catch (std::exception& e)
{
    cout << e.what() << endl;
}

