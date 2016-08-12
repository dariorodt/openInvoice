// File: main.cpp

#include <iostream>
#include <iomanip>
#include "invoice.hpp"
#include "utils.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
	// PRUEBA: CREACION DE FACTURA NUEVA.

	// Preparamos un cliente
	Client *cliente = new Client("V10046333","Dario Rodriguez","Calle 22, nro 51","0412.949.00.74","0281.332.43.86");

	// Preparamos un array de items
	Item* itm1 = new Item("45636", "Queso parmesano rallado", 450.0, 0.5);
	Item* itm2 = new Item("74589", "Jamon de pierna", 563.0, .5);
	Item* itm3 = new Item("74569", "Pulpa negra", 1200.0, 1.5);
	Item* itm4 = new Item("45263", "Riquesa Cheddar", 95.0, 1.0);
	Item* itm5 = new Item("74582", "Atun 140g", 255.0, 3.0);
	Item itmArray[] = {*itm1, *itm2, *itm3, *itm4, *itm5};

	// Definimos una factura nueva asignandole los datos necesarios para el constructor utilizado.
	// Se incluye entre los datos el cliente previamente definido.
	// Invoice(string invoice_number, string budget_number, string control_number, Client client)
	Invoice *inv = new Invoice("456956987", "no_budget", "45563256", *cliente);
	cout 	<< "Creada nueva factura " << inv->get_file_name() << endl
			<< "Cliente: " << inv->get_client().get_name() << endl;

	// Finalmente asignamos a la factura un conjunto de items desde el array previamente definido.
	(*inv).set_items(itmArray, 5);
	cout 	<< "Asignado un array a la lista via set_items()\n"
			<< "Items totales: " << inv->item_list_size() << endl
			<< "Total factura: " << inv->get_total() << endl;

	// PRUEBAS INDEPENDIENTES

	// Asignamos a la factura un nuevo item via add_item(Item)
	Item *newItm = new Item("88569", "Mayonesa", 75.0, 1.0);
	(*inv).add_item(*newItm);
	cout << endl << "Asignado un item via add_item(Item)";

	// Asignamos un nuevo item via add_item(string, string, double, double)
	(*inv).add_item("85696", "Salsa katchup", 63.5, 2.0);
	cout << endl << "Asignado un item via add_item(string, string, double, double)";

	// Prueba de búsqueda por ID devolviendo un índice
	cout << endl << "Busqueda por item_id regresando un indice" << endl;
	int ix = inv->find_item_index_by_id("74569");
	cout << (inv->get_item(ix)).to_string() << endl;

	// Prueba de guardado de la factura en un archivo
	if(inv->save_file()) cout << "Archivo " << inv->get_file_name() << " ha sido guardado...";

	// Prueba de borrado de un item suministrando el ID
	cout << endl << "Borrando item 45263 via delete_item_by_id(item_id)";
	inv->delete_item_by_id("45263");

	// Prueba de borrado de in item suministrando el índice
	cout << endl << "Borrando item 74589 via delete_item_by_index(indx)";
	ix = inv->find_item_index_by_id("74589");
	inv->delete_item_by_index(ix);

	// Prueba de borrado de todos los elementos de la lista de items
	cout << endl << "Vaciando la lista de items..." << endl;
	inv->clear_items();

	// Prueba de recuperación de una factura desde el correspondiente archivo
	cout << "Recargando factura..." << endl;
	Invoice *inv2 = new Invoice("456956987.invoice");
	cout << "Factura nro: " << inv2->get_invoice_number() << ", Total: " << inv2->get_total() << endl;

	// Prueba de obtención de la fecha de la factura "get_invoice_date()"
	cout << "Fecha factura: " << inv->get_invoice_date() << endl;

	// Prueba de obtención de la hora de la factura "string get_invoice_time()"
	cout << "Hora factura: " << inv->get_invoice_time() << endl;

	// Prueba de obtención del número de presupuesto "get_budget_number()"
	cout << "Número presupuesto: " << inv->get_budget_number() << endl;

	// Prueba de obtención del número de control "get_control_number()"
	cout << "Número de control: " << inv->get_control_number() << endl;

	// prueba de obtención del subtotal de la factura "get_sub_total()"
	cout << "Sub-total: " << inv->get_sub_total() << endl;

	// Prueba de obtención del impuesto "get_tax()"
	cout << "Impuesto cobrado: " << inv->get_tax() << endl;
	

	return 0;
}