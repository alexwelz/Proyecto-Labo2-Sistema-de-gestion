#include <iostream>
#include <iomanip>
using namespace std;
#include "InformesArchivo.h"
#include "Informe.h"

Informe InformesArchivo::leer(int nroRegistro) {
    Informe inf{};
    FILE* p;
    p = fopen("informes.dat", "rb");
    if (p == NULL) {
        return inf;
    }
    fseek(p, nroRegistro * sizeof(Informe), SEEK_SET);
    fread(&inf, sizeof(Informe), 1, p);
    fclose(p);
    return inf;
}

bool InformesArchivo::leerTodos(Informe informe[], int cantidad) {
    FILE* p;
    p = fopen("informes.dat", "rb");
    if (p == NULL) {
        return false;
    }
    fread(informe, sizeof(Informe), cantidad, p);
    fclose(p);
    return true;
}

bool InformesArchivo::guardar(Informe inf) {
    FILE* p = fopen("informes.dat", "ab");
    if (p == NULL) {
        return false;
    }
    bool ok = fwrite(&inf, sizeof(Informe), 1, p);
    fclose(p);
    return ok;
}

bool InformesArchivo::guardar(Informe inf, int nroRegistro) {
    FILE* p = fopen("informes.dat", "rb+");
    if (p == NULL) {
        return false;
    }
    fseek(p, nroRegistro * sizeof(Informe), SEEK_SET);
    bool ok = fwrite(&inf, sizeof(Informe), 1, p);
    fclose(p);
    return ok;
}

int InformesArchivo::getCantidad() {
    FILE* p = fopen("informes.dat", "rb");
    if (p == NULL) {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Informe);
    fclose(p);
    return cant;
}


void InformesArchivo::mostrarArchivo()
{
    InformesArchivo infArc;
    int cantArchivos = infArc.getCantidad();
    Informe* inf = new Informe[cantArchivos];
    infArc.leerTodos(inf, cantArchivos);
    cout << left;
    cout << setw(30) << "Nombre";
    cout << setw(4) << "ID";
    cout << setw(9) << "Cantidad";
    cout << setw(5) << "Tipo";
    cout << setw(7) << "Estado" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (int x = 0; x < cantArchivos; x++)
    {
        inf[x].mostrar();
    }

    delete[] inf;
}
