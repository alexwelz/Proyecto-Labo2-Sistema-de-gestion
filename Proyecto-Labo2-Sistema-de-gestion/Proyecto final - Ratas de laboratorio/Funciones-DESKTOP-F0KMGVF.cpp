#include <iostream>
#include <iomanip>
using namespace std;
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
#include "Informe.h"
#include "InformesArchivo.h"



void limpiarConsola()
{
    rlutil::cls();
}

void presioneUnaTecla()
{
    rlutil::anykey();
}

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

//TODO: MENU PRINCIPAL DEL PROGRAMA
void menuPrincipal()
{
    int y = 0;
    int op = 1;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();
        showItem("Bienvenido/a a LAB/RATS", 29, 8, 0);
        showItem("-------------------------------", 26, 9, 0);
        showItem("- Acceder como empleado  ", 30, 10, y == Opcion1);
        showItem("- Acceder como admin     ", 30, 11, y == Opcion2);

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
                break;
            case 1:
                op = 0;
                break;

            }

            if (y == 0)
            {
                menuEmpleado();
            }
            else
            {
                menuAdmin();
            }
        } 
    } while (op != 0);
}

//TODO: Login empleados
void menuEmpleado()
{
    int legajo;
    int password;
    int intentos=0;
    Empleado e, emp;
    EmpleadosArchivo ea;
    bool ingreso = false;
    bool repite = true;
    limpiarConsola();

    do
    {
        //TODO: Ingreso Empleados (funciona bien el do while)
        rlutil::setColor(rlutil::YELLOW);
        ubicar(27 , 8);
        cout << "                 INGRESO EMPLEADOS" << endl;
        ubicar(27, 9);
        cout << "=======================================================" << endl;
        //cout << endl << endl;
        ubicar(30 - 3, 10);
        rlutil::setColor(rlutil::WHITE);
        cout << "Ingrese nro de legajo: " ;
        rlutil::setColor(rlutil::CYAN);
        cin >> legajo;//validarlo del archivo de empleados
    

        rlutil::setColor(rlutil::WHITE);
        ubicar(27, 11);
        cout << "Ingrese su clave de ingreso: ";
        rlutil::setColor(rlutil::CYAN);
        cin >> password;
        rlutil::setColor(rlutil::CYAN);
        cout << endl;
        limpiarConsola();

        for (int x = 0; x < ea.getCantidad(); x++)
        {
            e = ea.leer(x);

            if (e.getLegajo() == legajo && e.getPassword() == password && e.getEstado() == true)
            {

                emp = e;
                if (emp.getCategoria() == 999)
                {
                    limpiarConsola();
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "El usuario ADMIN no puede acceder al menu de empleados" << endl;
                    rlutil::setColor(rlutil::WHITE);
                    presioneUnaTecla();
                    limpiarConsola();
                    return menuPrincipal();
                }
                else
                {
                    if (emp.getEstado() == false)
                    {
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::RED);
                        cout << "El usuario ha sido dado de baja" << endl;
                        rlutil::setColor(rlutil::WHITE);
                        presioneUnaTecla();
                    }
                }

                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "Ingreso exitoso! Bienvenido " << emp.getNombre() << " " << emp.getApellido();
                rlutil::setColor(rlutil::WHITE);
                ingreso = true;
                repite = false;
                presioneUnaTecla();
                limpiarConsola();
            }
        
            
        }

        if(ingreso == false)
        {
        intentos++;
            if (intentos < 3 && intentos > 0)
            {
                ubicar(27, 10);
                rlutil::setColor(rlutil::RED);
                cout << "Legajo o clave invalida, vuelva a intentar" << endl;
                rlutil::setColor(rlutil::WHITE);
                presioneUnaTecla();
                limpiarConsola();
            }
        }
        
        if (intentos == 3)
        {
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "Muchos ingresos fallidos, se cerrara el programa" << endl;
            rlutil::setColor(rlutil::WHITE);
            presioneUnaTecla();
            return;
        }
    }
    while (repite);

    menuPrincipalEmpleado(emp);
}

//TODO: Menu donde se filtra que menu mostrar segun la categoria
void menuPrincipalEmpleado(Empleado emp)
{
    int categoriaEmp=emp.getCategoria();
    int legajoEmp = emp.getLegajo();
    if (emp.getCategoria() == 1)
    {
        menuEmpleadoIngreso(legajoEmp, categoriaEmp);
    }
    else
    {
        if (emp.getCategoria() == 2 )
        {
            menuEmpleadoEgreso(legajoEmp, categoriaEmp);
        }
    }
}

//TODO: Menu empleado para ingreso de productos
void menuEmpleadoIngreso(int legajo, int categoria)//Si tiene categoria 1 se encarga del ingreso de productos
{
    //int opcion;
    int y = 0;
    int op = 1;
    do
    {
        rlutil::setBackgroundColor(rlutil::RED);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        showItemIngreso("                 INGRESO DE STOCK", 30, 8, 0);
        showItemIngreso("=======================================================", 30, 9, 0);
        showItemIngreso("- Registrar nuevo pedido      ", 30, 10, y == Opcion1);
        showItemIngreso("- Cargar pedido pendiente     ", 30, 11, y == Opcion2);
        showItemIngreso("- Cancelar pedido             ", 30, 12, y == Opcion3);
        showItemEgreso("- Menu Principal              ", 30, 13, y == Opcion4);
        showItemIngreso("-=======================================================", 30, 14, 0);
        showItemEgreso("- Volver al inicio de sesion  ", 30, 15, y == Opcion5);
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
            if (y > 4) {
                y = 4;
            }
            break;
        case 1: // ENTER

            switch (y)
            {
            case 0:
            {
                op = 0;
                Pedido ped;
                PedidosArchivo pedArc;
                ped.cargar(legajo, categoria);
                limpiarConsola();
                return menuEmpleadoIngreso(legajo, categoria);
                break;
            }
            case 1:
            {
                op = 0;
                bool repite = true;
                bool cancelado = false;
                bool cargado = false;
                int cont = 0;
                bool stockInsuficiente = false;

                do
                {
                    Pedido ped1;
                    PedidosArchivo pedArc1;
                    Producto* prod;
                    ProductosArchivo prodArc;
                    int idPedido;
                    int opcion;
                    bool encontro = false;

                    limpiarConsola();
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::YELLOW);
                    cout << "CARGAR PEDIDO PENDIENTE" << endl;
                    ubicar(27, 11);
                    cout << "=======================================================" << endl;
                    ubicar(27, 12);
                    rlutil::setColor(rlutil::WHITE);
                    cout << "Ingrese ID de pedido";
                    ubicar(27, 13);
                    rlutil::setColor(rlutil::CYAN);
                    cin >> idPedido;
                    limpiarConsola();

                    for (int x = 0; x < pedArc1.getCantidad(); x++)
                    {
                        ped1 = pedArc1.leer(x);
                        if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "i") == 0 && ped1.getEstadoPedido() == false)
                        {
                            cont++;
                            encontro = true;
                            repite = false;
                        }
                        else
                        {
                            if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "c") == 0)
                            {
                                limpiarConsola();
                                ubicar(27, 10);
                                rlutil::setColor(rlutil::RED);
                                cout << "El pedido fue cancelado con anterioridad." << endl;
                                rlutil::setColor(rlutil::CYAN);
                                presioneUnaTecla();
                                limpiarConsola();
                                cancelado = true;
                                encontro = true;
                                repite = false;
                                return menuEmpleado();
                            }
                            else
                            {
                                if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "e") == 0)
                                {
                                    limpiarConsola();
                                    encontro = true;
                                    repite = false;
                                    ubicar(27, 10);
                                    rlutil::setColor(rlutil::RED);
                                    cout << "No tiene permitido cargar pedidos de egreso de stock" << endl;
                                    rlutil::setColor(rlutil::CYAN);
                                    presioneUnaTecla();
                                    limpiarConsola();
                                    return menuEmpleadoIngreso(legajo, categoria);
                                }
                                else
                                {
                                    if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "i") == 0 && ped1.getEstadoPedido() != false)
                                    {
                                        limpiarConsola();
                                        ubicar(27, 10);
                                        rlutil::setColor(rlutil::RED);
                                        cout << "El pedido ya fue cargado anteriormente";
                                        rlutil::setColor(rlutil::CYAN);
                                        presioneUnaTecla();
                                        limpiarConsola();
                                        return menuEmpleadoIngreso(legajo, categoria);
                                    }
                                }
                            }
                        }
                    }
                    if (encontro == true && cancelado == false)
                    {

                        limpiarConsola();
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Pedido encontrado!";
                        rlutil::setColor(rlutil::CYAN);
                        presioneUnaTecla();
                        limpiarConsola();

                        prod = new Producto[prodArc.getCantidad()];
                        for (int i = 0; i < prodArc.getCantidad(); i++)
                        {
                            prod[i] = prodArc.leer(i);
                        }


                        for (int x = 0; x < pedArc1.getCantidad(); x++)
                        {
                            ped1 = pedArc1.leer(x);
                            if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "i") == 0 && ped1.getEstadoPedido() == false)
                            {
                                for (int i = 0; i < prodArc.getCantidad(); i++)
                                {
                                    if (ped1.getIdProducto() == prod[i].getIdProd() && ped1.getCantidadProducto() <= 0)
                                    {
                                            stockInsuficiente = true;
                                    }
                                }
                            }
                        }
                        if (stockInsuficiente)
                        {

                            limpiarConsola();
                            ubicar(27, 10);
                            rlutil::setColor(rlutil::RED);
                            cout << "No hay stock suficiente para el pedido";
                            rlutil::setColor(rlutil::CYAN);
                            presioneUnaTecla();
                            limpiarConsola();
                            return menuEmpleadoIngreso(legajo, categoria);
                        }
                        else
                        {
                            int y = 0;
                            int op = 1;
                            if (!stockInsuficiente)
                            {
                                do
                                {
                                    rlutil::setBackgroundColor(rlutil::BLACK);
                                    rlutil::setColor(rlutil::WHITE);
                                    rlutil::hidecursor();
                                    limpiarConsola();
                                    showItemEgreso("Desea guardar el pedido ingresado?", 30, 9, 0);
                                    showItemEgreso("- OK       ", 30, 11, y == Opcion1);         // Pienso que si se setea dentro del if que pregunte antes de setearlo
                                    showItemEgreso("- Cancelar ", 30, 12, y == Opcion2);    //Si quiere o no guardarlo pero tambien tendria que descontar stock en Opcion 1

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
                                            for (int x = 0; x < pedArc1.getCantidad(); x++)
                                            {
                                                ped1 = pedArc1.leer(x);
                                                if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "i") == 0 && ped1.getEstadoPedido() == false)
                                                {
                                                    for (int i = 0; i < prodArc.getCantidad(); i++)
                                                    {
                                                        if (ped1.getIdProducto() == prod[i].getIdProd())
                                                        {
                                                            prod[i].aumentarStock(ped1.getCantidadProducto());
                                                            ped1.setEstadoPedido(true);
                                                            prodArc.guardar(prod[i], i);
                                                            pedArc1.guardar(ped1, x);
                                                        }
                                                    }
                                                }
                                            }
                                            limpiarConsola();
                                            ubicar(27, 10);
                                            rlutil::setColor(rlutil::GREEN);
                                            cout << "Pedido cargado con exito" << endl;
                                            rlutil::setColor(rlutil::CYAN);
                                            presioneUnaTecla();
                                            limpiarConsola();
                                            delete[]prod;
                                            return menuEmpleadoIngreso(legajo, categoria);
                                            break;
                                        case 1:
                                            op = 0;
                                            return menuEmpleadoIngreso(legajo, categoria);
                                            break;
                                        }
                                    }

                                } while (op != 0);
                            }
                        }
                    }
                    else
                    {
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::RED);
                        cout << "Pedido no encontrado/incorrecto" << endl;
                        rlutil::setColor(rlutil::CYAN);
                        presioneUnaTecla();
                        limpiarConsola();
                        return menuEmpleadoIngreso(legajo, categoria);
                    }
                } while (repite);
                return menuEmpleadoIngreso(legajo, categoria);
                break;
            }
            case 2:
            {
                op = 0;
                int opcion1;
                Pedido ped1, *ped1Aux;
                PedidosArchivo pedArc1;
                int cantPed;
                int idPedido;
                int reg;
                bool encontro = false;
                bool cancelado = false;

                cantPed = pedArc1.getCantidad();
                ped1Aux = new Pedido[cantPed];

                limpiarConsola();
                ubicar(27, 10);
                rlutil::setColor(rlutil::YELLOW);
                cout << "CANCELAR PEDIDO DE INGRESO" << endl;
                ubicar(27, 11);
                cout << "=======================================================" << endl;
                ubicar(27, 12);
                rlutil::setColor(rlutil::WHITE);
                cout << "Ingrese ID de pedido";
                ubicar(27, 13);
                rlutil::setColor(rlutil::CYAN);
                cin >> idPedido;

                for (int x = 0; x < pedArc1.getCantidad(); x++)
                {
                    ped1 = pedArc1.leer(x);
                    if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "i") == 0)
                    {
                        if (ped1.getEstadoPedido() == false)
                        {
                            encontro = true;
                            reg = x;
                            ped1Aux[x] = ped1;
                        }
                        else
                        {
                            limpiarConsola();
                            ubicar(27, 10);
                            rlutil::setColor(rlutil::RED);
                            cout << "No se pueden cancelar pedidos ya cargados" << endl;
                            rlutil::setColor(rlutil::CYAN);
                            presioneUnaTecla();
                            limpiarConsola();
                            return menuEmpleadoIngreso(legajo, categoria);
                        }
                    }
                    else
                    {
                        if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "c") == 0)
                        {
                            limpiarConsola();
                            ubicar(27, 10);
                            rlutil::setColor(rlutil::RED);
                            cout << "El pedido fue cancelado con anterioridad." << endl;
                            rlutil::setColor(rlutil::CYAN);
                            presioneUnaTecla();
                            limpiarConsola();
                            return menuEmpleadoIngreso(legajo, categoria);
                        }
                        else
                        {
                            if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "e") == 0)
                            {
                                limpiarConsola();
                                ubicar(27, 10);
                                rlutil::setColor(rlutil::RED);
                                cout << "Usted no esta habilitado para cancelar pedidos de EGRESO de productos" << endl;
                                rlutil::setColor(rlutil::CYAN);
                                presioneUnaTecla();
                                limpiarConsola();
                                return menuEmpleadoIngreso(legajo, categoria);
                            }
                        }
                    }
                }
                if (encontro == false)
                {
                    limpiarConsola();
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "No se encontro ningun pedido" << endl;
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();
                    return menuEmpleadoIngreso(legajo, categoria);
                }
                else
                {
                    limpiarConsola();
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Pedido encontrado!" << endl;
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();

                    int op = 1;
                    int y = 0;
                    do
                    {
                        rlutil::setBackgroundColor(rlutil::BLACK);
                        rlutil::setColor(rlutil::WHITE);
                        rlutil::hidecursor();
                        limpiarConsola();
                        showItemIngreso("                 CANCELAR PEDIDOS", 30, 8, 0);
                        showItemIngreso("=======================================================", 30, 9, 0);
                        showItemIngreso("- OK        ", 38, 11, y == Opcion1);
                        showItemIngreso("- Cancelar  ", 38, 12, y == Opcion2);

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
                                limpiarConsola();
                                for (int x = 0; x < cantPed; x++)
                                {
                                    ped1 = pedArc1.leer(x);
                                    if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "i") == 0)
                                    {
                                        ped1Aux[x].setTipoPedido("c");
                                        pedArc1.guardar(ped1Aux[x], x);

                                    }
                                }
                                delete[]ped1Aux;

                                ubicar(27, 10);
                                rlutil::setColor(rlutil::GREEN);
                                cout << "Pedido cancelado con exito!" << endl;
                                rlutil::setColor(rlutil::CYAN);
                                presioneUnaTecla();
                                limpiarConsola();
                                return menuEmpleadoIngreso(legajo, categoria);
                                break;
                            case 1:
                                op = 0;
                                return menuEmpleadoIngreso(legajo, categoria);
                                limpiarConsola();
                                break;
                            }
                        }

                    } while (op != 0);
                }
                return menuEmpleadoIngreso(legajo, categoria);
                break;
            }
            case 3:
                op = 0;
                limpiarConsola();
                return menuPrincipal();
                break;
            case 4:
                op = 0;
                limpiarConsola();
                return menuEmpleado();
                break;
            }

        }
    }while (op != 0);
}

//TODO: Menu empleado para egreso de productos
void menuEmpleadoEgreso(int legajo, int categoria)//si tiene categoria 2 se encaga del egreso de productos por pedido
{
    int opcion;
    int y = 0;
    int op = 1;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        showItemEgreso("                  EGRESO DE STOCK", 30, 8, 0);
        showItemEgreso("=======================================================", 30, 9, 0);
        showItemEgreso("- Registrar nuevo pedido      ", 30, 10, y == Opcion1);
        showItemEgreso("- Cargar pedido pendiente     ", 30, 11, y == Opcion2);
        showItemEgreso("- Cancelar pedido             ", 30, 12, y == Opcion3);
        showItemIngreso("- Menu Principal              ", 30, 13, y == Opcion4);
        showItemIngreso("-=======================================================", 30, 14, 0);
        showItemIngreso("- Volver al inicio de sesion  ", 30, 15, y == Opcion5);
        
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
            if (y > 4) {
                y = 4;
            }
            break;
        case 1: // ENTER

            switch (y)
            {
            case 0:
            {
                op = 0;
                Pedido ped;
                PedidosArchivo pedArc;
                ped.cargar(legajo, categoria);
                limpiarConsola();
                return menuEmpleadoEgreso(legajo, categoria);
                break;
            }  
            case 1:
            {
                op = 0;
                bool repite = true;
                bool cancelado = false;
                int cont = 0;
                bool stockInsuficiente = false;
                do
                {
                    Pedido ped1;
                    PedidosArchivo pedArc1;
                    Producto* prod;
                    ProductosArchivo prodArc;
                    int idPedido;
                    int opcion;
                    bool encontro = false;

                    limpiarConsola();
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::YELLOW);
                    cout << "CARGAR PEDIDO PENDIENTE" << endl;
                    ubicar(27, 11);
                    cout << "=======================================================" << endl;
                    ubicar(27, 12);
                    rlutil::setColor(rlutil::WHITE);
                    cout << "Ingrese ID de pedido";
                    ubicar(27, 13);
                    rlutil::setColor(rlutil::CYAN);
                    cin >> idPedido;
                    limpiarConsola();

                    for (int x = 0; x < pedArc1.getCantidad(); x++)
                    {
                        ped1 = pedArc1.leer(x);
                        if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "e") == 0)
                        {
                            if (ped1.getEstadoPedido() == false)
                            {
                                cont++;
                                encontro = true;
                                repite = false;

                            }
                            else
                            {
                                limpiarConsola();
                                ubicar(27, 10);
                                rlutil::setColor(rlutil::RED);
                                cout << "No se pueden cancelar pedidos ya cargados" << endl;
                                rlutil::setColor(rlutil::CYAN);
                                presioneUnaTecla();
                                limpiarConsola();
                                return menuEmpleadoEgreso(legajo, categoria);
                            }
                        }
                        else
                        {
                            if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "c") == 0)
                            {
                                limpiarConsola();
                                ubicar(27, 10);
                                rlutil::setColor(rlutil::RED);
                                cout << "El pedido fue cancelado con anterioridad." << endl;
                                rlutil::setColor(rlutil::CYAN);
                                presioneUnaTecla();
                                limpiarConsola();
                                cancelado = true;
                                encontro = true;
                                repite = false;
                                return menuEmpleado();
                            }
                            else
                            {
                                if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "i") == 0)
                                {
                                    limpiarConsola();
                                    encontro = true;
                                    repite = false;
                                    ubicar(27, 10);
                                    rlutil::setColor(rlutil::RED);
                                    cout << "No tiene permitido cargar pedidos de ingreso de stock" << endl;
                                    rlutil::setColor(rlutil::CYAN);
                                    presioneUnaTecla();
                                    limpiarConsola();
                                    return menuEmpleadoEgreso(legajo, categoria);
                                }
                                else
                                {
                                    if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "e") == 0 && ped1.getEstadoPedido() != false)
                                    {
                                        limpiarConsola();
                                        ubicar(27, 10);
                                        rlutil::setColor(rlutil::RED);
                                        cout << "El pedido ya fue cargado anteriormente";
                                        rlutil::setColor(rlutil::CYAN);
                                        presioneUnaTecla();
                                        limpiarConsola();
                                        return menuEmpleadoEgreso(legajo, categoria);
                                    }
                                }
                            }
                        }
                    }
                    if (encontro == true && cancelado == false)
                    {

                        limpiarConsola();
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Pedido encontrado!";
                        rlutil::setColor(rlutil::CYAN);
                        presioneUnaTecla();
                        limpiarConsola();

                        prod = new Producto[prodArc.getCantidad()];
                        for (int i = 0; i < prodArc.getCantidad(); i++)
                        {
                            prod[i] = prodArc.leer(i);
                        }


                        for (int x = 0; x < pedArc1.getCantidad(); x++)
                        {
                            ped1 = pedArc1.leer(x);
                            if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "e") == 0 && ped1.getEstadoPedido() == false)
                            {
                                for (int i = 0; i < prodArc.getCantidad(); i++)
                                {
                                    if (ped1.getIdProducto() == prod[i].getIdProd())
                                    {
                                        if (ped1.getCantidadProducto() > prod[i].getStock()) {
                                            stockInsuficiente = true;
                                            cout << "entre" << endl;
                                            presioneUnaTecla();

                                        }
                                    }
                                }
                            }
                        }
                        if (stockInsuficiente)
                        {

                            limpiarConsola();
                            ubicar(27, 10);
                            rlutil::setColor(rlutil::RED);
                            cout << "No hay stock suficiente para el pedido";
                            rlutil::setColor(rlutil::CYAN);
                            presioneUnaTecla();
                            limpiarConsola();
                            return menuEmpleadoEgreso(legajo, categoria);
                        }
                        else
                        {
                            int y = 0;
                            int op = 1;
                            if (!stockInsuficiente)
                            {
                                do
                                {
                                    rlutil::setBackgroundColor(rlutil::BLACK);
                                    rlutil::setColor(rlutil::WHITE);
                                    rlutil::hidecursor();
                                    limpiarConsola();
                                    showItemEgreso("Desea guardar el pedido ingresado?", 30, 9, 0);
                                    showItemEgreso("- OK       ", 30, 11, y == Opcion1);         // Pienso que si se setea dentro del if que pregunte antes de setearlo
                                    showItemEgreso("- Cancelar ", 30, 12, y == Opcion2);    //Si quiere o no guardarlo pero tambien tendria que descontar stock en Opcion 1

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
                                            for (int x = 0; x < pedArc1.getCantidad(); x++)
                                            {
                                                ped1 = pedArc1.leer(x);
                                                if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "e") == 0 && ped1.getEstadoPedido() == false)
                                                {
                                                    for (int i = 0; i < prodArc.getCantidad(); i++)
                                                    {
                                                        if (ped1.getIdProducto() == prod[i].getIdProd())
                                                        {
                                                            prod[i].descontarStock(ped1.getCantidadProducto());
                                                            ped1.setEstadoPedido(true);
                                                            prodArc.guardar(prod[i], i);
                                                            pedArc1.guardar(ped1, x);
                                                        }
                                                    }
                                                }
                                            }
                                            limpiarConsola();
                                            ubicar(27, 10);
                                            rlutil::setColor(rlutil::GREEN);
                                            cout << "Pedido cargado con exito" << endl;
                                            rlutil::setColor(rlutil::CYAN);
                                            presioneUnaTecla();
                                            limpiarConsola();
                                            delete[]prod;
                                            return menuEmpleadoEgreso(legajo, categoria);
                                            break;
                                        case 1:
                                            op = 0;
                                            return menuEmpleadoEgreso(legajo, categoria);
                                            break;
                                        }
                                    }

                                } while (op != 0);
                            }
                        }
                    }
                    else
                    {
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::RED);
                        cout << "Pedido no encontrado/incorrecto" << endl;
                        rlutil::setColor(rlutil::CYAN);
                        presioneUnaTecla();
                        limpiarConsola();
                        return menuEmpleadoEgreso(legajo, categoria);
                    }
                } while (repite);
                return menuEmpleadoEgreso(legajo, categoria);
                break;
            }
            case 2:
            {
                op = 0;
                Pedido ped1, *ped1Aux;
                PedidosArchivo pedArc1;
                int cantPed;
                int idPedido;
                int reg;
                bool encontro = false;
                bool cancelado = false;
                
                cantPed = pedArc1.getCantidad();
                ped1Aux = new Pedido[cantPed];

                limpiarConsola();
                ubicar(27, 10);
                rlutil::setColor(rlutil::YELLOW);
                cout << "CANCELAR PEDIDO DE EGRESO" << endl;
                ubicar(27, 11);
                cout << "=======================================================" << endl;
                ubicar(27, 12);
                rlutil::setColor(rlutil::WHITE);
                cout << "Ingrese ID de pedido: ";
                rlutil::setColor(rlutil::CYAN);
                cin >> idPedido;
                limpiarConsola();

                for (int x = 0; x < pedArc1.getCantidad(); x++)
                {
                    ped1 = pedArc1.leer(x);
                    if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "e") == 0)
                    {
                        encontro = true;
                        reg = x;
                        ped1Aux[x] = ped1;
                    }
                    else
                    {
                        if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "c") == 0)
                        {
                            ubicar(27, 10);
                            rlutil::setColor(rlutil::RED);
                            cout << "El pedido fue cancelado con anterioridad." << endl;
                            rlutil::setColor(rlutil::CYAN);
                            presioneUnaTecla();
                            limpiarConsola();
                            return menuEmpleadoEgreso(legajo, categoria);
                        }
                        else
                        {
                            if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "i") == 0)
                            {
                                ubicar(27, 10);
                                rlutil::setColor(rlutil::RED);
                                cout << "Usted no esta habilitado para cancelar pedidos de INGRESO de productos" << endl;
                                rlutil::setColor(rlutil::CYAN);
                                return menuEmpleadoEgreso(legajo, categoria);
                                presioneUnaTecla();
                                limpiarConsola();
                            }
                        }
                    }
                }
                if (encontro == false)
                {
                    limpiarConsola();
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "No se encontro ningun pedido" << endl;
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();
                    return menuEmpleadoEgreso(legajo, categoria);
                }
                else
                {
                    limpiarConsola();
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Pedido encontrado!" << endl;
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();

                    int op = 1;
                    int y = 0;
                    do
                    {
                        rlutil::setBackgroundColor(rlutil::BLACK);
                        rlutil::setColor(rlutil::WHITE);
                        rlutil::hidecursor();
                        limpiarConsola();
                        showItemEgreso("                 CANCELAR PEDIDOS", 30, 8, 0);
                        showItemEgreso("=======================================================", 30, 9, 0);
                        showItemEgreso("- OK        ", 38, 11, y == Opcion1);
                        showItemEgreso("- Cancelar  ", 38, 12, y == Opcion2);

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
                                limpiarConsola();
                                for (int x = 0; x < cantPed; x++)
                                {
                                    ped1 = pedArc1.leer(x);
                                    if (ped1.getIdPedido() == idPedido && strcmp(ped1.getTipoPedido(), "e") == 0)
                                    {
                                        ped1Aux[x].setTipoPedido("c");
                                        pedArc1.guardar(ped1Aux[x], x);

                                    }
                                }
                                ubicar(27, 10);
                                rlutil::setColor(rlutil::GREEN);
                                cout << "Pedido " << ped1Aux[op].getIdPedido() << " cancelado con exito!" << endl;
                                rlutil::setColor(rlutil::CYAN);
                                presioneUnaTecla();
                                limpiarConsola();
                                return menuEmpleadoEgreso(legajo, categoria);
                                delete[]ped1Aux;
                                break;
                            case 1:
                                op = 0;
                                return menuEmpleadoEgreso(legajo, categoria);
                                limpiarConsola();
                                break;
                            }
                        }

                    } while (op != 0);
                }
                return menuEmpleadoEgreso(legajo, categoria);
                break;
            }
            case 3:
                op = 0;
                limpiarConsola();
                return menuPrincipal();
                break;
            case 4:
                op = 0;
                limpiarConsola();
                return menuEmpleado();
                break;
            }
        }
    } while (op != 0);
}   

//TODO: Login administrador
void menuAdmin()
{
    int legajo;
    int password;
    int intentos = 0;
    Empleado e, admin;
    EmpleadosArchivo ea;
    bool ingreso = false;
    bool repite = true;
    
    
    /*char caracter;// clave asterisco
    string pasword;*/
    limpiarConsola();

    do
    {
        //TODO: Ingreso Administrador
        ubicar(27, 10);
        rlutil::setColor(rlutil::YELLOW);
        cout << "                INGRESO ADMINISTRADOR" << endl;
        ubicar(27, 11);
        cout << "=======================================================" << endl;
        ubicar(27, 12);
        rlutil::setColor(rlutil::WHITE);
        cout << "Ingrese nro de legajo: ";
        rlutil::setColor(rlutil::CYAN);
        cin >> legajo;
        ubicar(27, 13);
        rlutil::setColor(rlutil::WHITE);
        cout  << "Ingrese su clave de ingreso: ";
        rlutil::setColor(rlutil::CYAN);
        cin >> password;
         
        //TODO: CLave asterisco
        // cout<<"Ingrese su clave de ingreso: "<<endl<<endl;
        //caracter = getch();
        //while (caracter != 13)
        //{
        //    pasword.push_back(caracter);
        //    cout << "*";
        //    caracter = getch();
        //}




        limpiarConsola();

        for (int x = 0; x < ea.getCantidad(); x++)
        {
            e = ea.leer(x);
            if (e.getLegajo() == legajo && e.getPassword() == password && e.getCategoria()== 999)
            {
                admin = e;
                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "Ingreso exitoso! Bienvenido " << admin.getNombre() << " " << admin.getApellido();
                rlutil::setColor(rlutil::CYAN);
                ingreso = true;
                repite = false;
                presioneUnaTecla();
                limpiarConsola();
            }
            else
            {
                if (e.getLegajo() == legajo && e.getPassword() == password && e.getCategoria() != 999)
                {
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "Solamente se permite ingresos con cuenta ADMIN";
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();
                    return menuAdmin();
                    
                }
            }
        }
        if (ingreso == false)
        {
            intentos++;
            if (intentos < 3 && intentos > 0)
            {
                limpiarConsola();   
                ubicar(27, 10);
                rlutil::setColor(rlutil::RED);
                cout << "Legajo o clave invalida, vuelva a intentar" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
            }
        }
        if (intentos == 3)
        {
            limpiarConsola();
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "Muchos ingresos fallidos, se cerrara el programa" << endl;
            rlutil::setColor(rlutil::CYAN);
            presioneUnaTecla();
            return;
        }
    }
    while (repite);

    menuPrincipalAdmin(admin);

}

//TODO: Menu de informes
void menuInformes()
{

    bool encontro = false;
    Empleado emp, empAux;
    do
    {
        EmpleadosArchivo empArc;
        int idEmp;
        int opcion;
        int password;
        int intentos = 0;
        int reg;

        limpiarConsola();
        rlutil::setColor(rlutil::YELLOW);
        ubicar(27, 10);
        cout << "                 Consulta de informes" << endl;
        ubicar(27, 11);
        cout << "=======================================================" << endl;
        ubicar(27, 12);
        rlutil::setColor(rlutil::WHITE);
        cout << "Ingrese el ID del empleado: ";
        rlutil::setColor(rlutil::CYAN);
        cin >> idEmp;

        for (int x = 0; x < empArc.getCantidad(); x++)
        {
            emp = empArc.leer(x);
            if (emp.getLegajo() == idEmp && emp.getEstado() == false)
            {
                limpiarConsola();
                rlutil::setColor(rlutil::RED);
                ubicar(27, 10);
                cout << "El empleado fue dado de baja"; 
                presioneUnaTecla();
                limpiarConsola();
            }
            else
            {

                if (emp.getLegajo() == idEmp && emp.getEstado() == true)
                {
                    empAux = emp;
                    rlutil::setColor(rlutil::GREEN);
                    limpiarConsola();
                    ubicar(27, 10);
                    cout << "Empleado encontrado!" << endl;
                    ubicar(27, 12);
                    rlutil::setColor(rlutil::WHITE);
                    cout << "Presione una tecla para continuar.." << endl;
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();
                    encontro = true;
                }
            }
        }
        if (encontro == false)
        {
            limpiarConsola();
            rlutil::setColor(rlutil::RED);
            ubicar(27, 10);
            cout << "El empleado no existe";
            presioneUnaTecla();
            limpiarConsola();
        }

    } while (!encontro);

    limpiarConsola();
    //pedirle la clave para volver a validar que sea el admin

    limpiarConsola();
    int opcion;
    int y = 0;
    int op = 1;
    rlutil::setColor(rlutil::YELLOW);
    ubicar(30, 10);
    cout << "               Solicitud de INFORMES" << endl;
    ubicar(30, 11);
    cout << "=======================================================" << endl;
    ubicar(30, 12);
    rlutil::setColor(rlutil::CYAN);
    cout << "Nombre: ";
    rlutil::setColor(rlutil::WHITE);
    cout << empAux.getNombre();
    rlutil::setColor(rlutil::CYAN);
    ubicar(30, 13);
    cout << "Apellido: ";
    rlutil::setColor(rlutil::WHITE);
    cout << empAux.getApellido();
    ubicar(30, 14);
    cout << "Legajo: ";
    rlutil::setColor(rlutil::WHITE);
    cout << empAux.getLegajo();
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
    rlutil::hidecursor();
    do
    {

        showItem("       Seleccione el informe para el empleado", 30, 16, 0);
        showItem("=======================================================", 30, 17, 0);
        showItem("         - Resumen anual de pedidos mensuales          ", 30, 18, y == Opcion1);//Faltan detalles, pero esta casi listo
        showItem("         - Cantidad de egresos por producto            ", 30, 19, y == Opcion2);//Faltan detalles, pero esta casi listo
        showItem("         - Cantidad de ingresos por producto           ", 30, 20, y == Opcion3);//Faltan detalles, pero esta casi listo
        showItem("         - Stock de productos por categoria            ", 30, 21, y == Opcion4);
        showItem("         - Productos mas vendidos en el mes            ", 30, 22, y == Opcion5);
        showItem("         - Historial productos menos vendidos          ", 30, 23, y == Opcion6);
        showItem("         - Resumen semanal de pedidos                  ", 30, 24 ,y == Opcion7);
        showItem("         - Volver al inicio de sesion                  ", 30, 25, y == Opcion8);
        showItem("=======================================================", 30, 26, 0);
        showItem("                     - Volver                          ", 30, 27 ,y == Opcion9);

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
            if (y > 8) {
                y = 8;
            }
            break;
        case 1: // ENTER

            switch (y)
            {
            case 0:
            {
                op = 0;
                Pedido ped, ped1;
                PedidosArchivo pedArc, pedArc1;
                Informe inf;
                InformesArchivo infArc;

                int meses[12] = {};
                int mesesTotales[12]={};
                int idPedAnt = 0;

                for (int i = 0; i < pedArc.getCantidad(); i++)
                {
                    ped = pedArc.leer(i);
                    if (empAux.getLegajo() == ped.getLegajo() && ped.getEstadoPedido() == true && ped.getIdPedido()!= idPedAnt)
                    {
                        meses[ped.getFechaPedido().getMes() - 1] += 1;
                        idPedAnt = ped.getIdPedido();
                    }
                }
                int cont = 0;
                for (int i = 0; i < 12; i++)
                {
                    mesesTotales[i]= mesesTotales[i]++;
                }

                bool band = false;

                limpiarConsola();
                for (int i = 0; i < 12; i++)
                {
                    ped = pedArc.leer(i);
                    if (band == false)
                    {
                        cout << "\t" << "\t" << empAux.getNombre() <<" "<<empAux.getApellido()<<" "<< "Legajo: " << empAux.getLegajo() << "\t" << "Anio " << ped.getFechaPedido().getAnio() << endl;
                        cout << "\t" << "\t" << "----------------------------------------------------" << endl;
                        cout << "\t" << "\t" << "\t" << "  MES" << "\t" << "\t" << "Pedidos cargados"<< endl;
                        cout << "\t" << "\t" << "====================================================" << endl;
                        band = true;
                    }
                    switch (i+1)
                    {
                    case 1:
                        cout << "\t" << "\t" << "\t" << "Enero" << "\t" << "\t" << "\t";
                        break;
                    case 2:
                        cout << "\t" << "\t" << "\t" << "Febrero" << "\t" << "\t" << "\t";
                        break;
                    case 3:
                        cout << "\t" << "\t" << "\t" << "Marzo" << "\t" << "\t" << "\t";
                        break;
                    case 4:
                        cout << "\t" << "\t" << "\t" << "Abril" << "\t" << "\t" << "\t";
                        break;
                    case 5:
                        cout << "\t" << "\t" << "\t" << "Mayo" << "\t" << "\t" << "\t";
                        break;
                    case 6:
                        cout << "\t" << "\t" << "\t" << "Junio" << "\t" << "\t" << "\t";
                        break;
                    case 7:
                        cout << "\t" << "\t" << "\t" << "Julio" << "\t" << "\t" << "\t";
                        break;
                    case 8:
                        cout << "\t" << "\t" << "\t" << "Agosto" << "\t" << "\t" << "\t";
                        break;
                    case 9:
                        cout << "\t" << "\t" << "\t" << "Septiembre" << "\t" << "\t";
                        break;
                    case 10:
                        cout << "\t" << "\t" << "\t" << "Octubre" << "\t" << "\t" << "\t";
                        break;
                    case 11:
                        cout << "\t" << "\t" << "\t" << "Noviembre" << "\t" << "\t";
                        break;
                    case 12:
                        cout << "\t" << "\t" << "\t" << "Diciembre" << "\t" << "\t";
                        break;
                    }
                    cout << meses[i]<<endl;
                }
                cout << "\t" << "\t"<<"====================================================" << endl;
                presioneUnaTecla();
                limpiarConsola();
                break;
            }
            case 1:
            {
                op = 0;

                if (empAux.getCategoria() == 1)
                {
                    limpiarConsola();
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "No tiene permitido ver informes de Egresos";
                    presioneUnaTecla();
                    limpiarConsola();
                    return menuInformes();
                }

                Pedido *ped, ped1;
                PedidosArchivo pedArc;
                Producto *prod,prod1;
                ProductosArchivo prodArc;
                Informe *inf;
                InformesArchivo infArc;
                bool *b;
                int cantidadProd = prodArc.getCantidad();
                int cantidadPed = pedArc.getCantidad();
                prod = new Producto[cantidadProd];
                ped = new Pedido[cantidadPed];
                inf = new Informe[cantidadProd];

                for (int x = 0; x < cantidadPed; x++)
                {
                    ped[x] = pedArc.leer(x);

                }
                for (int i=0; i < cantidadProd; i++)
                {
                    prod[i] = prodArc.leer(i);
                    inf[i].setIdProd(prod[i].getIdProd());
                    inf[i].setNombre(prod[i].getNombre());
                    inf[i].setCant(0);
                    inf[i].setEstado(prod[i].getEstado());
                    infArc.guardar(inf[i]);
                }

                for (int x = 0; x < cantidadPed+1; x++)
                {
                    for (int i = 0; i < cantidadProd; i++)
                    {
                        if (inf[i].getIdProd() == ped[x].getIdProducto() &&
                            strcmp(ped[x].getTipoPedido(), "e") == 0 &&
                            ped[x].getEstadoPedido() == true )
                        {
                            inf[i].setTipoPed(ped[x].getTipoPedido());
                            inf[i].aumentarCantidad(ped[x].getCantidadProducto());
                            infArc.guardar(inf[i], i);   
                        }
                    }
                    limpiarConsola();
                }
                
                delete[]ped;
                delete[]prod;
                delete[]inf;
                
                cout <<"Empleado: " << empAux.getNombre() << " " << empAux.getApellido() << " " << "Legajo: " << empAux.getLegajo() << endl <<endl;
                infArc.mostrarArchivo();
                presioneUnaTecla();
                limpiarConsola();
                break;
            }
            case 2:
            {
                op = 0;

                if (empAux.getCategoria() == 2)
                {
                    limpiarConsola();
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "No tiene permitido ver informes de Ingresos";
                    presioneUnaTecla();
                    limpiarConsola();
                    return menuInformes();
                }
                Pedido* ped, ped1;
                PedidosArchivo pedArc;
                Producto* prod, prod1;
                ProductosArchivo prodArc;
                Informe* inf;
                InformesArchivo infArc;
                bool* b;
                int cantidadProd = prodArc.getCantidad();
                int cantidadPed = pedArc.getCantidad();
                prod = new Producto[cantidadProd];
                ped = new Pedido[cantidadPed];
                inf = new Informe[cantidadProd];

                for (int x = 0; x < cantidadPed; x++)
                {
                    ped[x] = pedArc.leer(x);

                }
                for (int i = 0; i < cantidadProd; i++)
                {
                    prod[i] = prodArc.leer(i);
                    inf[i].setIdProd(prod[i].getIdProd());
                    inf[i].setNombre(prod[i].getNombre());
                    inf[i].setCant(0);
                    inf[i].setEstado(prod[i].getEstado());
                    infArc.guardar(inf[i]);

                }

                for (int x = 0; x < cantidadPed + 1; x++)
                {
                    for (int i = 0; i < cantidadProd; i++)
                    {
                        if (inf[i].getIdProd() == ped[x].getIdProducto() &&
                            strcmp(ped[x].getTipoPedido(), "i") == 0 &&
                            ped[x].getEstadoPedido() == true)
                        {
                            inf[i].setTipoPed(ped[x].getTipoPedido());
                            inf[i].aumentarCantidad(ped[x].getCantidadProducto());
                            infArc.guardar(inf[i], i);
                        }
                    }
                    limpiarConsola();
                }
                cout << "Empleado: " << empAux.getNombre() << " " << empAux.getApellido() << " " << "Legajo: " << empAux.getLegajo() << endl << endl;
                infArc.mostrarArchivo();


                delete[]ped;
                delete[]prod;
                delete[]inf;

                presioneUnaTecla();
                limpiarConsola();
                break;
            }
            case 3: {
                op = 0;

                limpiarConsola();

                int categoria;
                bool catExiste = false;
                ProductosArchivo prodArc;
                int cantArchivos = prodArc.getCantidad();
                Producto* prod = new Producto[cantArchivos];
                prodArc.leerTodos(prod, cantArchivos);


                do {
                    cout << "Ingrese la categoria a consultar " << endl;
                    cin >> categoria;

                    for (int x = 0; x < cantArchivos; x++)
                    {
                        if (prod[x].getCategoriaProd() == categoria) {
                            catExiste = true;
                            break;
                        }
                    }

                } while (catExiste == false);

                for (int x = 0; x < cantArchivos; x++)
                {
                    if (prod[x].getCategoriaProd() == categoria && prod[x].getEstado() == true) {
                        cout << left;
                        cout << setw(4) << prod[x].getCategoriaProd();
                        cout << setw(4) << prod[x].getIdProd();
                        cout << setw(10) << prod[x].getMarca();
                        cout << setw(16) << prod[x].getNombre();
                        cout << setw(4) << prod[x].getStock();
                    }
                }

                presioneUnaTecla();

                delete[] prod;

            }
                  break;
            case 4:
                op = 0;
                break;
            case 5:
                op = 0;
                break;
            case 6:
                op = 0;
                break;
            case 7:
                op = 0;
                break;
            case 8:
                op = 0;
                return menuAdmin();
                break;
            }
        }
       
    }while (op != 0);

}

//TODO: Menu principal del administrador
void menuPrincipalAdmin(Empleado admin)
{
    int op=1;
    int y = 0;
    limpiarConsola();
    do
    {
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
    rlutil::hidecursor();

    showItemEgreso("                  MENU ADMINISTRADOR", 30, 8, 0);
    showItemEgreso("=======================================================", 30, 9, 0);
    showItemEgreso("- Solicitar informes            ", 30, 10, y == Opcion1);
    showItemEgreso("- Alta empleado                 ", 30, 11, y == Opcion2);
    showItemEgreso("- Baja a empleado               ", 30, 12, y == Opcion3);
    showItemEgreso("- Modificar datos empleado      ", 30, 13, y == Opcion4);
    showItemEgreso("- Alta productos                ", 30, 14, y == Opcion5);
    showItemEgreso("- Baja de productos             ", 30, 15, y == Opcion6);
    showItemEgreso("- Modificar productos           ", 30, 16, y == Opcion7);
    showItemEgreso("=======================================================", 30, 18, 0);
    showItem("- Volver a inicio de sesion     ", 30, 17, y == Opcion8);
    showItem("- Menu principal                ", 30, 19, y == Opcion9);

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
        if (y > 8) {
            y =8;
        }
        break;
    case 1: // ENTER

        switch (y)
        {
        case 0:
            op = 0;
            break;
        case 1:
            op = 0;
            break;
        case 2:
            op = 0;
            break;
        case 3:
            op = 0;
            break;
        case 4:
            op = 0;
            break;
        case 5:
            op = 0;
            break;
        case 6:
            op = 0;
            break;
        case 7:
            op = 0;
            break;
        case 8:
            op = 0;
            break;

        }
    }

} while (op != 0);

    switch (y)
    {
    case 0:
        menuInformes();
        return menuPrincipalAdmin(admin);
        break;
    case 1:
    {
        Empleado e;
        EmpleadosArchivo ea;
        cin.ignore();
        e.cargar();
        ea.guardar(e);
        return menuPrincipalAdmin(admin);
        break;
    }
    case 2:
        menuBajaEmpleado(admin);
        return menuPrincipalAdmin(admin);
        break;
    case 3:
        rlutil::setColor(rlutil::CYAN);
        rlutil::setBackgroundColor(rlutil::BLACK);
        menuEditarEmpleado(admin);
        return menuPrincipalAdmin(admin);
        break;
    case 4:
        Producto prod;
        ProductosArchivo prodArc;
        cin.ignore();
        prod.cargar();
        prodArc.guardar(prod);
        return menuPrincipalAdmin(admin);
        break;

    case 5:
        limpiarConsola();
        menuBajaProducto(admin);
        return menuPrincipalAdmin(admin);
        break;
    case 6:
        limpiarConsola();
        menuEditarProducto(admin);
        return menuPrincipalAdmin(admin);
        break;
    case 7:
        limpiarConsola();
        return menuAdmin();
        break;
    case 8:
        limpiarConsola();
        return menuPrincipal();
        break;
    }
}

//TODO: Menu baja de empleados
void menuBajaEmpleado(Empleado admin)
{
    Empleado e, eAux;
    EmpleadosArchivo ea;
    int legajo;
    int opcion;
    bool encontro = false;
    int password;
    int intentos = 0;
    int reg;
    bool dadoDeBaja = false;
    int op = 1;
    int y = 0;

    limpiarConsola();
    rlutil::setColor(rlutil::YELLOW);
    ubicar(27, 10);
    cout << "BAJA DE EMPLEADO" << endl;
    ubicar(27, 11);
    cout << "=======================================================" << endl;
    ubicar(27, 12);
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el legajo del empleado: ";
    rlutil::setColor(rlutil::CYAN);
    cin >> legajo;
    limpiarConsola();
    //pedirle la clave para volver a validar que sea el admin

    for (int x = 0; x < ea.getCantidad(); x++)
    {
        e = ea.leer(x);

        if (e.getLegajo() == legajo && e.getEstado() == true && admin.getLegajo() == legajo)
        {
            limpiarConsola();
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "Sin permiso para darse de baja como ADMIN a si mismo"; // No detecta este mensaje 
            presioneUnaTecla();
            limpiarConsola();
            return menuPrincipalAdmin(admin);
        }

        if (e.getLegajo() == legajo && e.getEstado() == true && e.getCategoria() == 999)
        {
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "No se permite dar de baja a otro ADMIN" << endl;
            presioneUnaTecla();
            limpiarConsola();
            return menuPrincipalAdmin(admin);
        }
        
        if (e.getLegajo() == legajo && e.getEstado() == false)
        {
            limpiarConsola();
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "El empleado ya fue dado de baja anteriormente" << endl;
            dadoDeBaja = true;
            presioneUnaTecla();
            limpiarConsola();
            return menuPrincipalAdmin(admin);
            
        }
        else
        {
            if (e.getLegajo() == legajo && e.getEstado() == true)
            {
                eAux = e;
                encontro = true;
                reg = x;
            }
        }
    }
    if (encontro == true && dadoDeBaja == false)
    {
        rlutil::setColor(rlutil::GREEN);
        limpiarConsola();
        ubicar(27, 10);
        cout << "Empleado encontrado!" << endl;
        ubicar(27, 12);
        rlutil::setColor(rlutil::WHITE);
        cout << "Presione una tecla para continuar.." << endl;
        rlutil::setColor(rlutil::CYAN);
        presioneUnaTecla();
        limpiarConsola();

        rlutil::setColor(rlutil::YELLOW);
        ubicar(27, 10);
        cout << "               Solicitud Baja de empleado" << endl;
        ubicar(27, 11);
        cout << "=======================================================" << endl;
        ubicar(27, 12);
        rlutil::setColor(rlutil::CYAN);
        cout << "Nombre: ";
        rlutil::setColor(rlutil::WHITE);
        cout << eAux.getNombre();
        rlutil::setColor(rlutil::CYAN);
        ubicar(27, 13);
        cout << "Apellido: ";
        rlutil::setColor(rlutil::WHITE);
        cout << eAux.getApellido();
        ubicar(27, 14);
        cout << "Legajo: ";
        rlutil::setColor(rlutil::WHITE);
        cout << eAux.getLegajo();


        do
        {
            rlutil::setBackgroundColor(rlutil::BLACK);
            rlutil::setColor(rlutil::WHITE);
            rlutil::hidecursor();
            showItemEgreso("               Desea darlo de baja?", 27, 16, 0);
            showItemEgreso("=======================================================", 27, 17, 0);
            showItemEgreso("                - Si, dar de baja                      ", 27, 18, y == Opcion1);
            showItemEgreso("                - Cancelar                             ", 27, 19, y == Opcion2);
      

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
                    break;
                case 1:
                    op = 0;
                    break;
                }
            }

        } while (op != 0);


        if (y == 0)
        {
            limpiarConsola();
            ubicar(27, 10);
            rlutil::setColor(rlutil::WHITE);
            cout << "Ingrese su clave personal" << endl;
            ubicar(27, 11);
            rlutil::setColor(rlutil::CYAN);
            cin >> password;
            limpiarConsola();

            while (admin.getPassword() != password)
            {
                ubicar(27, 10);
                rlutil::setColor(rlutil::RED);
                cout << "Clave invalida, Intente nuevamente" << endl;
                ubicar(27, 11);
                rlutil::setColor(rlutil::WHITE);
                cout <<endl<< "Ingrese su clave personal" << endl;
                ubicar(27, 12);
                rlutil::setColor(rlutil::CYAN);
                cin >> password;

                intentos++;
                if (intentos == 3)
                {
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "Demaciados intentos fallidos, se cerrara el programa" << endl;
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    return;
                }
            }
            limpiarConsola();
            eAux.setEstado(false);
            ea.guardar(eAux, reg);
            ubicar(27, 10);
            rlutil::setColor(rlutil::GREEN);
            cout << "El empleado a sido dado de baja con exito!" << endl;
            rlutil::setColor(rlutil::CYAN);
            presioneUnaTecla();
            limpiarConsola();
            return menuPrincipalAdmin(admin);
        }

    }
    else
    {
        ubicar(27, 10);
        rlutil::setColor(rlutil::RED);
        cout << "No se encontro el empleado solicitado" << endl; //No detecta este mensaje
        rlutil::setColor(rlutil::CYAN);
        presioneUnaTecla();
        limpiarConsola();
        return menuPrincipalAdmin(admin);
    }
}

//TODO: Menu editar empleados
void menuEditarEmpleado(Empleado admin)
{
    Empleado e, eAux;
    EmpleadosArchivo ea; 
    int legajo;
    bool encontro = false;
    int reg=0;
    int op = 1;
    int y = 0;

    limpiarConsola();
    ubicar(27, 10);
    rlutil::setColor(rlutil::YELLOW);
    cout << "                   EDITAR EMPLEADO" << endl;
    ubicar(27, 11);
    cout << "=======================================================" << endl;
    ubicar(27, 12);
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el legajo del empleado: ";//Validar que el legajo este en el sistema antes de pedir la opcion a modificar
    rlutil::setColor(rlutil::CYAN);
    cin >> legajo;
    limpiarConsola();


    for (int x = 0; x < ea.getCantidad(); x++)
    {
        e = ea.leer(x);

        if (e.getLegajo() == legajo && e.getCategoria() == 999 && admin.getLegajo() != legajo)
        {
            ubicar(27, 10);
            cout << "No tiene permitido modificar los datos de otro ADMIN";
            presioneUnaTecla();
            return menuEditarEmpleado(admin);

        }
        else
        {

            if (e.getLegajo() == legajo)
            {
                limpiarConsola();
                encontro = true;
                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "Empleado encontrado!" << endl;
                ubicar(27, 11);
                cout << "Nombre: " << e.getNombre()<<endl;
                ubicar(27, 12);
                cout << "Apellido: " << e.getApellido()<<endl;
                ubicar(27, 13);
                cout << "Legajo: " << e.getLegajo()<<endl;
                rlutil::setColor(rlutil::CYAN);

                eAux = e;
                reg = x;
                presioneUnaTecla();
                limpiarConsola();

            }
        }
    }
    if (encontro == true)
    {

        do
        {
            rlutil::setBackgroundColor(rlutil::BLACK);
            rlutil::setColor(rlutil::WHITE);
            rlutil::hidecursor();
            //limpiarConsola();
            showItemEgreso("              SELECCIONAR DATO A MODIFICAR", 30, 8, 0);
            showItemEgreso("=======================================================", 30, 10, 0);
            showItemEgreso("                    - Nombre                           ", 30, 11, y == Opcion1);
            showItemEgreso("                    - Apellido                         ", 30, 12, y == Opcion2);
            showItemEgreso("                    - DNI                              ", 30, 13, y == Opcion3);
            showItemEgreso("                    - Domicilio                        ", 30, 14, y == Opcion4);
            showItemEgreso("                    - Email                            ", 30, 15, y == Opcion5);
            showItemEgreso("                    - Telefono                         ", 30, 16, y == Opcion6);
            showItemEgreso("                    - Categoria                        ", 30, 17, y == Opcion7);
            showItemEgreso("                    - Clave                            ", 30, 18, y == Opcion8);
            showItemEgreso("=======================================================", 30, 19, 0);
            showItemEgreso("                        VOLVER                         ", 30, 20, y == Opcion9);

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
                if (y > 8) {
                    y = 8;
                }
                break;
            case 1: // ENTER

                switch (y)
                {
                case 0:
                    op = 0;
                    limpiarConsola();
                    char nombre[30];
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::YELLOW);
                    cout << "Ingrese nuevo nombre: ";
                    rlutil::setColor(rlutil::CYAN);
                    cin.getline(nombre, 30, '\n');
                    eAux.setNombre(nombre);
                    ea.guardar(eAux, reg);
                    ubicar(27, 12);
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Nombre actualizado con exito!" << endl;
                    presioneUnaTecla();
                    limpiarConsola();
                    break;
                case 1:
                    op = 0;
                    limpiarConsola();
                    char apellido[30];
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::YELLOW);
                    cout << "Ingrese nuevo apellido: ";
                    rlutil::setColor(rlutil::CYAN);
                    cin.getline(apellido, 30, '\n');
                    eAux.setApellido(apellido);
                    ea.guardar(eAux, reg);
                    ubicar(27, 12);
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Apellido actualizado con exito!" << endl;
                    presioneUnaTecla();
                    limpiarConsola();
                    break;
                case 2:
                    op = 0;
                    limpiarConsola();
                    int dni;
                    rlutil::setColor(rlutil::YELLOW);
                    ubicar(27, 10);
                    cout << "Ingrese nuevo numero de dni: ";
                    rlutil::setColor(rlutil::CYAN);
                    cin >> dni;
                    eAux.setDni(dni);
                    ea.guardar(eAux, reg);
                    ubicar(27, 12);
                    rlutil::setColor(rlutil::GREEN);
                    cout << "DNI actualizado con exito!" << endl;
                    presioneUnaTecla();
                    limpiarConsola();
                    break;
                case 3:
                {
                    op = 0;
                    limpiarConsola();
                    Domicilio dom;
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::YELLOW);
                    cout << "Actualizacion de domicilio" << endl;
                    rlutil::setColor(rlutil::CYAN);
                    dom.cargar();
                    eAux.setDomicilio(dom);
                    ea.guardar(eAux, reg);
                    ubicar(27, 12);
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Domicilio actualizado con exito!" << endl;
                    presioneUnaTecla();
                    limpiarConsola();
                    break;
                }
                case 4:
                    op = 0;
                    limpiarConsola();
                    char email[30];
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::YELLOW);
                    cout << "Ingrese nuevo email: ";
                    rlutil::setColor(rlutil::CYAN);
                    cin.getline(email, 30, '\n');
                    ea.guardar(eAux, reg);
                    ubicar(27, 12);
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Email actualizado con exito!" << endl;
                    presioneUnaTecla();
                    break;
                case 5:
                    op = 0;
                    limpiarConsola();
                    int telefono;
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::YELLOW);
                    cout << "Ingrese nuevo nro de telefono: ";
                    rlutil::setColor(rlutil::CYAN);
                    cin >> telefono;
                    eAux.setTelefono(telefono);
                    ea.guardar(eAux, reg);
                    ubicar(27, 12);
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Telefono actualizado con exito!" << endl;
                    presioneUnaTecla();
                    break;
                case 6:
                    op = 0;
                    limpiarConsola();
                    int categoria;
                    do
                    {

                        ubicar(27, 10);
                        rlutil::setColor(rlutil::YELLOW);
                        cout << "Ingrese nueva categoria: ";
                        rlutil::setColor(rlutil::CYAN);
                        cin >> categoria;

                        if (categoria != 1 && categoria != 2 && categoria != 999)
                        {
                            ubicar(27, 12);//No lo detecta el ubicar()
                            rlutil::setColor(rlutil::RED);
                            cout << endl << "                           Ingrese una categoria valida ";
                            rlutil::setColor(rlutil::CYAN);
                            presioneUnaTecla();
                            limpiarConsola();
                        }


                    } while (categoria != 1 && categoria != 2 && categoria != 999);

                    eAux.setCategoria(categoria);
                    ea.guardar(eAux, reg);
                    ubicar(27, 12);
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Categoria actualizada con exito!" << endl;
                    presioneUnaTecla();
                    break;
                case 7:
                    op = 0;
                    limpiarConsola();
                    int password;
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::YELLOW);
                    cout << "Ingrese nueva contraseña: ";
                    rlutil::setColor(rlutil::CYAN);
                    cin >> password;
                    eAux.setPassword(password);
                    ea.guardar(eAux, reg);
                    ubicar(27, 12);

                    rlutil::setColor(rlutil::GREEN);
                    cout << "Contraseña actualizada con exito!" << endl;
                    presioneUnaTecla();
                    break;
                case 8:
                    op = 0;
                    break;
                }

            }

        } while (op != 0);

    }
    else
    {
        limpiarConsola();
        ubicar(27, 10);
        rlutil::setColor(rlutil::RED);
        cout << "No se encontro el empleado solicitado" << endl;
        rlutil::setColor(rlutil::CYAN);
        limpiarConsola();
    }  
}

//TODO: Menu baja de productos
void menuBajaProducto(Empleado admin)
{
    {
        Producto prod, prodAux;
        ProductosArchivo prodArc;
        int idProducto;
        int opcion;
        bool encontro = false;
        int password;
        int intentos = 0;
        int reg;
        bool dadoDeBaja = false;
        int op = 1;
        int y = 0;

        limpiarConsola();
        rlutil::setColor(rlutil::YELLOW);
        ubicar(27, 10);
        cout << "                 BAJA DE PRODUCTOS" << endl;
        ubicar(27, 11);
        cout << "=======================================================" << endl;
        ubicar(27, 12);
        rlutil::setColor(rlutil::WHITE);
        cout << "Ingrese el ID del producto: ";
        ubicar(27, 13);
        rlutil::setColor(rlutil::CYAN);
        cin >> idProducto;
        limpiarConsola();
        //pedirle la clave para volver a validar que sea el admin

        for (int x = 0; x < prodArc.getCantidad(); x++)
        {
            prod = prodArc.leer(x);

            if (prod.getIdProd() == idProducto && prod.getEstado() == false)
            {
                limpiarConsola();
                ubicar(27, 10);
                rlutil::setColor(rlutil::RED);
                cout << "El PRODUCTO ya fue dado de baja anteriormente" << endl;
                dadoDeBaja = true;
                presioneUnaTecla();
                limpiarConsola();
                return menuPrincipalAdmin(admin);

            }
            else
            {
                if (prod.getIdProd() == idProducto && prod.getEstado() == true)
                {
                    prodAux = prod;
                    encontro = true;
                    reg = x;
                }
            }
        }
        if (encontro == true && dadoDeBaja == false)
        {
            rlutil::setColor(rlutil::GREEN);
            limpiarConsola();
            ubicar(27, 10);
            cout << "Producto encontrado!" << endl;
            ubicar(27, 12);
            rlutil::setColor(rlutil::WHITE);
            cout << "Presione una tecla para continuar.." << endl;
            rlutil::setColor(rlutil::CYAN);
            presioneUnaTecla();
            limpiarConsola();

            rlutil::setColor(rlutil::YELLOW);
            ubicar(27, 10);
            cout << "               Solicitud Baja de producto" << endl;
            ubicar(27, 11);
            cout << "=======================================================" << endl;
            ubicar(27, 12);
            rlutil::setColor(rlutil::CYAN);
            cout << "Nombre: ";
            rlutil::setColor(rlutil::WHITE);
            cout << prodAux.getNombre();
            rlutil::setColor(rlutil::CYAN);
            ubicar(27, 13);
            cout << "Marca: ";
            rlutil::setColor(rlutil::WHITE);
            cout << prodAux.getMarca();
            ubicar(27, 14);
            cout << "ID producto: ";
            rlutil::setColor(rlutil::WHITE);
            cout << prodAux.getIdProd();

            do
            {
                rlutil::setBackgroundColor(rlutil::BLACK);
                rlutil::setColor(rlutil::WHITE);
                rlutil::hidecursor();
                showItemEgreso("         Desea dar de baja al producto?", 27, 16, 0);
                showItemEgreso("=======================================================", 27, 17, 0);
                showItemEgreso("                - Si, dar de baja                      ", 27, 18, y == Opcion1);
                showItemEgreso("                - Cancelar                             ", 27, 19, y == Opcion2);

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
                        break;
                    case 1:
                        op = 0;
                        break;
                    }
                }

            } while (op != 0);


            if (y == 0)
            {
                limpiarConsola();
                ubicar(27, 10);
                rlutil::setColor(rlutil::WHITE);
                cout << "Ingrese su clave personal" << endl;
                ubicar(27, 11);
                rlutil::setColor(rlutil::CYAN);
                cin >> password;
                limpiarConsola();

                while (admin.getPassword() != password)
                {
                    limpiarConsola();
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "Clave invalida, Intente nuevamente" << endl;
                    ubicar(27, 11);
                    rlutil::setColor(rlutil::WHITE);
                    cout << endl << "Ingrese su clave personal: " ;
                    rlutil::setColor(rlutil::CYAN);
                    cin >> password;

                    intentos++;
                    if (intentos == 3)
                    {
                        limpiarConsola();
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::RED);
                        cout << "Demaciados intentos fallidos, se cerrara el programa" << endl;
                        rlutil::setColor(rlutil::CYAN);
                        presioneUnaTecla();
                        return;
                    }
                }
                limpiarConsola();
                prodAux.setEstado(false);
                prodArc.guardar(prodAux, reg);
                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "El Producto fue dado de baja con exito!" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
                return menuPrincipalAdmin(admin);
            }

        }
        else
        {
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "No se encontro el producto mencionado" << endl;
            rlutil::setColor(rlutil::CYAN);
            return menuPrincipalAdmin(admin);
        }
    }
}

//TODO:Menu editar productos
void menuEditarProducto(Empleado admin)
{
    {
        Producto prod, prodAux;
        ProductosArchivo prodArc;
        int idProd;
        bool encontro = false;
        int reg = 0;
        int op = 1;
        int y = 0;

        limpiarConsola();
        ubicar(27, 10);
        rlutil::setColor(rlutil::YELLOW);
        cout << "                   EDITAR PRODUCTO" << endl;
        ubicar(27, 11);
        cout << "=======================================================" << endl;
        ubicar(27, 12);
        rlutil::setColor(rlutil::WHITE);
        cout << "Ingrese el ID del PRODUCTO: ";//Validar que el legajo este en el sistema antes de pedir la opcion a modificar
        rlutil::setColor(rlutil::CYAN);
        cin >> idProd;
        limpiarConsola();


        for (int x = 0; x < prodArc.getCantidad(); x++)
        {
            prod = prodArc.leer(x);

            if (prod.getIdProd() == idProd)
            {
                if (prod.getEstado() == false)
                {
                    int op = 1;
                    int y = 0;
                    do
                    {
                        int pos = x;
                        rlutil::setBackgroundColor(rlutil::BLACK);
                        rlutil::setColor(rlutil::WHITE);
                        rlutil::hidecursor();
                        limpiarConsola();
                        showItem("El producto fue dado de baja, quiere darlo de alta nuevamente?", 30, 9, 0);
                        showItem("- OK       ", 53, 11, y == Opcion1);
                        showItem("- Cancelar ", 53, 12, y == Opcion2);

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
                                limpiarConsola();
                                ubicar(27, 10);
                                prod.setEstado(true);
                                prodArc.guardar(prod, pos);
                                ubicar(27, 12);
                                rlutil::setColor(rlutil::GREEN);
                                cout << "Producto dado de alta!" << endl;
                                presioneUnaTecla();
                                limpiarConsola();
                                return menuPrincipalAdmin(admin);
                                break;
                            case 1:
                                op = 0;
                                break;
                            }
                        }

                    } while (op != 0);
                 }
                limpiarConsola();
                encontro = true;
                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "Producto encontrado!" << endl;
                ubicar(27, 11);
                cout << "Nombre: " << prod.getNombre() << endl;
                ubicar(27, 12);
                cout << "Marca: " << prod.getMarca() << endl;
                ubicar(27, 13);
                cout << "ID producto: " << prod.getIdProd() << endl;
                rlutil::setColor(rlutil::CYAN);

                prodAux = prod;
                reg = x;
                presioneUnaTecla();
                limpiarConsola();
            }
        }
        if (encontro == true)
        {

            do
            {
                rlutil::setBackgroundColor(rlutil::BLACK);
                rlutil::setColor(rlutil::WHITE);
                rlutil::hidecursor();
                showItemEgreso("          SELECCIONAR DATO A MODIFICAR", 30, 8, 0);
                showItemEgreso("=======================================================", 30, 10, 0);
                showItemEgreso("- Nombre         ", 38, 11, y == Opcion1);
                showItemEgreso("- Marca          ", 38, 12, y == Opcion2);
                showItemEgreso("- Cod Categoria  ", 38, 13, y == Opcion3);
                showItemEgreso("- Precio         ", 38, 14, y == Opcion4);
                showItemEgreso("- Stock          ", 38, 15, y == Opcion5);
                showItemEgreso("=======================================================", 30, 16, 0);
                showItemEgreso("-VOLVER          ", 38, 17, y == Opcion6);

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
                    if (y > 5) {
                        y = 5;
                    }
                    break;
                case 1: // ENTER

                    switch (y)
                    {
                    case 0:
                        op = 0;
                        limpiarConsola();
                        char nombre[30];
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::YELLOW);
                        cout << "Ingrese nuevo nombre: ";
                        rlutil::setColor(rlutil::CYAN);
                        cin.getline(nombre, 30, '\n');
                        prodAux.setNombre(nombre);
                        prodArc.guardar(prodAux, reg);
                        ubicar(27, 12);
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Nombre del producto actualizado con exito!" << endl;
                        presioneUnaTecla();
                        limpiarConsola();
                        return menuPrincipalAdmin(admin);
                        break;
                    case 1:
                        op = 0;
                        limpiarConsola();
                        char marca[30];
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::YELLOW);
                        cout << "Ingrese nueva MARCA: ";
                        rlutil::setColor(rlutil::CYAN);
                        cin.getline(marca, 30, '\n');
                        prodAux.setMarca(marca);
                        prodArc.guardar(prodAux, reg);
                        ubicar(27, 12);
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Marca actualizada con exito!" << endl;
                        presioneUnaTecla();
                        limpiarConsola();
                        return menuPrincipalAdmin(admin);
                        break;
                    case 2:
                        op = 0;
                        limpiarConsola();
                        int codCategoria;
                        rlutil::setColor(rlutil::YELLOW);
                        ubicar(27, 10);
                        cout << "Ingrese nuevo COD de CATEGORIA: ";
                        rlutil::setColor(rlutil::CYAN);
                        cin >> codCategoria;
                        prodAux.setCategoriaProd(codCategoria);
                        prodArc.guardar(prodAux, reg);
                        ubicar(27, 12);
                        rlutil::setColor(rlutil::GREEN);
                        cout << "CATEGORIA actualizada con exito!" << endl;
                        presioneUnaTecla();
                        limpiarConsola();
                        return menuPrincipalAdmin(admin);
                        break;
                    case 3:
                        op = 0;
                        limpiarConsola();
                        float precio;
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::YELLOW);
                        cout << "Ingrese nuevo precio unitario: ";
                        rlutil::setColor(rlutil::CYAN);
                        cin >> precio;
                        prodAux.setPrecio(precio);
                        prodArc.guardar(prodAux, reg);
                        ubicar(27, 12);
                        rlutil::setColor(rlutil::GREEN);
                        cout << "PRECIO actualizado con exito!" << endl;
                        presioneUnaTecla();
                        limpiarConsola();
                        return menuPrincipalAdmin(admin);
                        break;
                    case 4:
                        op = 0;
                        limpiarConsola();
                        int stock;
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::YELLOW);
                        cout << "Ingrese nuevo stock disponible: ";
                        rlutil::setColor(rlutil::CYAN);
                        cin >> stock;
                        prodAux.setStock(stock);
                        prodArc.guardar(prodAux, reg);
                        ubicar(27, 12);
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Stock disponible actualizado con exito!" << endl;
                        presioneUnaTecla();
                        limpiarConsola();
                        return menuPrincipalAdmin(admin);
                        break;
                    case 5:
                        op = 0;
                        return menuPrincipalAdmin(admin);
                        break;
                    }

                }

            } while (op != 0);

            cin.ignore();
        }
        else
        {
            limpiarConsola();
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "No se encontro el PRODUCTO solicitado" << endl;
            rlutil::setColor(rlutil::CYAN);
            limpiarConsola();
            return menuPrincipalAdmin(admin);
        }


    }
}

//TODO: MOSTRAR ITEMS DE LOS MENU
void showItem(const char* text, int posx, int posy, bool selected) {

    if (selected) {
        rlutil::setBackgroundColor(rlutil::MAGENTA);
        rlutil::locate(posx - 3, posy);
        std::cout << " " << (char)175 << " " << text << " " << (char)174 << " " << std::endl;

    }
    else {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::locate(posx - 3, posy);
        std::cout << "   " << text << "   " << std::endl;
    }

    rlutil::setBackgroundColor(rlutil::BLACK);
}
void showItemIngreso(const char* text, int posx, int posy, bool selected) {

    if (selected) {
        rlutil::setBackgroundColor(rlutil::LIGHTBLUE);
        rlutil::locate(posx - 3, posy);
        std::cout << " " << (char)175 << " " << text << " " << (char)174 << " " << std::endl;

    }
    else {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::locate(posx - 3, posy);
        std::cout << "   " << text << "   " << std::endl;
    }

    rlutil::setBackgroundColor(rlutil::BLACK);
}
void showItemEgreso(const char* text, int posx, int posy, bool selected) {

    if (selected) {
        rlutil::setBackgroundColor(rlutil::LIGHTRED);
        rlutil::locate(posx - 3, posy);
        std::cout << " " << (char)175 << " " << text << " " << (char)174 << " " << std::endl;

    }
    else {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::locate(posx - 3, posy);
        std::cout << "   " << text << "   " << std::endl;
    }

    rlutil::setBackgroundColor(rlutil::BLACK);
}
void ubicar(int posx, int posy)
{
    rlutil::locate(posx, posy);
}