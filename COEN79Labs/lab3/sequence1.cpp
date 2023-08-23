#include "sequence1.h"
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

//Pre and post conditions in "sequence1.h"
namespace coen79_lab3 {
    //constructor
    sequence::sequence() {
	this->used = 0;
	this->current_index = 0;
    }

    void sequence::start() {
	current_index = 0;
    }

    void sequence::end() {
	if(used != 0) {
	    current_index = used-1;
	} else {
	    current_index = 0;
	}
    }

    void sequence::last() {
	current_index = CAPACITY-1;
    }

    void sequence::advance() {
	assert(is_item());
	if(current_index != CAPACITY-1) {
	    current_index += 1;
	} else {
	    cout << "Current_index is at end of sequence.\n";
	}
    }
    
    void sequence::retreat() {
	if(current_index != 0) {
	    current_index -= 1;
	}
    }

    void sequence::insert(const value_type& entry) {
	assert(size() < CAPACITY);
	if(used == 0) { //set current_index to 0 if there are not items in the sequence 
	    current_index = 0;
	} else {
	    //shift every item on the rhs of the current_index and the item at current_index one index to the right
	    for(int i = used; i>current_index; i--) {
		data[i] = data[i-1];
	    }
	}
	data[current_index] = entry; //insert entry into sequence at current_index
	used++;
    }

    void sequence::attach(const value_type& entry) {
	assert(size() < CAPACITY);
	if(used == 0) { //if there are not items in the sequence, attach entry to the end of the sequence
	    data[CAPACITY-1] = entry;
	    last();
	} else {
	    //shift every item on the rhs of the current_index one index to the right
	    for(int i = used; i>current_index+1; i--) {
		data[i] = data[i-1];
	    }
	    current_index++;
	    data[current_index] = entry;
	}
	used++;
    }

    void sequence::remove_current() {
	assert(is_item());
	    //shift every item on the rhs of current_index to the left one index
	for(int i = current_index+1; i<used; i++) {
	    data[i-1] = data[i];
	}
	used--;
    }

    void sequence::insert_front(const value_type& entry) {
	assert(size() < CAPACITY);
	start();
	insert(entry);
	used++;
    }

    void sequence::attach_back(const value_type& entry) {
	assert(size() < CAPACITY);
	current_index = used;
	data[current_index] = entry;
	used++;
    }

    void sequence::remove_front() {
	assert(is_item());
	start();
	for(int i = 0; i<used; i++) { //shift every item to the left oneto fill the empty spot
	    data[i-1] = data[i];
	}
	used--;
    }

    void sequence::operator +=(const sequence& rhs) {
	assert((used+rhs.size()) < CAPACITY);
	size_type temp = rhs.used;
	for(int i = 0; i<temp; i++) {
	    data[used++] = rhs.data[i];
	}
    }

    sequence::size_type sequence::size() const {
	return used;
    }

    bool sequence::is_item() const{
	if(current_index < size()) {
	    return true;
	} else {
	    return false;
	}
    }

    sequence::value_type sequence::current() const {
	assert(is_item());
	return data[current_index];
    }

    sequence::value_type sequence::operator[](int index) const {
	assert(index < used);
	return data[index];
    }

    double sequence::mean() const {
	value_type sum = 0;
	for(int i = 0; i<used; i++) {
	    sum += data[i];
	} 
	return (sum/used);
    }

    double sequence::standardDeviation() const {
	double m = mean();
	double stdv = 0;
	for(int i = 0; i<used; i++) {
	    stdv += pow((data[i] - m),2);
	}
	stdv = sqrt(stdv/used);
	return stdv;
    }

    sequence operator +(const sequence& lhs, const sequence& rhs) {
	//lhs.end(); //iterator pointint to last item
	sequence newSeq(lhs);
	sequence r(rhs);
	r.start();
	for(int i = 0; i<r.size(); i++) {
	    newSeq.attach_back(r.current()); //insert rhs[i] to back of lhs sequence
	    r.advance();
	}
	return newSeq;
    }

    sequence::value_type summation(const sequence &s) {
	return s.mean() * s.size();
    }
}
