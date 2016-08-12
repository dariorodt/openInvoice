// Item.h
#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <sstream>
#include "utils.hpp"


using namespace std;

class Item {
    friend class Invoice;

	private: // All private members

		string item_id;
	    string item_desript;
	    double item_price;
	    double item_quantity;
	    double item_total;

	public: // All public members
	
	Item(string item_id, string item_desript, double item_price, double item_quantity) {
        (*this).item_id = item_id;
        (*this).item_desript = item_desript;
        (*this).item_price = item_price;
        (*this).item_quantity = item_quantity;
        (*this).item_total = item_price * item_quantity;
    }
    Item() {
        (*this).item_id = "";
        (*this).item_desript = "";
        (*this).item_price = 0.0;
        (*this).item_quantity = 0.0;
        (*this).item_total = 0.0;
    }
	~Item() {}
	
	string get_item_id(){ return item_id; }
    string get_item_desript(){ return item_desript; }
    double get_item_price(){ return item_price; }
    double get_item_quantity(){ return item_quantity; }
    double get_item_total(){ return item_total; }

    string to_string() {
    	ostringstream stm ;
        stm << item_id << ";"
        	<< item_desript << ";"
        	<< item_price << ";"
        	<< item_quantity << ";"
        	<< item_total;
        return stm.str();
    }
};
#endif