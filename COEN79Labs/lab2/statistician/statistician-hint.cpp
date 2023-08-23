// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician-hint.h"

using namespace std;

namespace coen79_lab2
{
	//Constructor
	statistician::statistician( )
    {
        //TO DO
        //In Constructor, initialize member variables' values
	reset();
    }
    
    void statistician::next(double r)
    {
        //TO DO
        //Think about what variables you need to update when the next function is called
	size++;
	total += r;
	if(min > r || size == 1) {
	    min = r;
	}
	if(max < r || size == 1) {
	    max = r;
	}
	avg = total/size;
    }
    
    void statistician::reset( )
    {
        //TO DO
        //Used for initialzing variables
	total = 0;
	size = 0;
	min = 0;
	max = 0;
	avg = 0;	
    }
    
    double statistician::mean( ) const
    {
        //TO DO
        //Only works when the sequence is not empty
	//assert(length() > 0);
	return avg;
    }
    
    double statistician::minimum( ) const
    {
        //TO DO
        //Only works when the sequence is not empty
	//assert(length() > 0);
	return min;
    }
    
    double statistician::maximum( ) const
    {
        //TO DO
        //Only works when the sequence is not empty
	//assert(length() > 0);
	return max;
    }
    
    //FRIEND function +
    statistician operator +(const statistician& s1, const statistician& s2)
    {
    	//TO DO
    	//The function returns a statistician object
    	//After combination, think about how to assign values to the returned object's member variables
	statistician s3;
	s3.total += s1.total + s2.total;
	s3.size += s1.size + s2.size;
	s3.avg += s3.total/s3.size;
	//find most min of both s1 and s2
	if(s1.min <= s2.min) {
	    s3.min = s1.min;
	} else if (s1.min > s2.min) {
	    s3.min = s2.min;
	}

	//find most max of both s1 and s2
	if(s1.max >= s2.max) {
	    s3.max = s1.max;
	} else if (s1.max < s2.max) {
	    s3.max = s2.max;
	}
	return s3;
    }
    
    //NON-MEMBER function ==
    bool operator ==(const statistician& s1, const statistician& s2)
    {
    	//TO DO
    	//2 situations:1. If at least one of the sequence is empty; 2. Both sequences are NOT empty
	if(s1.length()>0 && s2.length()>0) {
	    if(s1.length()==s2.length() && s1.sum()==s2.sum() && s1.minimum()==s2.minimum() && s1.maximum()==s2.maximum()) {
		return true;
	    }
	} else if (s1.length()==0 && s2.length()==0) {
	    return true;
	} else {
	    return false;
	}
    }
    
    //FRIEND function *
    statistician operator *(double scale, const statistician& p)
    {
    	//TO DO
    	//The function returns a statistician object
    	//Pay attention to the scale, it could be either positive or negative       
        //Assume we have 4 and -2 added to the object
        //The total is 2
        //If the scale is 4, then the total will be 8, and if the scale is -4, the total will be -8
        //If the scale is 4, then the largest and tiniest will be the same, if the scale is -4, the largest becomes the tiniest and the tiniest becomes the largest
        //Therefore, you need to distinguish between these 2 situations
	statistician s3;
	s3.total = p.total * scale;
	s3.avg = p.avg * scale;
	//s3.size = p.size * scale;
	if(scale < 0) {
	    s3.min = p.max * scale;
	    s3.max = p.min * scale;
	} else {
	    s3.min = p.min * scale;
	    s3.max = p.max * scale;
	}
	return s3;
    }
}


