// FILE: poly.cpp
//
// 
// 
//
//
// NOTE: current_degree is always equal to the largest exponent with a non-zero
//          coefficient. If all coeficients are 0.0, then current_degree is 0.

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <climits>
#include "poly_hint.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4
{
    // CONSTANTS
    const unsigned int polynomial::MAXDEGREE;

    // HELPER FUNCTIONS
    void polynomial::update_current_degree() {
        //set current degree to the index of the item with the maximum degree
	for(int i = MAXDEGREE; i >= 0; i--) {
	    if(coef[i] != 0) {
		current_degree = i;
		break;
	    }
	}
	current_degree = 0;
    }

    // CONSTRUCTOR
    polynomial::polynomial(double c, unsigned int exponent){
        //check MAXIMUM_DEGREE first
        //all coefficients should set to be 0 except for the specified one
        //don't forget to set the current_degree pointing to it
		//clear();
	assert(exponent <= MAXDEGREE);
	for(int i = 0; i<=MAXDEGREE; i++) {
	    coef[i] = 0;
	}
	coef[exponent] =c;
	current_degree = exponent;
    }

	// MODIFICATION MEMBER FUNCTIONS
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        //check MAXIMUM_DEGREE first
        //assign the coefficient, update the current_degree if necessary
	assert(exponent <= MAXDEGREE);
	coef[exponent] = coefficient;
	    //std::cout << exponent << std::endl;
	    //std::cout << coefficient <<std::endl;
	update_current_degree();
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent){
        //check MAXIMUM_DEGREE first
        //update the coefficient of the specified exponent
	assert(exponent <= MAXDEGREE);
	coef[exponent] += amount;
	update_current_degree();
    }
    void polynomial::clear( ) {
        // Zero out all the coeficients.
        //don't forget to reset the current_degree
	for(int i = 0; i<=MAXDEGREE; i++){
	    coef[i] = 0;
	}
        current_degree = 0;
    }
	// // CONSTANT MEMBER FUNCTIONS
    polynomial polynomial::antiderivative( ) const {
	assert(degree() <= MAXDEGREE);
	polynomial temp;
	for(int i = 0; i <= current_degree; i++){
	    temp.assign_coef(coef[i]/(i+1), i+1);
	}
	temp.current_degree = current_degree + 1;
	return temp;
    }

    double polynomial::coefficient(unsigned int exponent) const {
        // Always return 0.0 if exponent is greater than maximum degree.
        if(exponent > MAXDEGREE)
            return 0;
	else 
	    return coef[exponent];	
    }

    double polynomial::definite_integral(double x0, double x1) const {
	polynomial temp = this->antiderivative();
	double r = temp.eval(x1) - temp.eval(x0);
	return r;
	
	/*double upper = 0;
	double lower = 0;
	for(int i = 0; i< MAXDEGREE; i++) {
	    upper += (temp.coef[i] * pow(x1,i));
	    lower += (temp.coef[i] * pow(x0,i));
	}
	return (upper - lower);*/
    }

    polynomial polynomial::derivative( ) const {
	polynomial temp;
	for(int i = 1; i <= current_degree; i++) {
	    temp.assign_coef((double)i * coef[i], i-1);
	}
	temp.current_degree = current_degree - 1;
	//temp.update_current_degree();
	return temp;
		
		/*polynomial temp;
		for(int i = MAXDEGREE; i>0; --i){
			//temp.assign_coef( e * coefficient(e),e-1);
			temp.coef[i] = (coef[i]*i);
		}
		for(int i = 0; i<= MAXDEGREE-1; i++) {
			temp.coef[i] = temp.coef[i+1];
		}
		temp.update_current_degree();
		return temp;*/
    }

    double polynomial::eval(double x) const {
        //a specified value for x is given
	double res = 0.0;
	for(int i = 0; i<= current_degree; i++){
	    int n = coef[i];
	    for(int j = 0; j < i; j++) {
		n = n*x;
	    }
	    res += n;
	}
	return res;
    }

    bool polynomial::is_zero( ) const {
        //whether it is a zero polynomial
	return (current_degree == 0 && coef[0] == 0);
    }

    unsigned int polynomial::next_term(unsigned int e) const {
        //return the next valid exponent
        //otherwise return 0
	for(int i = e+1; i<=MAXDEGREE; i++){
	    if(coef[i] != 0)
		return i;
	}
	return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const {
        //return the previous valid exponent
        //otherwise retun UINT_MAX
	for(int i = e-1; i >= 0; i--){
	    if(coef[i] != 0)
		return i;
	}
	return UINT_MAX;
    }

    // // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2) {
	polynomial temp;
	int max;
	if(p1.degree() > p2.degree())
	    max = p1.degree();
	else
	    max = p2.degree();
	for(int i = 0; i <= max; i++) {
	    temp.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
	}
	return temp;
	/*polynomial temp;
	for(int i = 0; i<=polynomial::MAXDEGREE; i++) {
	    temp.coef[i] = (p1.coef[i] + p2.coef[i]);
	}
	return temp;*/
		/*polynomial temp;
		for(int i =0;i <= fmax(p1.degree(),p2.degree()); i++){
			temp.assign_coef(p1.coefficient(i) + p2.coefficient(i),i);
		}
		temp.update_current_degree();	
		return temp;*/
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) {
	polynomial temp;
	int max;
	if(p1.degree() > p2.degree())
	    max = p1.degree();
	else 
	    max = p2.degree();
	for(int i = 0; i<=max; i++) {
	   temp.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
	}
	return temp;
		
		/*polynomial temp;
		for(int i =0;i <= fmax(p1.degree(),p2.degree()); i++){
			temp.assign_coef(p1.coefficient(i) - p2.coefficient(i),i);
		}
		temp.update_current_degree();
		return temp;	*/
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        //for *, need to check the MAXIMUM_DEGREE
	assert(p1.degree()+p2.degree() <= polynomial::MAXDEGREE);
	polynomial temp;
	for(int i = 0; i<=p1.degree(); i++) {
	    for(int j =0; j<= p2.degree(); j++) {
		temp.add_to_coef(p1.coefficient(i)*p2.coefficient(j), i+j);
	    }
	}
	return temp;
		/*polynomial temp;
		for(int e1 = 0; e1 <= p1.degree();e1++){
			for(int e2 = 0; e2<=p2.degree();e2++){
				double oc = temp.coefficient(e1+e2);
				double tc = p1.coefficient(e1) * p2.coefficient(e2);
				temp.assign_coef(oc+tc,e1+e2);
			}
		}
		temp.update_current_degree();
		return temp;*/
    }

    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p) {
	int deg = p.degree();
	if(deg > 1) {
	    out << p.coefficient(deg) << "x^" << deg;
	    deg--;
	    while(deg != 1) {
		if(p.coefficient(deg) > 0) {
		    out << " + " << p.coefficient(deg) << "x^" << deg;
		} else if (p.coefficient(deg) < 0) {
		    out << " - " << abs(p.coefficient(deg)) << "x" << deg;
		}
		deg--;
	    }
	    if(p.coefficient(deg) > 0) {
		out << " + " << p.coefficient(deg) << "x";
	    } else if(p.coefficient(deg) < 0) {
		out << " - " << abs(p.coefficient(deg)) << "x";
	    }
	    deg--;
	    if(p.coefficient(deg) > 0) {
		out << " + " << p.coefficient(deg);
	    } else if(p.coefficient(deg) < 0) {
		out << " - " << abs(p.coefficient(deg));
	    }
	} else if (deg == 1) {
	    out << p.coefficient(1) << "x";
	    if(p.coefficient(0) > 0) {
		out << " + " << p.coefficient(0);
	    } else if(p.coefficient(0) < 0) {
		out << " - " << abs(p.coefficient(deg));
	    }
	} else {
	    out << p.coefficient(0);
	}
	return out;
		/*if(p.is_zero()){
			out << "0.0";
			return out;
		}
		for(int i = p.degree(); i > -1; --i) {
			if(p.coefficient(i) != 0) {
				if(p.coefficient(i) < 0) {
					out << " - ";
				} else if (i != p.degree() && p.coefficient(i) >0) {
					out < " + ";
				}
				out << fixed << setprecision(1) << abs(p.coefficient(i));
				if(i != 1 && i!=0) {
					out << "x^" << i;
				} else {
					out << "x";
				}
			}
		}
		out << setprecision(1);
		return out;*/
		/*char sign;
		if(p.degree() == 0){
			std::cout << p.coefficient(0);
			return out;
		}
		std::cout << p.coefficient(p.degree()) << "x^" << p.degree();
		for(int i = p.degree()-1; i > 1; i--){
			if(p.coefficient(i) == 0)
				continue;
			if(p.coefficient(i) < 0)
				sign = '-';
			else
				sign = '+';
			std::cout << ' ' << sign << ' ' <<  std::abs(p.coefficient(i)) << "x^" << i;
		}
		if(p.coefficient(1) != 0){
			if(p.coefficient(1) < 0)
				std::cout << ' ';// << '-';
			else
				std::cout << ' ' << '+';
			std::cout << ' ' << p.coefficient(1) << "x";
		}
		if(p.coefficient(0) != 0){
			if(p.coefficient(0) < 0)
				std::cout << ' ';//'-';
			else 
				std::cout << ' ' << '+';
			std::cout << ' ' << p.coefficient(0) << std::endl;
		}
		return out;
		*/
    }
}
