#include "roots.hpp"
#include <cmath>
#include <iostream>

bool bisection(std::function<double(double)> f,
               double a, double b,
               double *root) {
    const double tol = 1e-6; //acounting for how close to zero root needs to be
    const long long max_iter = 1000000; // max number of loops, high so it doesn't stop early 

    double fa= f(a); // f at left end
    double fb = f(b); //at right end
    //if loop for if there's no root
    if (fa * fb > 0.0) {
        return false;
    }
    long long iter_count = 0;
    
    while (iter_count < max_iter) {
        
        // Step 1: Compute midpoint
        double m = 0.5 * (a + b);
        
        // Step 2: Evaluate function at midpoint
        double fm = f(m);
        
        // Step 3: Check if good enough (success!)
        // fabs gives absolute value, doesnt miss (-)ives 
        if (std::abs(fm) <= tol) {
            *root = m;
            return true;
        }
        
        // Step 4: Decide which half contains root
        if (fa * fm < 0.0) {
            // Root is in left half [a, m] redfing function sides
            b = m;
            fb = fm;
        } else {
            // Root is in right half [m, b]
            a = m;
            fa = fm;
        }
    }
}

bool regula_falsi(std::function<double(double)> f,
                  double a, double b,
                  double *root) {
    
    return false;
}

bool newton_raphson(std::function<double(double)> f,
                    std::function<double(double)> g,
                    double a, double b, double c,
                    double *root) {
    return false;
}

bool secant(std::function<double(double)> f,
            double a, double b, double c,
            double *root) {
    return false;
}

