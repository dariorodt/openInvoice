// Client.h
#ifndef CLIENT_H
#define CLIENT_H

#include "utils.hpp"
using namespace std;

class Client {
	friend class Invoice;

	private: // All private members

	string id, name, address, phone1, phone2;
	
	public: // All public members

	Client(string id,string name,string address,string phone1,string phone2) {
		this->id = id;
		this->name = name;
		this->address = address;
		this->phone1 = phone1;
		this->phone2 = phone2;
	};
	Client() {}
	~Client() {}

	string get_id() { return id; }
	string get_name() { return name; }
	string get_address() { return address; }
	string get_phone1() { return phone1; }
	string get_phone2() { return phone2; }

    string to_string() {
        string cadena = id + ";" + name + ";" + address + ";" + phone1 + ";" + phone2;
        return cadena;
    }

	protected: // All protected members

    void set_id(string id) { this->id = id; }
    void set_name(string name) { this->name = name; }
    void set_address(string address) { this->address = address; }
    void set_phone1(string phone1) { this->phone1 = phone1; }
    void set_phone2(string phone2) { this->phone2 = phone2; }
};

#endif
