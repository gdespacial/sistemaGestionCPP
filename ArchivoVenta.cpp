#include <iostream>
#include <cstring>
#include <ctime>
#include "rlutil.h"
using namespace std;
#include "Artista.h"
#include "Disco.h"
#include "Cliente.h"
#include "Venta.h"
#include "ArchivoArtista.h"
#include "ArchivoDisco.h"
#include "ArchivoCliente.h"
#include "ArchivoVenta.h"
#include "amblArtista.h"
#include "abmlDisco.h"
#include "abmlCliente.h"
#include "abmlVenta.h"


bool ArchivoVenta::grabarVenta(Venta regi){
    FILE *pVenta; /// Puntero file.
    pVenta = fopen(nombreVenta, "ab"); /// abrir archivo.
    if(pVenta == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "Error" << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    int escribio = fwrite(&regi, tamReg, 1, pVenta);
    fclose(pVenta);
    return escribio;
}

bool ArchivoVenta::leerVenta(Venta &regi, int idVenta) {
    FILE *pVenta = fopen(nombreVenta, "rb");
    if (pVenta == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "No se pudo abrir el archivo de Ventas para Leer. " << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    while (fread(&regi, sizeof(Venta), 1, pVenta) == 1){
        if (regi.getIdVenta() == idVenta) {
            fclose(pVenta);
            return true;
        }
    }
    fclose(pVenta);
    return false;
}

int ArchivoVenta::contarVentas(){
    FILE *pVenta;
    Venta regi;
    pVenta=fopen(nombreVenta, "rb");
    if(pVenta==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo"<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return -1;
    }
    fseek(pVenta,0, 2);
    int cantidadByte=ftell(pVenta);
    fclose(pVenta);
    ///cout << "Cantidad de ventas: " << cantidadByte / tamReg << endl;  /// DEPURACION QUE DEBE SER BORRADA.
    return cantidadByte/tamReg;
}

bool ArchivoVenta::listarVentas(){
    FILE *pVenta;
    Venta regi;
    pVenta=fopen(nombreVenta, "rb");
    if(pVenta==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo"<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    while(fread(&regi,tamReg,1,pVenta)==1){  /// Este while me permite listar todos los registros.
        regi.mostrarVenta();
        cout<<endl;
    }
    fclose(pVenta);
    return true;
}

int ArchivoVenta::buscarVentas(int id, bool keHago){  /// HECHA.
    FILE *pVenta;
    Venta regi;
    int pos=0;
    pVenta=fopen(nombreVenta, "rb");
    if(pVenta==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return -2;
    }
    if(keHago==true){
        while(fread(&regi,tamReg,1,pVenta)==1){
            if(regi.getIdVenta()==id &&regi.getEstado()){
                fclose(pVenta);
                return pos;
            }pos++;
        }
        fclose(pVenta);
        return -1;
    }else{
        while(fread(&regi,tamReg,1,pVenta)==1){
            if(regi.getIdVenta()==id){
                fclose(pVenta);
                return pos;
            }
            pos++;
        }
        fclose(pVenta);
        return -1;
    }
}

Venta ArchivoVenta::leerVentas(int ubicacion){
    FILE *pVenta;
    Venta reg;
    reg.setIdVenta(-1);
    pVenta=fopen(nombreVenta, "rb");
    if(pVenta==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return reg;
    }
    int cuanto=ubicacion*tamReg;
    int desde_donde=0;
    fseek(pVenta,cuanto, desde_donde);
    fread(&reg, tamReg,1, pVenta);
    fclose(pVenta);
    return reg;
}

bool ArchivoVenta::modificarVenta(Venta reg,int pos){
    FILE *pVenta;
    pVenta=fopen(nombreVenta, "rb+");
    if(pVenta==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    fseek(pVenta,pos*tamReg, 0);
    bool escribio=fwrite(&reg, tamReg,1, pVenta);
    fclose(pVenta);
    return escribio;
}

bool ArchivoVenta::buscarYMostrarVenta(int idVenta){
    FILE *pVenta;
    Venta reg;
    pVenta = fopen(nombreVenta, "rb");
    if (pVenta == NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
   while (fread(&reg, tamReg, 1, pVenta) == 1){
        if (reg.getIdVenta() == idVenta && reg.getEstado()) {
            reg.mostrarVenta();
            fclose(pVenta);
            return true;
        }
    }
    fclose(pVenta);
    rlutil::setColor(rlutil::RED);
    cout << "Venta no Encontrada" << endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    return false;
}

bool ArchivoVenta::leerVentaPorPosicion(Venta &reg, int posicion){
    FILE *pVenta = fopen(nombreVenta, "rb");
    if (pVenta == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "No se pudo abrir el archivo de ventas para leer." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    fseek(pVenta, posicion * sizeof(Venta), SEEK_SET);  /// Poner el puntero en la posición
    bool leido = fread(&reg, sizeof(Venta), 1, pVenta) == 1;  /// Lee el registro de la posición
    fclose(pVenta);
    return leido;
}

float ArchivoVenta::calcularGastoTotal(int numeroCliente){
    Venta reg;
    float gastoTotal = 0;
    int totalVentas = contarVentas();
    for(int i = 0; i < totalVentas; i++){
        if(leerVentaPorPosicion(reg, i) && reg.getNumeroCliente() == numeroCliente){
            gastoTotal+=reg.getMontoTotal();
        }
    }
    return gastoTotal;
}

void buscarVentaPorId(){
  ArchivoVenta archivoVenta;
    int idVen;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el numero de La Venta a buscar: ";
    cin >> idVen;
    if (!archivoVenta.buscarYMostrarVenta(idVen)){
        rlutil::setColor(rlutil::RED);
        cout << "No se encontró una Venta con el numero ingresado." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
}

///--------------------------------------------FUNCIONES DE ARCHIVO VENTA DETALLE-----------------------------------------------------------------//

bool ArchivoVentaDetalle::grabarVentaDetalle(VentaDetalle detalle) {
    FILE *pDetalle = fopen(nombreVentaDetalle, "ab"); /// Abre el archivo en modo agregar
    if (pDetalle == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "Error al abrir el archivo de detalles." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    size_t escribio = fwrite(&detalle, tamReg, 1, pDetalle);
    fclose(pDetalle); /// Cierra el archivo
    return escribio == 1;
}

bool ArchivoVentaDetalle::leerVentaDetalle(VentaDetalle &detalle, int pos){
    FILE *pDetalle = fopen(nombreVentaDetalle, "rb"); /// Abre el archivo en modo lectura
    if (pDetalle == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "No se pudo abrir el archivo de detalles." <<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    fseek(pDetalle, pos * tamReg, SEEK_SET); /// Mueve el puntero a la posición deseada
    size_t leido = fread(&detalle, tamReg, 1, pDetalle); /// Lee el detalle desde el archivo
    fclose(pDetalle); /// Cierra el archivo
    return leido == 1; /// Devuelve true si leyO correctamente
}

int ArchivoVentaDetalle::contarDetalles() {
    FILE *pDetalle = fopen(nombreVentaDetalle, "rb"); /// Abre el archivo en modo lectura
    if (pDetalle == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "No se pudo abrir el archivo." <<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return -1;
    }
    fseek(pDetalle, 0, SEEK_END); /// Mueve el puntero al final del archivo
    int cantidadDetalles = ftell(pDetalle) / tamReg; /// Calcula la cantidad de registros
    fclose(pDetalle); /// Cierra el archivo
    return cantidadDetalles; /// Devuelve la cantidad de detalles
}

bool ArchivoVentaDetalle::listarDetallesPorVenta(int idVenta) {
    FILE *pDetalle = fopen(nombreVentaDetalle, "rb"); /// Abre el archivo en modo lectura
    if (pDetalle == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "No se pudo abrir el archivo." <<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    VentaDetalle detalle;
    bool encontrado = false; /// Indica si se encontró al menos un detalle
    while (fread(&detalle, tamReg, 1, pDetalle) == 1){ /// Lee todos los detalles
        if (detalle.getIdVenta() == idVenta){ /// Compara el ID de la venta
            detalle.mostrarDetalle(); /// Muestra el detalle
            encontrado = true;
        }
    }
    fclose(pDetalle); /// Cierra el archivo
    return encontrado;/// Devuelve true si se encontraron detalles
}

int ArchivoVentaDetalle::buscarDetalles(int idVenta, bool keHago) {
    FILE *pDetalle;
    VentaDetalle detalle;
    int pos = 0;
    pDetalle = fopen(nombreVentaDetalle, "rb");
    if (pDetalle == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "No se pudo abrir el archivo." <<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return -2;
    }
    if (keHago == true) {
        while (fread(&detalle, tamReg, 1, pDetalle) == 1) {
            if (detalle.getIdVenta() == idVenta && detalle.getEstado()) { /// Verifica el estado
                fclose(pDetalle);
                return pos;
            }
            pos++;
        }
        fclose(pDetalle);
        return -1; /// No se encontró el detalle activo
    }else{
        while (fread(&detalle, sizeof(VentaDetalle), 1, pDetalle) == 1) {
            if (detalle.getIdVenta() == idVenta) { /// Verifica solo el ID de venta
                fclose(pDetalle);
                return pos;
            }
            pos++;
        }
        fclose(pDetalle);
        return -1;
    }
}

bool ArchivoVentaDetalle::modificarDetalle(VentaDetalle detalle, int pos) {
    FILE *pDetalle = fopen(nombreVentaDetalle, "rb+"); /// Abrir el archivo en modo lectura y escritura.
    if (pDetalle == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "No se pudo abrir el archivo." <<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false; /// Devuelve false si no se pudo abrir el archivo.
    }
    fseek(pDetalle, pos * tamReg, SEEK_SET); /// Mover el puntero a la posición deseada
    size_t escribio = fwrite(&detalle, tamReg, 1, pDetalle); /// Escribir el detalle en la posición.
    fclose(pDetalle); /// Cierra el archivo.
    return escribio == 1;
}

VentaDetalle ArchivoVentaDetalle::leerDetalles(int ubicacion) {
    FILE *pDetalle;
    VentaDetalle detalle;
    detalle.setIdVenta(-1);
    pDetalle = fopen(nombreVentaDetalle, "rb");
    if (pDetalle == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "No se pudo abrir el archivo." <<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return detalle;
    } /// Retorna un objeto vacío
    int cuanto = ubicacion * sizeof(VentaDetalle);
    fseek(pDetalle, cuanto, SEEK_SET);
    fread(&detalle, tamReg, 1, pDetalle); /// Leer el detalle desde el archivo
    fclose(pDetalle);
    return detalle; /// Retornar el detalle leído.
}

bool ArchivoVenta::listarVentasPorCliente(int numeroCliente) {
    FILE *pVenta;
    Venta reg;
    ArchivoCliente archivoCliente;
    Cliente cliente;
    pVenta = fopen(nombreVenta, "rb");

    if (pVenta == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "No se pudo abrir el archivo." <<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }

    bool hayVentas = false;

    if (archivoCliente.leerRegistroCliente(cliente, numeroCliente) && cliente.getEstado()) {  /// MODIFICACION 2/12/2024
        rlutil::setColor(rlutil::GREEN);
        cout << "Cliente: " << cliente.getNombre() << endl; /// Mostrar nombre del Cliente.
    }else{
        rlutil::setColor(rlutil::RED);
        cout << "Cliente No encontrado" << endl; /// DEPURACION PARA VER SI FUNCIONA. 2 /12 /2024
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
    cout << endl;
    while (fread(&reg, tamReg, 1, pVenta) == 1) {
        if (reg.getNumeroCliente() == numeroCliente) {
            reg.mostrarVenta();
            cout << endl;
            hayVentas = true;
        }
    }
    fclose(pVenta);
    return hayVentas;
}

void listarVentasPorClienteInteractivo() {
    ArchivoVenta archiV;
    int numeroCliente;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el numero del Cliente: ";
    cin >> numeroCliente;
    if (!archiV.listarVentasPorCliente(numeroCliente)) {
        rlutil::setColor(rlutil::RED);
        cout << "No se encontraron ventas para el cliente con ID " << numeroCliente << "." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
}

