#pragma once
#include <string>
using namespace std;
#include "Empleado.h"

void limpiarConsola();
void presioneUnaTecla();
void menuPrincipal();
void menuEmpleado();
void menuPrincipalEmpleado(Empleado emp);
void menuEmpleadoIngreso(int legajo, int categoria);
void menuEmpleadoEgreso(int legajo, int categoria);
void menuAdmin();
void menuInformes();
void menuPrincipalAdmin(Empleado admin);
void menuBajaEmpleado(Empleado admin);
void menuEditarEmpleado(Empleado admin);
void menuBajaProducto(Empleado admin);
void menuEditarProducto(Empleado admin);
void showItem(const char* text, int posx, int posy, bool selected);
void showItemIngreso(const char* text, int posx, int posy, bool selected);
void showItemEgreso(const char* text, int posx, int posy, bool selected);
void ubicar(int posx, int posy);