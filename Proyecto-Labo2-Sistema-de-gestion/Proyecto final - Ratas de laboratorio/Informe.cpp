#include <iomanip>
#include "Informe.h"
#include "rlutil.h"
#include "Funciones.h"
#include "Domicilio.h"
#include "Fecha.h"
#include "Pedido.h"
#include "PedidosArchivo.h"
#include "Empleado.h"
#include "EmpleadosArchivo.h"
#include "Producto.h"
#include "ProductosArchivo.h"


void Informe::mostrar()
{
	if (cant > 0)
	{
		cout << left;
		cout << setw(30) << nombre;
		cout << setw(4) << idProd;
		cout << setw(9) << cant;
		cout << setw(5) << tipoPed;
		cout << setw(7) << estado;
		cout << endl;
	}
}

void Informe::cargar()
{
	cant = 0;
}

void Informe::setIdProd(int _idProd)
{
	idProd = _idProd;
}

void Informe::setNombre(const char* _nombre)
{
	strcpy(nombre, _nombre);
}

void Informe::setCant(int _cant)
{
	cant = _cant;
}

void Informe::setTipoPed(const char* _tipoPed)
{
	strcpy(tipoPed, _tipoPed);
}

void Informe::setEstado(bool _estado)
{
	estado = _estado;
}

int Informe::getIdProd()
{
	return idProd;
}

const char* Informe::getNombre()
{
	return nombre;
}

int Informe::getCant()
{
	return cant;
}

const char* Informe::getTipoPed()
{
	return tipoPed;
}

bool Informe::getEstado()
{
	return estado;
}

void Informe::aumentarCantidad(int _cant)
{
	cant += _cant;
}
