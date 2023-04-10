#pragma once


class Fecha
{
private:
    int _dia;
    int _mes;
    int _anio;
    int _hora;
    int _min;
    int _seg;

public:
    void cargar();
    void mostrar();

    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);
    void setHora(int hora);
    void setMin(int min);
    void setSeg(int seg);

    int getDia();
    int getMes();
    int getAnio();
    int getHora();
    int getMin();
    int getSeg();

    Fecha();
};

