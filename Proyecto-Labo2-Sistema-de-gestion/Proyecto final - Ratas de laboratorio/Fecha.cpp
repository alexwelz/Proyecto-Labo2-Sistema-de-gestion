#include <iostream>
using namespace std;
#include "Fecha.h"
#include "rlutil.h"
#include "Funciones.h"

//void Fecha::cargar()
//{
//    ubicar(27, 13);
//    do
//    {
//        rlutil::setColor(rlutil::CYAN);
//        cout << "Dia: " ;
//        cin >> _dia;
//        if (_dia < 1 || _dia > 31)
//        {
//            rlutil::setColor(rlutil::RED);
//            cout << "Ingrese un dia valido" << endl;
//            rlutil::setColor(rlutil::CYAN);
//            presioneUnaTecla();
//            limpiarConsola();
//        }
//    } while (_dia < 1 || _dia > 31);
//    ubicar(27, 14);
//    do
//    {
//        rlutil::setColor(rlutil::CYAN);
//        cout << "Mes: " ;
//        cin >> _mes;
//        if (_mes < 1 || _mes > 12)
//        {
//            rlutil::setColor(rlutil::RED);
//            cout << "Ingrese un mes valido" << endl;
//            rlutil::setColor(rlutil::CYAN);
//            presioneUnaTecla();
//            limpiarConsola();
//        }
//    } while (_mes < 1 || _mes > 12);
//
//    ubicar(27, 15);
//    do
//    {
//        rlutil::setColor(rlutil::CYAN);
//        cout << "Anio: " ;
//        cin >> _anio;
//        if (_anio < 2021 )
//        {
//            rlutil::setColor(rlutil::RED);
//            cout << "Ingrese un anio valido" << endl;
//            rlutil::setColor(rlutil::CYAN);
//            presioneUnaTecla();
//            limpiarConsola();
//        }
//    } while (_anio < 2021 );
//}

void Fecha::cargar() {
    time_t rawtime;
    struct tm timeinfo;

    time(&rawtime);
    timeinfo = *(localtime(&rawtime));

    _dia = timeinfo.tm_mday;
    _mes = timeinfo.tm_mon - 1;// harcodeo -1
    _anio = timeinfo.tm_year + 1900;
    _hora = timeinfo.tm_hour;
    _min = timeinfo.tm_min;
}

void Fecha::mostrar()
{
    rlutil::setColor(rlutil::CYAN);
    cout << _dia << "/" << _mes << "/" << _anio << "   " <<_hora<<":"<<_min<<"hs"<<endl;
}

//SETS

void Fecha::setDia(int dia)
{
    _dia = dia;
}

void Fecha::setMes(int mes)
{
    _mes = mes;
}

void Fecha::setAnio(int anio)
{
    _anio = anio;
}

void Fecha::setHora(int hora)
{
    _hora = hora;
}

void Fecha::setMin(int min)
{
    _min = min;
}

void Fecha::setSeg(int seg)
{
    _seg = seg;
}

//GETS

int Fecha::getDia()
{
    return _dia;
}

int Fecha::getMes()
{
    return _mes;
}

int Fecha::getAnio()
{
    return _anio;
}

int Fecha::getHora()
{
    return _hora;
}

int Fecha::getMin()
{
    return _min;
}

int Fecha::getSeg()
{
    return _seg;
}

Fecha::Fecha() {
    time_t rawtime;
    struct tm timeinfo;

    time(&rawtime);
    timeinfo = *(localtime(&rawtime));

    _dia = timeinfo.tm_mday;
    _mes = timeinfo.tm_mon + 1;
    _anio = timeinfo.tm_year + 1900;
    _hora = timeinfo.tm_hour;
    _min = timeinfo.tm_min;
    _seg = timeinfo.tm_sec;
}

