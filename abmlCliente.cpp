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

bool altaCliente(){
    Cliente regi;
    ArchivoCliente archiC;
    int number;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingresar numero de cliente a dar de Alta: ";
    cin >> number;
    int pos = archiC.buscarRegistroCliente(number, CLIENTESTODOS);
    if (pos != -1){
        rlutil::setColor(rlutil::RED);
        cout << "Ya hay un registro de cliente con ese Numero" << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    regi.cargarCliente(number);
    rlutil::setColor(rlutil::WHITE);
    cout << "Numero de Cliente Ingresado: " << regi.getNumeroCliente() << endl;
    if (archiC.grabarRegistroCliente(regi)){
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

bool bajaCliente(){
    Cliente regi;
    ArchivoCliente archiC;
    int number;
    rlutil::setColor(rlutil::WHITE);
    cout<<"Ingresar el numero del cliente a dar de Baja: ";
    cin>>number;
    int pos=archiC.buscarRegistroCliente(number, CLIENTESACTIVOS);
    ///Puede ser que se haya encontrado o no el registro.
    if(pos==-1){
        rlutil::setColor(rlutil::RED);
        cout<<"No hay registros de clientes con ese Numero"<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    regi=archiC.leerRegistroCliente(pos);                  ///Se lee el registro y se lo copia en reg.
    regi.setEstado(false);
    if(archiC.modificarRegistroCliente(regi,pos)){
        /// 2/12/2024 MODIFICACION PARA QUE CUANDO BORRO UN CLIENTE SE BORREN TAMBIEN SUS VENTAS.
        ArchivoVenta archivoVenta;
        Venta venta;
        int cantidadVentas = archivoVenta.contarVentas();   /// Cantidad total de ventas.
        for (int i = 0; i < cantidadVentas; i++){
            venta = archivoVenta.leerVentas(i);
            if (venta.getNumeroCliente() == number && venta.getEstado()){    /// LA CLAVE ESTABA EN .getEstado();
                /// Si La venta pertenece al cliente y está activa:
                venta.setEstado(false);         /// Baja lógica de la venta
                archivoVenta.modificarVenta(venta, i);
            }
        }
        return true;
    }
    rlutil::setColor(rlutil::RED);
    cout << "Error al dar de baja el cliente" << endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    return false;
}

void listadoRegistrosClientes(){
    Cliente regi;
    ArchivoCliente archiC;
    archiC.listarRegistrosClientes();
    pausarSistema();
}

bool modificacionRegistroClientes(){///(la M en ABML).
    Cliente reg;
    ArchivoCliente archivo;
    int numeroCliente;
    char nuevoEmail[100];
    //int nuevasComprasRealizadas;
    rlutil::setColor(rlutil::WHITE);
    cout<<"Ingresar el numero del Cliente: ";
    cin>>numeroCliente;
    int pos=archivo.buscarRegistroCliente(numeroCliente, CLIENTESACTIVOS);///Puede ser que se haya encontrado o no el registro.
    if(pos==-1){
        rlutil::setColor(rlutil::RED);
        cout<<"No hay registros de clientes con ese Numero"<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    reg=archivo.leerRegistroCliente(pos);///Se lee el registro y se lo copia en reg.
    rlutil::setColor(rlutil::GREEN);
    cout << "Cliente Encontrado: " << reg.getNombre()<<endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    cout << "Ingrese el nuevo email del Cliente: ";
    cin.ignore();
    cin.getline(nuevoEmail, 100);
    reg.setEmail(nuevoEmail);
    if(archivo.modificarRegistroCliente(reg,pos))return true;
    return false;
}
