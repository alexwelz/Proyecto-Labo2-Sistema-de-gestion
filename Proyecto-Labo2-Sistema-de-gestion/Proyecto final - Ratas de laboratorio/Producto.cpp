#include <iostream>
using namespace std;
#include "funciones.h"
#include "Producto.h"
#include "ProductosArchivo.h"
#include "rlutil.h"
#include <string>


enum opciones
{
	Opcion1 = 0,
	Opcion2 = 1,
	Opcion3 = 2,
	Opcion4 = 3,
	Opcion5 = 4,
	Opcion6 = 5,
	Opcion7 = 6,
	Opcion8 = 7,
	Opcion9 = 8
};

void Producto::cargar()//TODO: CARGAR PRODUCTOS
{
	Producto prod;
	int codProd;
	char nombre[30];
	char marca[30];
	int categoriaProd;
	float precio;
	int stock;
	bool estado;
	bool repite = true;
	int opcion;

	do
	{
		Producto prodVerificacion;
		ProductosArchivo prodVerificacionArc;
		bool repetido = false;

		limpiarConsola();
		rlutil::cls();

		ubicar(27, 8);
		rlutil::setColor(rlutil::YELLOW);
		cout << "CARGA DE PRODUCTOS - LAB RATS";
		rlutil::setColor(rlutil::WHITE);

		ubicar(27, 9);
		cout << "=======================================================";

		ubicar(27, 10);
		cout << "Codigo de producto: ";
		rlutil::setColor(rlutil::CYAN);
		cin >> codProd;
		cin.ignore();

		ubicar(27, 11);
		rlutil::setColor(rlutil::WHITE);
		cout << "Nombre: ";
		rlutil::setColor(rlutil::CYAN);
		cin.getline(nombre, 30, '\n');

		ubicar(27, 12);
		rlutil::setColor(rlutil::WHITE);
		cout << "Marca: ";
		rlutil::setColor(rlutil::CYAN);
		cin.getline(marca, 30, '\n');

		ubicar(27, 13);
		rlutil::setColor(rlutil::WHITE);
		cout << "Categoria de producto: ";
		rlutil::setColor(rlutil::CYAN);
		cin >> categoriaProd;

		ubicar(27, 14);
		rlutil::setColor(rlutil::WHITE);
		cout << "Precio unitario: $";
		rlutil::setColor(rlutil::CYAN);
		cin >> precio;

		ubicar(27, 15);
		rlutil::setColor(rlutil::WHITE);
		cout << "Cantidad: ";
		rlutil::setColor(rlutil::CYAN);
		cin >> stock;

		ubicar(27, 17);
		cout << "Presione una tecla para continuar";
		presioneUnaTecla();
		estado = true;

		//VALIDO QUE EL PRODUCTO NO TENGA EL MISMO CODIGO QUE OTRO DEL ARCHIVO
		for (int x = 0; x < prodVerificacionArc.getCantidad(); x++)
		{
			prodVerificacion = prodVerificacionArc.leer(x);
			if (prodVerificacion.getIdProd() == codProd)
			{
				repetido = true;
			}
		}
		if (repetido == true)
		{
			limpiarConsola();
			ubicar(27, 10);
			rlutil::setColor(rlutil::RED);
			cout << endl << "Ya hay un Producto registrado con el mismo codigo" << endl;
			rlutil::setColor(rlutil::WHITE);
			presioneUnaTecla();
			return menuAdmin();
		}


		prod.setIdProd(codProd);
		prod.setNombre(nombre);
		prod.setMarca(marca);
		prod.setCategoriaProd(categoriaProd);
		prod.setPrecio(precio);
		prod.setStock(stock);
		prod.setEstado(estado);

		int op = 1;
		int y = 0;
		do
		{
			rlutil::setBackgroundColor(rlutil::BLACK);
			rlutil::setColor(rlutil::WHITE);
			rlutil::hidecursor();
			limpiarConsola();
			showItemEgreso("Desea guardar el producto ingresado?", 30, 9, 0);
			showItemEgreso("- OK       ", 40, 11, y == Opcion1);
			showItemEgreso("- Cancelar ", 40, 12, y == Opcion2);

			switch (rlutil::getkey())
			{
			case 14: // UP
				rlutil::locate(28, 10 + y);
				std::cout << " " << std::endl;
				y--;
				if (y < 0) {
					y = 0;
				}
				break;
			case 15: // DOWN
				rlutil::locate(28, 10 + y);
				std::cout << " " << std::endl;
				y++;
				if (y > 1) {
					y = 1;
				}
				break;
			case 1: // ENTER

				switch (y)
				{
				case 0:
				{
					op = 0;
					ProductosArchivo prodA;
					prodA.guardar(prod);
					limpiarConsola();
					ubicar(27, 10);
					rlutil::setColor(rlutil::GREEN);
					cout << "Producto cargado con exito" << endl;
					rlutil::setColor(rlutil::CYAN);
					presioneUnaTecla();
					limpiarConsola();
					break;
				}
				case 1:
					op = 0;
					limpiarConsola();
					break;
				}
			}

		} while (op != 0);
		op = 1;
		y = 0;
		do
		{
			rlutil::setBackgroundColor(rlutil::BLACK);
			rlutil::setColor(rlutil::WHITE);
			rlutil::hidecursor();
			limpiarConsola();
			showItemEgreso("Desea CARGAR otro producto?", 30, 9, 0);
			showItemEgreso("- OK       ", 38, 11, y == Opcion1);
			showItemEgreso("- Cancelar ", 38, 12, y == Opcion2);

			switch (rlutil::getkey())
			{
			case 14: // UP
				rlutil::locate(28, 10 + y);
				std::cout << " " << std::endl;
				y--;
				if (y < 0) {
					y = 0;
				}
				break;
			case 15: // DOWN
				rlutil::locate(28, 10 + y);
				std::cout << " " << std::endl;
				y++;
				if (y > 1) {
					y = 1;
				}
				break;
			case 1: // ENTER

				switch (y)
				{
				case 0:
					op = 0;
					repite = true;
					break;
				case 1:
					op = 0;
					repite = false;
					break;
				}
			}

		} while (op != 0);

	} while (repite);
}

void Producto::mostrar()
{
	
	rlutil::setColor(rlutil::CYAN);
	//ubicar(27, 10);
	cout << "Codigo de producto: " << getIdProd() << endl;
	//ubicar(27, 11);
	cout << "Nombre: " << getNombre() << endl;
	//ubicar(27, 12);
	cout << "Marca: " << getMarca() << endl;
	//ubicar(27, 13);
	cout << "Categoria producto: " << getCategoriaProd() << endl;
	//ubicar(27, 14);
	cout << "Precio: " << getPrecio() << endl;
	//ubicar(27, 15);
	cout << "Stock Actual: " << getStock() << endl;
	//ubicar(27, 16);
	cout << "Estado: " << getEstado() << endl ;
}

//SETS

void Producto::setIdProd(int idProd)
{
	_idProd = idProd;
}

void Producto::setNombre(const char* nombre)
{
	strcpy(_nombre, nombre);
}

void Producto::setMarca(const char* marca)
{
	strcpy(_marca, marca);
}

void Producto::setCategoriaProd(int categoriaProd)
{
	_categoriaProd = categoriaProd;
}

void Producto::setPrecio(float precio)
{
	_precio = precio;
}

void Producto::setStock(int stock)
{
	_stock = stock;
}

void Producto::setEstado(bool estado)
{
	_estado = estado;
}

void Producto::aumentarStock(int cant)
{
	_stock += cant;
}

void Producto::descontarStock(int cant)
{
	_stock -= cant;
}



//GETS

int Producto::getIdProd()
{
	return _idProd;
}

const char* Producto::getNombre()
{
	return _nombre;
}

const char* Producto::getMarca()
{
	return _marca;
}

int Producto::getCategoriaProd()
{
	return _categoriaProd;
}

float Producto::getPrecio()
{
	return _precio;
}

int Producto::getStock()
{
	return _stock;
}

bool Producto::getEstado()
{
	return _estado;
}

