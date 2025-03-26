#ifndef ARCHIVOVENTA_H
#define ARCHIVOVENTA_H
#include "Venta.h"
const bool VENTASACTIVAS=true;
const bool VENTASTODAS=false;
const bool VENTADETALLEACTIVAS=true;
const bool VENTADETALLETODAS=false;

class ArchivoVenta{
private:
    char nombreVenta[50];
    int tamReg;
public:
    ArchivoVenta(const char *nV = "ventas.dat"){
    strcpy(nombreVenta, nV);
    tamReg = sizeof(Venta);}
    bool grabarVenta(Venta regi);
    bool leerVenta(Venta &regi, int idVenta);
    int contarVentas();
    bool listarVentas();
    int buscarVentas(int id, bool keHago);
    Venta leerVentas(int ubicacion);
    bool modificarVenta(Venta regi,int pos);
    bool buscarYMostrarVenta(int idVenta);
    float calcularGastoTotal(int numeroCliente);
    bool leerVentaPorPosicion(Venta &reg, int posicion);
    bool listarVentasPorCliente(int numeroCliente);
};

class ArchivoVentaDetalle{
private:
    char nombreVentaDetalle[50];
    int tamReg;
public:
    ArchivoVentaDetalle(const char *nVD = "ventaDetalle.dat"){
    strcpy(nombreVentaDetalle, nVD);
    tamReg = sizeof(VentaDetalle);}
    bool grabarVentaDetalle(VentaDetalle detalle);
    bool leerVentaDetalle(VentaDetalle &detalle, int pos);
    int contarDetalles();
    bool listarDetallesPorVenta(int idVenta); /// Lista detalles de una venta específica
    int buscarDetalles(int idVenta, bool keHago); /// Busca un detalle específico
    bool modificarDetalle(VentaDetalle detalle, int pos);
    VentaDetalle leerDetalles(int ubicacion);
};
#endif // ARCHIVOVENTA_H
