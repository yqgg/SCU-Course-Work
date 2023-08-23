// FILE: rand_gen.cpp
// CLASS IMPLEMENTED: rand_gen (see rand_gen.h for documentation)

#include "random-hint.h"
#include <cassert>
#include <iostream>
using namespace std;
//using namespace coen79_lab2;

namespace coen79_lab2 {
    
    //Constructor
    rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus) {
        //TO DO
        //Don't forget to check the precondition
	this->seed = seed;
	this->multiplier = multiplier;
	this->increment = increment;
	this->modulus = modulus;
    }
    
    void rand_gen::set_seed(int new_seed) {
        //TO DO
	this->seed = new_seed;
    }
    
    int rand_gen::next() {
        //TO DO
	int next_seed = (this->multiplier * this->seed + this->increment) % this->modulus;
	this->seed = next_seed;
	return next_seed;
    }
    
    void rand_gen::print_info() {
        //TO DO
	cout << "Values of the private member variables:";
	cout <<	"\nSeed: " << seed;
	cout << "\nMultiplier: " << multiplier;
	cout << "\nIncrement: " << increment;
	cout << "\nModulus: " << modulus;
    }
}
