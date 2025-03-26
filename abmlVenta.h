#ifndef ABMLVENTA_H
#define ABMLVENTA_H
bool altaVenta();
bool bajaVenta();             ///Funciones para abml de Ventas.
void listadoRegistrosVentas();
bool modificacionRegistroVentas();

void mostrarRecaudacionPorFecha();
void mostrarRecaudacionPorAnio();    /// Funciones para recaudación.
void mostrarRecaudacionPorMes();
void mostrarRecaudacionPorDia();

void buscarVentaPorId();                        /// Funciones para listado.
void listarVentasPorClienteInteractivo();
#endif // ABMLVENTA_H
