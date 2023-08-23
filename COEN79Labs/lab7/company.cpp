// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    //  company(const std::string& company_name);
    //   Precondition: company_name is a non-empty string
    //   Postcondition: The company object is initialized with "company_name"
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);
        // COMPLETE THE IMPLEMENTATION...
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    //Copy constructor
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);
        // COMPLETE THE IMPLEMENTATION...
        this->company_name = src.company_name;
        list_copy(src.get_head(), this->head_ptr, this->tail_ptr);
    }

    //Assignment operator
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);
        // COMPLETE THE IMPLEMENTATION...
        this->company_name = src.company_name;
        list_copy(src.get_head(), this->head_ptr, this->tail_ptr);
        return *this;
    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    //      Precondition: product_name is a non-empty string
    //      Postcondition: Creates and inserts a new node (product) to the back of the linked list.
    //      Returns true if successfully inserted, and returns false if there is a duplicate 
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            // COMPLETE THE IMPLEMENTATION...
            //std::cout << product_name << " inserted at head\n";
            list_init(head_ptr, tail_ptr, product_name, price);
            /*head_ptr = new node(product_name, price);
            tail_ptr = head_ptr;*/
        }
        else {
            // COMPLETE THE IMPLEMENTATION...
            //std::cout << product_name << " inserted at tail\n";
            list_tail_insert(tail_ptr, product_name, price);
            /*node *newProduct = new node(product_name, price);
            list_tail_insert(tail_ptr, product_name, price);*/
        }
        return true;
    }

    //      Postcondition:  Erases the product that its name matches product_name. Returns true if the
    //      product has been found and deleted, returns false otherwise
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);
        // COMPLETE THE IMPLEMENTATION...
        if(list_contains_item(head_ptr, product_name)) {
            node *temp = head_ptr;
            while(temp->getLink()->getName() != product_name) {
                temp = temp->getLink();
            }
            node *delete_p = temp;
            delete_p = delete_p->getLink();
            temp->setLink(delete_p->getLink());
            delete delete_p;
            return true;
        }
    }
    
    
}
