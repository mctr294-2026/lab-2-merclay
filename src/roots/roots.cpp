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
    const double tol = 1e-6; // accounting for how close to zero root needs to be
    const long long max_iter = 1000000;

    double fa = f(a); // f at left end
    double fb = f(b); // at right end
    
    // if loop for if there's no root checks for no sign change 
    if (fa * fb > 0.0) {
        return false;
    }
    //computing false position point
    double c = (a * fb - b * fa) / (fb - fa);
    double fc = f(c);

    long long iter_count = 0;
    
    while (iter_count < max_iter) {
        //formula
        double c = (a * fb - b * fa) /(fb-fa);
        // Convergence tests 
        if (std::fabs(fc) < tol) {
             *root = c;
              return true;

         // MATH: If f(a)*f(c) < 0, root in [a,c], else root in [c,b]
        if (fa * fc < 0.0) {
            b = c; fb = fc;  // Shrink to [a,c]
        } else {
            a = c; fa = fc;  // Shrink to [c,b]
        }
        
        ++iter_count;
    }
    
    *root = 0.5 * (a + b);
    return false;
        }
    
}

bool newton_raphson(std::function<double(double)> f,
                    std::function<double(double)> g,
                    double a, double b, double c,
                    double *root) {
    const double tol = 1e-6;
    const long long max_iter = 1000000;
    
    // No bracketing check (Newton doesn't guarantee bracket)
    
    long long iter_count = 0;
    
    while (iter_count < max_iter) {
        // ========== MATH → CODE TRANSLATION ==========
        // MATH: x_new = c - f(c)/f'(c)
        double fc = f(c);                          // f(c)
        double gc = g(c);                          // f'(c) ← NEW!
        if (std::abs(gc) < 1e-12) { break; }       // Derivative too small
        
        double c_new = c - fc / gc;                // ← EXACT Newton formula
        
        // NEW: Stay in bounds [a,b]
        if (c_new < a || c_new > b) {
            *root = c;
            return false;  // Left interval
        }
        
        // Check success
        double f_new = f(c_new);
        if (std::abs(f_new) <= tol) {
            *root = c_new;
            return true;
        }
        
        c = c_new;  // Update guess (NO bracketing!)
        ++iter_count;
    }
    
    *root = c;
    return false;
}

bool secant(std::function<double(double)> f,
            double a, double b, double c,
            double *root) {
    return false;
}

