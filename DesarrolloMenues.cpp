#include <iostream>
#include <ctime>
#include "rlutil.h"
using namespace std;
#include "DesarrolloMenues.h"
#include "menu.h"
#include "amblArtista.h"
#include "abmlDisco.h"
#include "abmlCliente.h"
#include "abmlVenta.h"

void pausarSistema() {
#ifdef _WIN32
    cout << "Presiona Enter para continuar" << endl; /// Similar a la función limpiar pantalla, aquí la función que alterna entre windows y ubuntu para pausar el sistema.
    system("pause");  // Pausa en Windows.
#else
    cout << "Presiona Enter para continuar" << endl;
    cin.ignore();
    cin.get();  // Pausa en Linux.
#endif
}

void menuPrincipal(){
    int opcionPrincipal = 1;
    while(opcionPrincipal != 0){
        mostrarMenuPrincipal();
        cin >> opcionPrincipal;
        switch(opcionPrincipal){
            case 1:
                desarrolloMenuArtistas();
            break;

            case 2:
                desarrolloMenuDiscos();
            break;

            case 3:
                desarrolloMenuClientes();
            break;

            case 4:
                desarrolloMenuVentas();
            break;

            case 5:
                desarrolloMenuRecaudacion();
            break;

            case 0:
                rlutil::setColor(rlutil::DARKGREY);
                cout << "Saliendo del programa";
            break;

            default:
                rlutil::setColor(rlutil::RED);
                cout << "Opcion Incorrecta" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;
        }
    }
}

void desarrolloMenuArtistas(){
    int opcionArtistas = 1;
    while(opcionArtistas != 0){
        mostrarMenuArtistas();
        cin >> opcionArtistas;
        switch(opcionArtistas){
            case 1:
                if(altaArtista());
                else{

                    rlutil::setColor(rlutil::RED);
                    cout << "No se pudo agregar el Artista"<< endl;
                }
                    rlutil::setColor(rlutil::LIGHTBLUE);
                    pausarSistema();
            break;

            case 2:
                if (bajaArtista()) {
                    rlutil::setColor(rlutil::GREEN);
                    cout << "El Artista fue borrado Correctamente " <<endl;
                } else {
                    rlutil::setColor(rlutil::RED);
                    cout << "No se pudo borrar el Artista" <<endl;
                }
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;

            case 3:
                if(modificarArtista()){
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Artista modificado Correctamente"<< endl;
                }

                else {
                    rlutil::setColor(rlutil::RED);
                    cout <<"No se pudo modificar el Artista" << endl;
                }
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;

            case 4:
                limpiarPantalla();
                listadoArtistas();
            break;

            case 5:
                desarrolloMenuConsultasArtistas();
                pausarSistema();
            break;

            case 0:
                rlutil::setColor(rlutil::DARKGREY);
                cout << "Volver al Menu Principal" << endl;
                pausarSistema();
            break;

            default:
                rlutil::setColor(rlutil::RED);
                cout << "Opcion Incorrecta" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;
        }
    }
}

void desarrolloMenuDiscos(){
    int opcionDiscos = 1;
    while(opcionDiscos != 0){
        mostrarMenuDiscos();
        cin >> opcionDiscos;
        switch(opcionDiscos){
            case 1:
                if(altaRegistro()){
                    rlutil::setColor(rlutil::GREEN);
                    cout <<"Se agrego el registro Correctamente" << endl;
                }else{
                    rlutil::setColor(rlutil::RED);
                    cout << "No se pudo agregar el Registro" << endl;
                }
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;

            case 2:
                if(bajaRegistro()) {
                    rlutil::setColor(rlutil::GREEN);
                    cout << "El registro fue borrado Correctamente " << endl;
                }else{
                    rlutil::setColor(rlutil::RED);
                    cout << "No se pudo borrar el Registro" << endl;
                }
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;

            case 3:
                if(modificacionRegistro()){
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Registro modificado Correctamente" << endl;
                }
                else{
                    rlutil::setColor(rlutil::RED);
                    cout << "No se pudo modificar el Registro" << endl;
                }
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;

            case 4:
                limpiarPantalla();
                listadoRegistros();
            break;

            case 5:
                desarrolloMenuConsultasDiscos();
            break;

            case 6:
                desarrolloMenuListadosDiscos();
            break;

            case 0:
                rlutil::setColor(rlutil::DARKGREY);
                cout << "Volver al Menu Principal" << endl;
                pausarSistema();
            break;

            default:
                rlutil::setColor(rlutil::RED);
                cout << "Opcion Incorrecta" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;
        }
    }
}

void desarrolloMenuClientes(){
    int opcionClientes = 1;
    while(opcionClientes != 0){
     mostrarMenuClientes();
     cin >> opcionClientes;
        switch(opcionClientes){
            case 1:
                if(altaCliente()){
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Se agrego el cliente Correctamente" << endl;
                }
                else{
                    rlutil::setColor(rlutil::RED);
                    cout << "No se pudo agregar el Cliente" << endl;
                }
                pausarSistema();
                rlutil::setColor(rlutil::LIGHTBLUE);
            break;

            case 2:
                if(bajaCliente()){
                    rlutil::setColor(rlutil::GREEN);
                    cout << "El cliente fue borrado Correctamente"<< endl;
                }
                else{
                    rlutil::setColor(rlutil::RED);
                    cout << "No se pudo borrar el Cliente" << endl;
                }
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;

            case 3:
                if(modificacionRegistroClientes()) {
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Datos modificados Correctamente" << endl;
                }
                else {
                    rlutil::setColor(rlutil::RED);
                    cout << "No se pudo modificar los Datos" << endl;
                }
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;

            case 4:
                limpiarPantalla();
                listadoRegistrosClientes();
            break;

            case 5:
                desarrolloMenuConsultasClientes();
            break;

            case 0:
                rlutil::setColor(rlutil::DARKGREY);
                cout << "Volver al Menu Principal" << endl;
                pausarSistema();
            break;

            default:
                rlutil::setColor(rlutil::RED);
                cout << "Opcion Incorrecta" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;
        }
    }
}

void desarrolloMenuVentas(){
    int opcionVentas = 1;
    while(opcionVentas != 0){
        mostrarMenuVentas();
        cin >> opcionVentas;
        switch(opcionVentas){
            case 1:
                if(altaVenta()) {
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Se agrego la venta Correctamente" << endl;
                }
                else{
                    rlutil::setColor(rlutil::RED);
                    cout << "No se pudo agregar la Venta" << endl;
                }
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;

            case 2:
                if(bajaVenta()) {
                    rlutil::setColor(rlutil::GREEN);
                    cout <<"Se borro la venta Correctamente"<<endl;
                }
                else{
                    rlutil::setColor(rlutil::RED);
                    cout << "No se pudo borrar la Venta "<<endl;
                }
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;

            case 3:
                if(modificacionRegistroVentas()){
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Venta modificada Correctamente" << endl;
                }
                else{
                    rlutil::setColor(rlutil::RED);
                    cout << "No se pudo modificar la Venta." << endl;
                }
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;

            case 4:
                limpiarPantalla();
                listadoRegistrosVentas();
            break;

            case 5:
                desarrolloMenuConsultasVentas();
            break;

            case 6:
                desarrolloMenuListadosVentas();
            break;

            case 0:
                rlutil::setColor(rlutil::DARKGREY);
                cout << "Volver al Menu Principal" << endl;
                pausarSistema();
            break;

            default:
                rlutil::setColor(rlutil::RED);
                cout << "Opcion Incorrecta" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;
        }
    }
}

void desarrolloMenuConsultasArtistas(){
    int opcionConsultasArtista = 1;
    while(opcionConsultasArtista !=0){
        mostrarMenuConsultasArtistas();
        cin>>opcionConsultasArtista;
        switch(opcionConsultasArtista){
            case 1:
                limpiarPantalla();
                buscarArtistaPorId();
                pausarSistema();
            break;

            case 0:
                rlutil::setColor(rlutil::DARKGREY);
                cout << "Volver al Menu Anterior" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
            break;

            default:
                rlutil::setColor(rlutil::RED);
                cout << "Opcion Incorrecta" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;
        }
    }
}

void desarrolloMenuConsultasDiscos(){
    int opcionConsultasDisco = 1;
    while(opcionConsultasDisco !=0){
        mostrarMenuConsultasDiscos();
        cin >> opcionConsultasDisco;
        switch(opcionConsultasDisco){
            case 1:
                limpiarPantalla();
                buscarDiscoPorId();
                pausarSistema();
            break;

            case 0:
                rlutil::setColor(rlutil::DARKGREY);
                cout << "Volver al Menu Anterior" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
            break;

            default:
                rlutil::setColor(rlutil::RED);
                cout << "Opcion Incorrecta" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;
        }
    }
}

void desarrolloMenuConsultasClientes(){
    int opcionConsultasCliente = 1;
    while (opcionConsultasCliente !=0){
        mostrarMenuConsultasClientes();
        cin >>opcionConsultasCliente;
        switch(opcionConsultasCliente){
            case 1:
                limpiarPantalla();
                buscarClientePorId();
                pausarSistema();
            break;

            case 0:
                rlutil::setColor(rlutil::DARKGREY);
                cout << "Volver al Menu Anterior" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;

            default:
                rlutil::setColor(rlutil::RED);
                cout << "Opcion Incorrecta" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;
        }
    }
}

void desarrolloMenuConsultasVentas(){
    int opcionConsultasVenta = 1;
    while (opcionConsultasVenta !=0){
        mostrarMenuConsultasVentas();
        cin >>opcionConsultasVenta;
        switch(opcionConsultasVenta){
            case 1:
                limpiarPantalla();
                buscarVentaPorId();
                pausarSistema();
            break;

            case 0:
                rlutil::setColor(rlutil::DARKGREY);
                cout << "Volver al Menu Anterior" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
            break;

            default:
                rlutil::setColor(rlutil::RED);
                cout << "Opcion Incorrecta" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;
        }
    }
}

void desarrolloMenuListadosDiscos(){
    int opcionListadosDisco = 1;
    while(opcionListadosDisco !=0){
        mostrarMenuListadosDiscos();
        cin >> opcionListadosDisco;
        switch(opcionListadosDisco){
            case 1:
                limpiarPantalla();
                listarDiscosPorArtistaInteractivo();
                pausarSistema();
            break;

            case 0:
                rlutil::setColor(rlutil::DARKGREY);
                cout << "Volver al Menu Anterior" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
            break;

            default:
                rlutil::setColor(rlutil::RED);
                cout << "Opcion Incorrecta" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;
        }
    }
}

void desarrolloMenuListadosVentas(){
    int opcionListadosVenta = 1;
    while(opcionListadosVenta !=0){
        mostrarMenuListadosVentas();
        cin >> opcionListadosVenta;
        switch(opcionListadosVenta){
            case 1:
                limpiarPantalla();
                listarVentasPorClienteInteractivo();
                pausarSistema();
            break;

            case 0:
                rlutil::setColor(rlutil::DARKGREY);
                cout << "Volver al Menu Anterior" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
            break;

            default:
                rlutil::setColor(rlutil::RED);
                cout << "Opcion Incorrecta" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;
        }
    }
}

void desarrolloMenuRecaudacion(){
    int opcionRecaudacion = 1;
    while(opcionRecaudacion !=0){
        mostrarMenuRecaudacion();
        cin >> opcionRecaudacion;
        switch(opcionRecaudacion){
            case 1:
                limpiarPantalla();
                mostrarRecaudacionPorFecha();
                pausarSistema();
            break;

            case 2:
                limpiarPantalla();
                mostrarRecaudacionPorAnio();
                pausarSistema();
            break;

            case 3:
                limpiarPantalla();
                mostrarRecaudacionPorMes();
                pausarSistema();
            break;

            case  4:
                limpiarPantalla();
                mostrarRecaudacionPorDia();
                pausarSistema();
            break;

            case 0:
                rlutil::setColor(rlutil::DARKGREY);
                cout << "Volver al Menu Principal" << endl;
                pausarSistema();
            break;

            default:
                rlutil::setColor(rlutil::RED);
                cout << "Opcion Incorrecta" << endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
                pausarSistema();
            break;
        }
    }
}
