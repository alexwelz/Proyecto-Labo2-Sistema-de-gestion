#include <vector>
#include "Pedido.h"
#include "PedidosArchivo.h"
#include "rlutil.h"
#include "Funciones.h"
#include "Fecha.h"
#include "ProductosArchivo.h"
#include "Pedido.h"


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

void Pedido::cargar(int legajo,int categoria)
{
	bool repite = true;
	do
	{
		int cantidad = 50;
		PedidosArchivo parc;
		Pedido* p = new Pedido[cantidad];
		int idPedido;
		int idProducto;
		int cantidadProducto;
		int vCantProd[50];
		Fecha fechaPedido;
		bool cargado;
		char tipoPedido[2];// I = INGRESO STOCK E= EGRESO STOCK C= CANCELADO
		bool repite = true;

		if (parc.getCantidad() == 0)
		{
			idPedido = 1000;
		}
		else
		{
			idPedido = parc.getCantidad() + 1000;
		}

		if (categoria == 1)
		{
			tipoPedido[0] = {'i'};
			tipoPedido[1] = {'\0'};
		}
		else
		{
			if (categoria == 2)
			{
				tipoPedido[0] = { 'e' };
				tipoPedido[1] = { '\0' };
			}
		}
		cargado = false;
		
		fechaPedido.cargar();

		int pos = 0;
		do
		{
			int stock;
			bool existe = false;
			do {
				bool stockSuficiente = false;
				bool existe1 = false;
				bool existe2 = false;
				bool baja = false;
				ProductosArchivo pArchAux;
				Producto prod, prodAux;

				limpiarConsola();
				rlutil::setColor(rlutil::YELLOW);
				ubicar(27, 9);
				cout << "CARGA DE PEDIDOS - LAB RATS" << endl;
				ubicar(27, 10);
				cout << "=======================================================";
				rlutil::setColor(rlutil::CYAN);
				ubicar(27, 11);
				rlutil::setColor(rlutil::CYAN);
				cout <<"Ingrese ID producto: ";
				rlutil::setColor(rlutil::WHITE);
				cin >> idProducto;
				ubicar(27, 12);
				rlutil::setColor(rlutil::CYAN);
				cout << "Unidades solicitadas: ";
				rlutil::setColor(rlutil::WHITE);
				cin >> cantidadProducto;

				for (int x = 0; x < pArchAux.getCantidad(); x++)
				{
					prod = pArchAux.leer(x);

					if (prod.getIdProd() == idProducto && prod.getEstado() == false) {
						ubicar(27, 14);
						rlutil::setColor(rlutil::RED);
						cout << "El producto no esta disponible, por favor ingrese un ID valido" << endl;
						rlutil::setColor(rlutil::CYAN);
						baja = true;
						presioneUnaTecla();
						limpiarConsola();
					}
					else
					{
						if (prod.getIdProd() == idProducto && prod.getEstado() == true)
						{
							stock = prod.getStock();
							if (categoria == 2 && cantidadProducto > 0)
							{
								existe = true;
								existe2 = true;
								stockSuficiente = true;

							}
							else
							{
								if (categoria == 2 && cantidadProducto <= 0)
								{
									limpiarConsola();
									ubicar(27, 10);
									rlutil::setColor(rlutil::RED);
									cout << "Cantidad indicada NO VALIDA";
									rlutil::setColor(rlutil::CYAN);
									presioneUnaTecla();
									limpiarConsola();
								}
							}
							if (categoria == 1 && cantidadProducto >= 0)
							{
								existe = true;
								existe1 = true;
								stockSuficiente = true;
							}
							else
							{
								if (categoria == 1 && cantidadProducto <= 0)
								{
									limpiarConsola();
									ubicar(27, 10);
									rlutil::setColor(rlutil::RED);
									cout << "Cantidad indicada NO VALIDA";
									rlutil::setColor(rlutil::CYAN);
									presioneUnaTecla();
									limpiarConsola();
								}
							}
						}
					}
				}
				if (existe == false)
				{
					limpiarConsola();
					ubicar(27, 10);
					rlutil::setColor(rlutil::RED);
					cout << "No se encontro el ID del producto solicitado, ingrese un ID valido.";
					rlutil::setColor(rlutil::CYAN);
					presioneUnaTecla();
					limpiarConsola();
				}
			} while (!existe);

			p[pos].setIdPedido(idPedido);
			p[pos].setIdProducto(idProducto);
			p[pos].setCantidadProducto(cantidadProducto);
			p[pos].setFechaPedido(fechaPedido);
			p[pos].setEstadoPedido(cargado);
			p[pos].setTipoPedido(tipoPedido);
			p[pos].setLegajo(legajo);

			int op = 1;
			int y = 0;
			do
			{
				rlutil::setBackgroundColor(rlutil::BLACK);
				rlutil::setColor(rlutil::WHITE);
				rlutil::hidecursor();
				limpiarConsola();
				showItemEgreso("Desea agregar otro producto al pedido?", 30, 8, 0);
				showItemEgreso("==============================================", 30, 9, 0);
				showItemEgreso("- SI          ", 38, 11, y == Opcion1);
				showItemEgreso("- Cancelar    ", 38, 12, y == Opcion2);

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
						pos++;
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

		int op = 1;
		int y = 0;
		do
		{
			rlutil::setBackgroundColor(rlutil::BLACK);
			rlutil::setColor(rlutil::WHITE);
			rlutil::hidecursor();
			limpiarConsola();
			showItemEgreso("Desea guardar el pedido ingresado?", 30, 9, 0);
			showItemEgreso("- OK       ", 30, 11, y == Opcion1);
			showItemEgreso("- Cancelar ", 30, 12, y == Opcion2);

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
					PedidosArchivo pedArc;

					for (int j = 0; j <= pos; j++) {
						pedArc.guardar(p[j]);//Guarda el pedido
					}
					limpiarConsola();
					ubicar(27, 10);
					rlutil::setColor(rlutil::GREEN);
					cout << "Pedido cargado con exito" << endl;
					ubicar(27, 11);
					cout << "Tu ID de pedido es: "<< p[0].getIdPedido();
					rlutil::setColor(rlutil::CYAN);
					presioneUnaTecla();
					limpiarConsola();
					delete[] p;
					break;
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
			showItemEgreso("Desea CARGAR otro pedido?", 30, 9, 0);
			showItemEgreso("- OK       ", 30, 11, y == Opcion1);
			showItemEgreso("- Cancelar ", 30, 12, y == Opcion2);

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
					if (categoria == 1)
					{
						return menuEmpleadoIngreso(legajo, categoria);
					}
					else
					{
						if (categoria == 2)
						{
							return menuEmpleadoEgreso(legajo, categoria);
						}
					}
					break;
				}
				break;
			}

		} while (op != 0);
	}
	while (repite);

}

void Pedido::mostrar()
{	
	//ubicar(27, 10);
	rlutil::setColor(rlutil::CYAN);
	cout <<"Numero de pedido: "<< getIdPedido() << endl;
	//ubicar(27, 11);
	cout <<"Legajo del empleado: "<< getLegajo() << endl;
	//ubicar(27, 12);
	cout << "Tipo de pedido: " << getTipoPedido() << endl;
	//ubicar(27, 13);
	cout <<"ID del producto solicitado: " << getIdProducto() << endl;
	//ubicar(27, 14);
	cout <<"Cantidad: " << getCantidadProducto() << endl;//Cantidad total de un producto
	//ubicar(27, 15);
	_fechaPedido.mostrar();
	cout << "estado " <<getEstadoPedido()<< endl;
}

void Pedido::setIdPedido(int idPedido)
{
	_idPedido = idPedido;
}

void Pedido::setLegajo(int legajo)
{
	_legajo = legajo;
}

void Pedido::setIdProducto(int idProducto)
{
	_idProducto = idProducto;
}

void Pedido::setFechaPedido(Fecha fechaPedido)
{
	_fechaPedido = fechaPedido;
}

void Pedido::setCantidadProducto(int cantidadProducto)
{
	_cantidadProducto = cantidadProducto;
}

int Pedido::getIdPedido()
{
	return _idPedido;
}

int Pedido::getLegajo()
{
	return _legajo;
}

int Pedido::getIdProducto()
{
	return _idProducto;
}

int Pedido::getCantidadProducto()
{
	return _cantidadProducto;
}

Fecha Pedido::getFechaPedido()
{
	return _fechaPedido;
}

bool Pedido::getEstadoPedido()
{
	return _cargado;
}

const char* Pedido::getTipoPedido()
{
	return _tipoPedido;
}

void Pedido::setEstadoPedido(bool cargado)
{
	_cargado = cargado;
}

void Pedido::setTipoPedido(const char* tipoPedido)
{
	strcpy(_tipoPedido, tipoPedido);
}
