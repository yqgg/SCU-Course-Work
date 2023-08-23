#include "sequence.h"
#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>
using namespace std;

/* private:
    	node *head_ptr;
    	node *tail_ptr;
    	node *cursor;
    	node *precursor;
    	size_type many_nodes;

        void init();*/

namespace coen79_lab6 {
    void sequence::init() {
        head_ptr = NULL;
		tail_ptr = NULL;
		cursor = NULL;
		precursor = NULL;
		many_nodes = 0;
    }

    // CONSTRUCTORS and DESTRUCTOR
    sequence::sequence( ) {
        init();
    }

    //copy constructor
    sequence::sequence(const sequence& source) {
        init();
        *this = source;
    }
    sequence::~sequence( ) {
        list_clear(head_ptr);
        init();
    }

        
    // MODIFICATION MEMBER FUNCTIONS
    //     Postcondition: The precursor and cursor are adjusted such that the first
    //     item in the sequence becomes the current item (but if the sequence is
    //     empty, then there is no current item).
    void sequence::start( ) {
        if(head_ptr == NULL) return;
        else if (head_ptr == tail_ptr) {
            cursor = head_ptr;
            precursor = NULL;
        } else {
            cursor = head_ptr;
            precursor = NULL;
        }
    }

    //     Postcondition: The precursor and cursor are adjusted such that the last
    //     item in the sequence becomes the current item (but if the sequence is
    //     empty, then there is no current item).
    void sequence::end() {
        cursor = tail_ptr;
        if(head_ptr == tail_ptr) {
            precursor = NULL;
        } else {
            precursor = list_locate( head_ptr, many_nodes - 1);
        }
    }

    //     Precondition: is_item returns true.
    //     Postcondition: If the current item was already the last item in the
    //     sequence, then there is no longer any current item. Otherwise, the new
    //     current item is the item immediately after the original current item.
    void sequence::advance( ) {
        assert(is_item() == true);
        precursor = cursor;
        cursor = cursor->link();
    }

    //     Postcondition: A new copy of entry has been inserted in the sequence
    //     before the current item. If there was no current item, then the new entry
    //     has been inserted at the front of the sequence. In either case, the newly
    //     inserted item is now the current item of the sequence.
    void sequence::insert(const value_type& entry) {
        if(head_ptr == NULL) {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
        } else if ((is_item() && cursor == head_ptr) || !is_item()) { //if cursor is at head of list, or list is empty
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
        } else if (is_item() && cursor != head_ptr) {
            list_insert(precursor, entry);
            cursor = precursor->link();
        }
        many_nodes++;
    }

    //     Postcondition: A new copy of entry has been inserted in the sequence after
    //     the current item. If there was no current item, then the new entry has
    //     been attached to the end of the sequence. In either case, the newly
    //     inserted item is now the current item of the sequence.
    void sequence::attach(const value_type& entry) {
        if(head_ptr == NULL) {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
        } else if((is_item() && cursor == head_ptr) || is_item()) {
            list_insert(cursor, entry);
            precursor = cursor;
            cursor = cursor->link();
            tail_ptr = list_locate(head_ptr, many_nodes);
        } else {
            precursor = list_locate(head_ptr, many_nodes);
            list_insert(precursor, entry);
            cursor = precursor->link();
            tail_ptr = cursor;
        }
        many_nodes++;
    }


    void sequence::operator =(const sequence& source) {
    	list_clear(head_ptr);
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        many_nodes = source.size();
    }

    //     Precondition: is_item returns true.
    //     Postcondition: The current item has been removed from the sequence, and
    //     the item after this (if there is one) is now the new current item.
	void sequence::remove_current( ) {
        assert(is_item() == true);
        if(many_nodes > 1) {
            if(cursor == head_ptr) {
                list_head_remove(head_ptr);
                cursor = head_ptr;
            } else if (cursor == tail_ptr) {
                list_remove(precursor);
                cursor = precursor->link();
                tail_ptr = cursor;
            } else {
                list_remove(precursor);
                cursor = precursor->link();
            }
        } else if (many_nodes == 1) {
            list_remove(precursor);
            init();
        }
        many_nodes--;
    }
      
    // CONSTANT MEMBER FUNCTIONS
    //     Postcondition: The return value is the number of items in the sequence.
    sequence::size_type sequence::size( ) const {
        return many_nodes;
    }

    //     Postcondition: A true return value indicates that there is a valid
    //     "current" item that may be retrieved by activating the current
    //     member function (listed below). A false return value indicates that
    //     there is no valid current item.
    bool sequence::is_item( ) const {
        if(cursor == NULL) {
            return false;
        } else {
            return true;
        }
    }

    //     Precondition: is_item( ) returns true.
    //     Postcondition: The item returned is the current item in the sequence.   
    sequence::value_type sequence::current( ) const {
        assert(is_item() == true);
        return cursor->data();
    }
}