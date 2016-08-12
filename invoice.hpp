// invoice.h
#ifndef INVOICE_HPP
#define INVOICE_HPP

#include <list>
#include <fstream>
#include <ctime>
//#include <string>
#include "item.hpp"
#include "client.hpp"
using namespace std;

enum FileType { PLAIN, JSON, XML, BINARY };
enum InvoiceState { ACTIVE, CLOSED, CANCELED, ANULATED };

class Invoice {

	/*	NOTA IMPORTANTE: ************************************************************
		Hay que revisar la pertinencia de algunos métodos en el modelo de documento.
		
		Todos los procesos que puedan colocarse en un archivo separado deben ser 
		removidos y trasladados a dicho archivo. Hay que evaluar si es necesario 
		diseñar una clase con las funciones de uso general.
		
		Por lo pronto, en este archivo sólo deben quedar aquellos métodos que estén 
		directamente relacionados con los procésos intrínsecos al documento, como 
		por ejemplo, los de formatting y parsing, y los de proceso y computo interno.
		*/



	/*	Todo: **********************************************************************
		Falta cagar la lista de items. Ref: M9380L. */

	// Todo: string json_string() {} // Returns a JSON serialized string.
	// Todo: Implementar un metodo para conactarse a un a Base de Datos.
	// Todo: Crear los metodos necesarios para trabajas desde una base de tatos.
	// dbSearch(), dbLoad(), dbUpdate(), dbAppend(), dbDelete().

private: // All private members
	
	// FIELDS AND PROPERTIES ==================================================================

	FileType file_type = PLAIN;
	string invoice_number;
	string invoice_date;
	string invoice_time;
	string budget_number;
	string control_number;
	string file_name;
	
	double sub_total;
	double tax;
	double total;
	
	Client client;
	
	list<Item> items;
	
	bool active;
	bool paid;
    
    time_t now;
    struct tm * date_time;
	
	ostringstream stmstr;
	char colon = ';';
	char comma = ',';


public: // All Public members


	// CONSTRUCTORS ===========================================================================

	
	Invoice(string invoice_number, string budget_number, string control_number, Client client)
	: tax(1.12), active(true), paid(false) {

        this->invoice_number = invoice_number;
        this->file_name = invoice_number + ".invoice";
        this->budget_number = budget_number;
        this->control_number = control_number;

        // Generate date
        time(&now);
        date_time = localtime(&now);
        stmstr.str("");
        stmstr << date_time->tm_hour << ":"<< date_time->tm_min;
        this->invoice_time = stmstr.str();
        stmstr.str("");
        stmstr << date_time->tm_mday << "-" << date_time->tm_mon << "-" << (date_time->tm_year + 1900);
        this->invoice_date = stmstr.str();

        this->client = client;
    };

    
	Invoice(string fn) {
		file_name = fn;
		string tmpStr;
		fstream current_file(file_name, fstream::in);
		
		// Load invoice header fields
		getline(current_file, tmpStr);
		file_type = (FileType)str_to_int(tmpStr);
		getline(current_file, invoice_number, colon);
		getline(current_file, invoice_date, colon);
		getline(current_file, invoice_time, colon);
		getline(current_file, budget_number, colon);
		getline(current_file, control_number);

		// Load client
		getline(current_file, tmpStr, colon);
		client.set_id(tmpStr);
		getline(current_file, tmpStr, colon);
		client.set_name(tmpStr);
		getline(current_file, tmpStr, colon);
		client.set_address(tmpStr);
		getline(current_file, tmpStr, colon);
		client.set_phone1(tmpStr);
		getline(current_file, tmpStr);
		client.set_phone2(tmpStr);
		
		// Load invoice footer fields
		getline(current_file, tmpStr, colon);
		sub_total = str_to_double(tmpStr);
		getline(current_file, tmpStr, colon);
		tax = str_to_double(tmpStr);
		getline(current_file, tmpStr, colon);
		total = str_to_double(tmpStr);
		getline(current_file, tmpStr, colon);
		active = (bool)str_to_int(tmpStr);
		getline(current_file, tmpStr, colon);
		paid = (bool)str_to_int(tmpStr);

		// M9380L
		
		current_file.close();
	}

	~Invoice();




	// GETTERS ====================================================================================


    string get_file_name() { return file_name; } 

    string get_invoice_number() { return invoice_number; } 

	string get_invoice_date() { return invoice_date; } 

    string get_invoice_time() { return invoice_time; } 

    string get_budget_number() { return budget_number; } 

    string get_control_number() { return control_number; } 

    Client get_client() { return client; } 

    double get_sub_total() { return sub_total; } 

    double get_tax() { return tax; } 

    double get_total() { return total; } 

    bool is_active() { return active; } 

    bool is_paid() { return paid; } 

	
	Item get_item(int indx) {
		auto itm = items.begin();
		advance(itm, indx);
		return *itm;
	}

	int item_list_size() { return items.size(); } 




	// SETTERS ===================================================================================

	
	void set_items(Item itmArr[], int n) {
		items.assign(itmArr, itmArr + n); // <- causa violacion de segmento
		compute();
	}

	// void set_file_name(string fn) { file_name = fn; } // Evaluar conveniencia...

	void set_active(bool active) { this->active = active; }

	void set_paid(bool paid) { this->paid = paid; }




	// GENERAL METHODS ===========================================================================
	
	
	void compute() {
		sub_total = 0;
		list<Item>::iterator itm = items.begin();
		for(int i = 0; i < items.size(); i++) {
			sub_total += (*itm).get_item_total();
			advance(itm, 1);
		}
		total = sub_total * tax;

		// Solo para propositos de depuracion. Comentar o descomentar segun se necesite

		// cout << endl << "==============================================" << endl;
		// for(list<Item>::iterator i = items.begin(); i != items.end(); ++i) {
		// 	cout << (*i).to_string() << endl;
		// }
		// cout << "==============================================" << endl;
		// cout << "Sub total: " << sub_total << " -- Total: " << total << endl;
	}

	
	void add_item(Item itm) {
		items.emplace_back(itm);
		compute();
	}

	
	void add_item(string id, string desript, double price, double qtty) {
		Item* newItem = new Item(id, desript, price, qtty);
		items.emplace_back(*newItem);
		compute();
	}

	
	Item find_item_by_id(string itmID) { // Todo: Renombrar find_item()
		Item itm;
		for (list<Item>::iterator i = items.begin(); i != items.end(); ++i) {
			if(i->get_item_id() == itmID) itm = *i;
		}
		return itm;
	}

	
	int find_item_index_by_id(string itmID) { // Todo: Renombrar find_item_index()
		int indx = 0;
		for (list<Item>::iterator i = items.begin(); i != items.end(); ++i) {
			if(i->get_item_id() == itmID) break;
			++indx;
		}
		return indx;
	}

	
	void delete_item_by_id(string itmID) { // Todo: Renombrar delete_item()
		for (list<Item>::iterator i = items.begin(); i != items.end(); ++i) {
			if(i->get_item_id() == itmID) i = items.erase(i);
		}
		compute();
	}

	
	void delete_item_by_index(int indx) { // Todo: Renombrar delete_item() (overload)
		auto itm = items.begin();
		advance(itm, indx);
		itm = items.erase(itm); // <- causa violacion de segmento en QtCreator
		compute();
	}

	
	void clear_items() {
		items.clear();
		compute();
	}

	/**
	* Este método es candidato para moverlo a utils.hpp
	*/
	bool save_file() {
		fstream current_file(file_name, fstream::out | fstream::trunc);

		if(file_type == PLAIN){
			current_file << file_type << endl;

			// Insert at one line invoice header:
			current_file 	<< invoice_number << ";"
							<< invoice_date  << ";"
							<< invoice_time  << ";"
							<< budget_number  << ";"
							<< control_number << endl;

			// Inser at one line client data:
			current_file << client.to_string() << endl;

			// Insert at one line invoice footer:
			current_file 	<< sub_total << ";"
							<< tax << ";"
							<< total << ";"
							<< active << ";"
							<< paid << endl;

			// Insert items one each line until the end of the list:
			for (list<Item>::iterator it = items.begin(); it != items.end(); ++it) {
				current_file << it->to_string() << endl;
			}
			current_file << "END_ITEM_LIST";

		}
		current_file.close();
		return true;
	}
};
#endif