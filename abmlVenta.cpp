#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include "rlutil.h"
using namespace std;
#include "DesarrolloMenues.h"
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

double calcularRecaudacionPorFecha(Fecha& fechaInicio, Fecha& fechaFin);
double calcularRecaudacionPorAnio(int anio);
double calcularRecaudacionPorMes(int mes, int anio);
double calcularRecaudacionPorDia(int mes, int anio, int dia);

bool altaVenta(){         /// Alta.
    Venta reg;
    ArchivoVentaDetalle archivoDetalle;
    ArchivoVenta archivo;
    ArchivoCliente archivoCliente;
    int idVenta;
    int numeroCliente;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingresar ID de la venta a dar de Alta: ";
    cin >> idVenta;
    int pos = archivo.buscarVentas(idVenta, VENTASTODAS);
    if (pos != -1) {
    rlutil::setColor(rlutil::RED);
        cout << "Ya hay un registro de venta con ese ID" << endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingresar el numero de cliente: ";
    cin >> numeroCliente;
    Cliente cliente;
    if(archivoCliente.leerRegistroCliente(cliente, numeroCliente) && cliente.getEstado()){/// 02/12/2024 MODIFICACION QUE CORRIGE ERRORES A LA HORA DE ENCONTRAR CLIENTES.
        rlutil::setColor(rlutil::GREEN);
        cout << "Cliente Encontrado: " << cliente.getNombre() << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }else{
        rlutil::setColor(rlutil::RED);
        cout << "Cliente no encontrado." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    reg.cargarVenta(idVenta,numeroCliente);
    reg.calcularMontoTotal();  /// 11/12 / 2024
    int montoTotal = reg.calcularMontoTotal();
    if(montoTotal <= 0)
    {
         rlutil::setColor(rlutil::RED);
        cout << "Error, volver a intentar. No se pudo agregar la venta" << endl;
        return false;
    }
    rlutil::setColor(rlutil::WHITE);
    cout << "ID ingresado: " << reg.getIdVenta() << endl; /// Depuracion.
    if (archivo.grabarVenta(reg)){
        rlutil::setColor(rlutil::GREEN);
        cout << "Registro grabado exitosamente." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return true;
    }
    rlutil::setColor(rlutil::RED);
    cout << "Error al grabar el registro." << endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    return false;
}

bool bajaVenta(){                                             /// Baja Lógica.
    Venta reg;                                               /// Crear Registro.
    ArchivoVenta archivo;                                   /// Crear el objeto de la clase ArchivoVenta.
    int id;
    rlutil::setColor(rlutil::WHITE);
    cout<<"Ingresar ID de la venta a dar de Baja: ";
    cin>>id;
    int pos=archivo.buscarVentas(id, VENTASACTIVAS);        ///Buscar el registro.
    if(pos==-1){
        rlutil::setColor(rlutil::RED);
        cout<<"No hay registros de ventas con ese ID"<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    reg=archivo.leerVentas(pos);                            ///Se lee el registro y se lo copia en reg.
    reg.setEstado(false);                                   /// Poner el estado en falso.
    if(archivo.modificarVenta(reg,pos))return true;         /// Modificar registro.
    return false;
}

bool modificacionRegistroVentas(){                      ///Modificar.
    Venta reg;
    ArchivoVenta archivo;
    int idVenta;
    Fecha nuevaFecha;
    rlutil::setColor(rlutil::WHITE);
    cout<<"Ingresar el ID de la Venta: ";
    cin>>idVenta;
    int pos=archivo.buscarVentas(idVenta, VENTASACTIVAS);   ///Puede ser que se haya encontrado o no el registro.
    if(pos==-1){
        rlutil::setColor(rlutil::RED);
        cout<<"No hay registros de ventas con ese Numero"<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    reg=archivo.leerVentas(pos);        ///Se lee el registro y se lo copia en reg.
    rlutil::setColor(rlutil::GREEN);
    cout << "Venta Encontrada: " << reg.getIdVenta()<<endl;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese la nueva fecha de la Venta: "<<endl;
    cin.ignore();
    nuevaFecha.cargarFecha();
    reg.setFecha(nuevaFecha);
    if(archivo.modificarVenta(reg,pos))return true;
    return false;
}

void listadoRegistrosVentas(){                    ///Listar.
    Venta reg;
    ArchivoVenta archivo;
    archivo.listarVentas();
    pausarSistema();
}

double calcularRecaudacionPorFecha(Fecha& fechaInicio, Fecha& fechaFin){ /// DEPURACIONES COMENTADAS.
    double totalRecaudacion = 0.0;
    ArchivoVenta archivoVenta;
    Venta venta;
    ///2/12/2024 Obtener la cantidad total de registros en el archivo.
    int totalVentas = archivoVenta.contarVentas();
    for (int pos = 0; pos < totalVentas; ++pos){ /// Iteramos sobre cada posición en el archivo
        if (archivoVenta.leerVentaPorPosicion(venta, pos)){ /// Nueva función para leer por posición
            Fecha fechaVenta = venta.getFecha();
            if (fechaVenta >= fechaInicio && fechaVenta <= fechaFin && venta.getEstado()){ /// 03/02/2024 LE AGREGAMOS UN GET ESTADO PARA QUE SOLO DETECTE LAS VENTAS ACTIVAS.
                totalRecaudacion += venta.getMontoTotal();
            }
        }
    }

    return totalRecaudacion;
}

void mostrarRecaudacionPorFecha(){
    Fecha fechaInicio, fechaFin;
    cout << "Ingrese la fecha de inicio (ejemplo: 01/01/2024): "<<endl;
    rlutil::setColor(rlutil::WHITE);
    fechaInicio.cargarFecha();                                        /// Pedir al usuario el rango de Fechas.
    rlutil::setColor(rlutil::LIGHTBLUE);
    cout << "Ingrese la fecha de fin (ejemplo: 31/12/2024): "<<endl;
    rlutil::setColor(rlutil::WHITE);
    fechaFin.cargarFecha();
    if (fechaInicio<=fechaFin){
    double total = calcularRecaudacionPorFecha(fechaInicio, fechaFin); /// Calcular la recaudación en el rango de fechas
    rlutil::setColor(rlutil::GREEN);
    cout << "La recaudacion total desde:  "<<endl;
    fechaInicio.mostrarFecha();
    cout << " hasta "<<endl; /// Mostrar resultado.
    fechaFin.mostrarFecha();
    cout << " es: $" << total <<endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    }else{
        rlutil::setColor(rlutil::RED);
        cout<<"La fecha de fin es menor a la fecha de inicio"<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return;
    }

}

int obtenerAnioActual(){
    time_t t = time(nullptr);    /// 03/12/2024 FUNCION EXTRA PARA RECAUDACION ANUAL.
    tm* ahora = localtime(&t);
    return 1900 + ahora->tm_year;
}

double calcularRecaudacionPorAnio(int anio){
    /// Validar que el año esté entre 2020 y el año actual
    int anioActual = obtenerAnioActual();
    if (anio < 2020 || anio > anioActual){
        rlutil::setColor(rlutil::RED);
        cout << "El anio ingresado no es valido. Debe estar entre 2020 y " << anioActual << "." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return 0.0;
    }
    double totalRecaudacionAnio = 0.0;
    ArchivoVenta archivoVenta;
    Venta venta;
    int totalVentas = archivoVenta.contarVentas();
    for (int i = 0; i < totalVentas; i++){ /// Usar índices desde 0..?
        if (archivoVenta.leerVentaPorPosicion(venta, i)){ /// Leer venta por posición
            Fecha fechaVenta = venta.getFecha();
            int anioVenta = fechaVenta.getAnio();
            if (anioVenta == anio && venta.getEstado()){ /// 03/02/2024 LE AGREGAMOS UN GET ESTADO PARA QUE SOLO DETECTE LAS VENTAS ACTIVAS.
                totalRecaudacionAnio += venta.getMontoTotal();
            }
        }else {
            rlutil::setColor(rlutil::RED);
            cout << "Error al leer el registro de venta en la posición " << i << endl;
            rlutil::setColor(rlutil::LIGHTBLUE);
        }
    }
    return totalRecaudacionAnio;
}

void mostrarRecaudacionPorAnio(){
    int anio;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el anio deseado (minimo 2020): ";
    cin >> anio;
    double total = calcularRecaudacionPorAnio(anio);
    if (total > 0){
        rlutil::setColor(rlutil::GREEN);
        cout << "La recaudacion total del anio " << anio << " es: $" << total << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }else{
        rlutil::setColor(rlutil::RED);
        cout << "No se encontro recaudacion para el anio " << anio << "." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
}


double calcularRecaudacionPorMes(int mes, int anio){ /// 03/12/2024 Función para calcular la recaudación por mes
    if (mes < 1 || mes > 12){  /// Validar el rango del mes
        rlutil::setColor(rlutil::RED);
        cout << "El mes ingresado no es valido. Debe estar entre 1 y 12." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return 0.0;
    }
    int anioActual = obtenerAnioActual();  /// Validar el año (2020 como mínimo y no mayor al año actual)
    if (anio < 2020 || anio > anioActual){
        rlutil::setColor(rlutil::RED);
        cout << "El anio ingresado no es valido. Debe estar entre 2020 y " << anioActual << "." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return 0.0;
    }
    double totalRecaudacionMes = 0.0;
    ArchivoVenta archivoVenta;
    Venta venta;
    int totalVentas = archivoVenta.contarVentas(); /// Contar los registros de ventas en el archivo.
    for (int i = 0; i < totalVentas; i++){ /// Usar índices base 0
        if (archivoVenta.leerVentaPorPosicion(venta, i)){ /// Leer venta por posición
            Fecha fechaVenta = venta.getFecha();
            int mesVenta = fechaVenta.getMes();
            int anioVenta = fechaVenta.getAnio();
            if (anioVenta == anio && mesVenta == mes && venta.getEstado()) { /// Verificar si el año y mes coinciden Y SI LA VENTA ESTA ACTIVA.
                totalRecaudacionMes += venta.getMontoTotal();
            }
        }else{
            rlutil::setColor(rlutil::RED);
            cout << "Error al leer el registro de venta en la posición " << i << endl;
            rlutil::setColor(rlutil::LIGHTBLUE);
        }
    }
    return totalRecaudacionMes;
}

void mostrarRecaudacionPorMes() { /// 03/12/2024 ACTUALIZACION: Función para mostrar la recaudación por mes
    int anio, mes;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el anio deseado (minimo 2020): ";
    cin >> anio;
    cout << "Ingrese el mes del anio (entre 1 y 12): ";
    cin >> mes;
    if (mes < 1 || mes > 12){  /// Validar el rango de meses antes de continuar
        rlutil::setColor(rlutil::RED);
        cout << "El mes ingresado no es valido. Intente nuevamente." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return;
    }
    double totalMes = calcularRecaudacionPorMes(mes, anio); /// Calcular recaudación para el mes y año especificado
    if (totalMes > 0){
        rlutil::setColor(rlutil::GREEN);
        cout << "La recaudacion total del mes " << mes << " del anio " << anio << " es: $" << totalMes << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }else{
        rlutil::setColor(rlutil::RED);
        cout << "No se encontro recaudacion para el mes " << mes << " del anio " << anio << "." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
}


double calcularRecaudacionPorDia(int dia, int mes, int anio){
    if (mes < 1 || mes > 12){  /// Validar el mes y el anio primero
        rlutil::setColor(rlutil::RED);
        cout << "El mes ingresado no es valido. Debe estar entre 1 y 12." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return 0.0;
    }
    int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)){
        diasEnMes[1] = 29;
    } /// Ajustar febrero para años bisiestos
    if (dia < 1 || dia > diasEnMes[mes - 1]){  /// Validar el día en el mes
        rlutil::setColor(rlutil::RED);
        cout << "El dia ingresado no es valido para el mes " << mes << " del anio " << anio << "." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return 0.0;
    }
    int anioActual = obtenerAnioActual(); /// Validar el año (mínimo 2020 y no mayor al actual)
    if (anio < 2020 || anio > anioActual){
        rlutil::setColor(rlutil::RED);
        cout << "El anio ingresado no es valido. Debe estar entre 2020 y " << anioActual << "." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return 0.0;
    }
    double totalRecaudacionDia = 0.0;
    ArchivoVenta archivoVenta;
    Venta venta;
    int totalVentas = archivoVenta.contarVentas(); /// Contar los registros de ventas en el archivo.
    for (int i = 0; i < totalVentas; i++){ /// Usar índices base 0
        if (archivoVenta.leerVentaPorPosicion(venta, i)){ /// Leer venta por posición
            Fecha fechaVenta = venta.getFecha();
            if (fechaVenta.getAnio() == anio && fechaVenta.getMes() == mes && fechaVenta.getDia() == dia && venta.getEstado()){  /// 3/12/2024 solo las ventas que estén activas.
                totalRecaudacionDia += venta.getMontoTotal();
            }
        }else{
            rlutil::setColor(rlutil::RED);
            cout << "Error al leer el registro de venta en la posición " << i << endl;
            rlutil::setColor(rlutil::LIGHTBLUE);
        }
    }
    return totalRecaudacionDia;
}

void mostrarRecaudacionPorDia(){
    int anio, mes, dia;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el anio deseado (minimo 2020): ";
    cin >> anio;
    cout << "Ingrese el mes del anio (entre 1 y 12): ";
    cin >> mes;
    cout << "Ingrese el dia del mes: ";
    cin >> dia;
    int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};/// Validar el día y mostrar error si no es válido
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)){
        diasEnMes[1] = 29; /// Ajustar febrero para años bisiestos
    }
    if (dia < 1 || dia > diasEnMes[mes - 1]){
        rlutil::setColor(rlutil::RED);
        cout << "El dia ingresado no es valido. Intente nuevamente." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return;
    }
    double totalDia = calcularRecaudacionPorDia(dia, mes, anio); /// Calcular recaudación para el día especificado
    if (totalDia > 0){
        rlutil::setColor(rlutil::GREEN);
        cout << "La recaudacion total del dia " << dia << " del mes " << mes << " del anio " << anio << " es: $" << totalDia << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }else{
        rlutil::setColor(rlutil::RED);
        cout << "No se encontro recaudacion para el dia " << dia << " del mes " << mes << " del anio " << anio << "." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
}
