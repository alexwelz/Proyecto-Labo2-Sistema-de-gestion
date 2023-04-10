#pragma once
#include "Informe.h"

class InformesArchivo
{
public:
	Informe leer(int nroRegistro);
	bool leerTodos(Informe informe[], int cantidad);
	bool guardar(Informe informe);
	bool guardar(Informe inf, int nroRegistro);
	int getCantidad();

	void mostrarArchivo();
};

