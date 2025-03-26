#include <iostream>
#include <cstring>
#include <ctime>
#include "rlutil.h"
using namespace std;
#include "Cliente.h"
#include "Disco.h"
#include "Venta.h"
#include "ArchivoCliente.h"
#include "ArchivoDisco.h"
#include "ArchivoVenta.h"

bool Fecha::esMayorQueHoy() const { /// Mediante la libreria Ctime, seremos capaces de programar el sistema para que no permita ingresar ventas en fechas que superen la fecha actual.
    /// Obtener la fecha actual del sistema
    time_t tiempoActual = time(nullptr);
    tm* fechaActual = localtime(&tiempoActual);

    /// Crear una instancia de la fecha de hoy
    Fecha hoy(fechaActual->tm_mday, fechaActual->tm_mon + 1, fechaActual->tm_year + 1900);

    /// Usar el operador > o >= para comparar
    return (*this > hoy);
}

bool Fecha::esFechaValida() const { /// Validacion para los dias de los meses del año.
    if (mes < 1 || mes > 12) return false;
    if (dia < 1) return false;
    /// Días máximos según el mes
    int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
        diasEnMes[1] = 29; /// Febrero en año bisiesto
    }
    return dia <= diasEnMes[mes - 1];
}

///-------------------------------------------------------------PRIMERO LAS FUNCIONES DE VENTA DETALLE----------------------------------------------//

void VentaDetalle::cargarDetalle(int idV, int nuevoIdVentaDetalle) {
    idVenta = idV;
    idVentaDetalle = nuevoIdVentaDetalle; /// Se asigna un nuevo ID único para cada detalle
    Disco disco;
    ArchivoDisco archivoDisco;
    float precioUnitario = 0.0;
    rlutil::setColor(rlutil::WHITE);
    cout << "ID del Disco: ";
    cin >> idDisco;
    int pos = archivoDisco.buscarRegistro(idDisco, TODOS);
    if (pos != -1 && archivoDisco.leerRegistro(disco, idDisco) && disco.getEstado()){///MODIFICACION PARA CORREGIR ALTA DE VENTAS 02/12/2024
        rlutil::setColor(rlutil::GREEN);
        cout << "Disco encontrado: " << disco.getTitulo() << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        precioUnitario = disco.getPrecio();
    }else {
        rlutil::setColor(rlutil::RED);
        cout << "No se encontró el disco con ID: " << idDisco << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return;
    }
    cout << "Cantidad: ";
    cin >> cantidad;
    estado = true;
    monto = precioUnitario * cantidad;
}

void VentaDetalle::mostrarDetalle() {
    if (estado) {
        Disco disco;
        ArchivoDisco archivoDisco;
        if (archivoDisco.leerRegistro(disco, idDisco)) {
            rlutil::setColor(rlutil::LIGHTBLUE);
            cout << "ID Venta Detalle: " << idVentaDetalle << endl;
            cout << "ID Venta: " << idVenta << endl;
            cout << "ID Disco: " << idDisco << endl;
            cout << "Cantidad: " << cantidad << endl;
            cout << "Monto: $" << monto << endl; /// Muestra el monto ya calculado.
            cout<<"-----------------------------------"<<endl;
        }
    }
}

///----------------------------------------------AQUI VIENEN LAS FUNCIONES PARA VENTA-----------------------------------------------------------////

void Venta::cargarVenta(int id, int numeroCliente){
    this->numeroCliente = numeroCliente;
    cout << "ID del Cliente recibido: " << this->numeroCliente << endl;  /// Depuración.
    aumentarComprasCliente(numeroCliente);
    if (id == 0) {
        cout << "Id de la venta: ";
        cin >> idVenta;
        cin.ignore();
    }else{
        idVenta = id;}
        cout << "Fecha de la venta: " << endl;
        fechaVenta.cargarFecha();
    int agregarMas;
    do {
        agregarDetalle();
        cout << "Desea agregar Otro disco? (1 = Si, 0 = No): ";
        cin >> agregarMas;
    } while(agregarMas == 1 && cantidadDetalles < 10);
        estado = true;
}

float Venta::calcularMontoTotal() {
    ArchivoDisco archivoDisco;
    Disco disco;
    montoTotal = 0.0;
    for (int i = 0; i < cantidadDetalles; ++i) {
        int idDisco = detalles[i].getIdDisco();
        int cantidad = detalles[i].getCantidad();
        int pos = archivoDisco.buscarRegistro(idDisco, TODOS);
        if (pos != -1 && archivoDisco.leerRegistro(disco, idDisco)) {
            if (disco.getIdDisco() == idDisco) {
                float precioUnitario = disco.getPrecio();
                montoTotal += precioUnitario * cantidad;
            }
        }
    }
    return montoTotal;
}

void Venta::mostrarVenta(){
    if(estado==true){
        ArchivoDisco archivoDisco;
        Disco disco;
        Cliente cliente;
        ArchivoCliente archivoCliente;
        montoTotal = 0.0;
        rlutil::setColor(rlutil::LIGHTMAGENTA);
        cout<<"-----------------------------------"<<endl;
        cout <<"Id de la venta: " << idVenta << endl;
        cout <<"Numero de cliente: " << numeroCliente << endl;
        int pos = archivoCliente.buscarRegistroCliente(numeroCliente,CLIENTESTODOS);
        if (pos != -1 && archivoCliente.leerRegistroCliente(cliente, numeroCliente)&& cliente.getEstado()){
            rlutil::setColor(rlutil::GREEN);
            cout << "Nombre del Cliente: " << cliente.getNombre() << endl;
            cout << "Apellido del cliente: " << cliente.getApellido() << endl;
            rlutil::setColor(rlutil::LIGHTBLUE);
        }

        cout <<"Fecha de la venta: ";
        fechaVenta.mostrarFecha();
        cout<<"-----------------------------------"<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        cout <<"Detalles de la venta"<<endl
        ;
        for (int i = 0; i < cantidadDetalles; ++i) {
            int idDisco = detalles[i].getIdDisco();   /// Obtener el id del disco en el detalle.
            int cantidad = detalles[i].getCantidad();
            int pos = archivoDisco.buscarRegistro(idDisco, TODOS);
            if (pos != -1 && archivoDisco.leerRegistro(disco, idDisco)) {
                if (disco.getIdDisco() == idDisco) {
                    float precioUnitario = disco.getPrecio();
                    float montoDisco = precioUnitario * cantidad;
                    montoTotal += montoDisco;
                    detalles[i].mostrarDetalle();
                    cout << endl;
                }
            }
        }
        rlutil::setColor(rlutil::WHITE);
        cout << "Monto Total de la venta: $" << montoTotal << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        cout<<"-----------------------------------"<<endl;
    }
}

void Venta::agregarDetalle() {
    if (cantidadDetalles < 10){
        detalles[cantidadDetalles].cargarDetalle(idVenta, cantidadDetalles + 1);
        cantidadDetalles++;
    }else{
        rlutil::setColor(rlutil::RED);
        cout << "No se pueden agregar más de 10 discos a esta venta.";
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
}

void Venta::aumentarComprasCliente(int numeroCliente) {
    ArchivoCliente archivoCliente;
    Cliente cliente; /// Crear un objeto Cliente para almacenar los datos del cliente.
    int clientePos = archivoCliente.buscarRegistroCliente(numeroCliente, true);
        if (clientePos != -1) { /// Verifica si el cliente existe.
            if (archivoCliente.leerRegistroCliente(cliente, numeroCliente)) {
                int nuevasCompras = cliente.getComprasRealizadas() + 1; /// Incrementar el contador.
                archivoCliente.modificarComprasCliente(numeroCliente, nuevasCompras); /// Actualizar solo el contador.
            }else{
                rlutil::setColor(rlutil::RED);
                cout << "No se pudo leer el registro del cliente." <<endl;
                rlutil::setColor(rlutil::LIGHTBLUE);
        }   }else{
        rlutil::setColor(rlutil::RED);
        cout << "Cliente no encontrado." <<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
}
