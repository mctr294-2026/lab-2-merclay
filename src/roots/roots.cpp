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
    double fa = f(a);  // f at a
    double fb = f(b);  // f at b
    if (fa * fb > 0.0) {  
        return false;
    }
    
    const double tol = 1e-6;           // Tolerance 
    const long long max_iter = 1000000; 
    
    long long iter_count = 0;
    
    while (iter_count < max_iter) {
        
        //  c = [a*f(b) - b*f(a)] / [f(b) - f(a)] 
        //if (std::abs(fb - fa) < 1e-12) { break; }  // Avoid divide-by-zero
        double c = (a * fb - b * fa) / (fb - fa);   
        
        //  Evaluate f(c), check tolerance
        double fc = f(c);
        if (std::abs(fc) <= tol) {     // |f(c)| ≤ tolerance?
            *root = c;                 // c is root!
            return true;               // SUCCESS yay!
        }
        
        // STEP 4: f(a), f(c) opposite? 
        if (fa * fc < 0.0) {           // f(a), f(c) opposite signs
            b = c;                     // Setting b = c 
            fb = fc;
        } else {                       // f(c), f(b) opposite signs  
            a = c;                     // Setting a = c 
            fa = fc;
        }
        
        ++iter_count;  //  Repeat
    }
    
    *root = 0.5 * (a + b);
    return false;
}
    


bool newton_raphson(std::function<double(double)> f,
                    std::function<double(double)> g,
                    double a, double b, double c,
                    double *root) {
    const double tol = 1e-6;
    const long long max_iter = 1000000;
    
    
    long long iter_count = 0;
    
    while (iter_count < max_iter) {
        // MATH: x_new = c - f(c)/f'(c)
        double fc = f(c);                          // f(c)
        double gc = g(c);                          // f'(c) 
        if (std::abs(gc) < 1e-12) { break; }       // Derivative too small
        
        double c_new = c - fc / gc;                //  Newton formula
        
        //Stay in bounds [a,b]
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
        
        c = c_new;  // Update guess
        ++iter_count;
    }
    
    *root = c;
    return false;
}

bool secant(std::function<double(double)> f,
            double a, double b, double c,
            double *root) {
            const double tol = 1e-6;
    const long long max_iter = 1000000;
    
    // Secant TWO points c and b as x0, x-1
    double x0 = c;  // Current guess
    double x1 = b;  // Prev guess

    long long iter_count = 0;
    
    while (iter_count < max_iter) {
        // MATH: x2 = x0 - f(x0) * (x0 - x1) / [f(x0) - f(x1)]
        double f0 = f(x0);
        double f1 = f(x1);
        if (std::abs(f0 - f1) < 1e-12) { break; }
        
        double x2 = x0 - f0 * (x0 - x1) / (f0 - f1);  //secant formula
        
        // Stay in bounds
        if (x2 < a || x2 > b) {
            *root = x0;
            return false;
        }
        
        double f2 = f(x2);
        if (std::abs(f2) <= tol) {
            *root = x2;
            return true;
        }
        
        // Shift: x1 ← x0, x0 ← x2
        x1 = x0;
        x0 = x2;
        ++iter_count;
    }
    
    *root = x0;
    return false;
}
    

