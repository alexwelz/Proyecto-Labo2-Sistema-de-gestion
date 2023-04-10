#pragma once
class Informe
{
private:
    int idProd;
    char nombre[30];
    int cant;
    char tipoPed[2];
    bool estado;

public:
    void mostrar();
    void cargar();

    void setIdProd(int _idProd);
    void setNombre(const char* _nombre);
    void setCant(int _cant);
    void setTipoPed(const char* _tipoPed);
    void setEstado(bool _estado);

    int getIdProd();
    const char* getNombre();
    int getCant();
    const char* getTipoPed();
    bool getEstado();

    void aumentarCantidad(int _cant);
};

