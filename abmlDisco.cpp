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

bool altaRegistro(){
    Disco reg;
    ArchivoDisco archivo;
    ArchivoArtista archivoArtista;
    int idDisco;
    int idArtista;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingresar ID del disco a dar de Alta: ";
    cin >> idDisco;
    int pos = archivo.buscarRegistro(idDisco, TODOS);  /// Buscamos que ese registro no esté ya agregado.
    if (pos != -1){
        rlutil::setColor(rlutil::RED);
        cout << "Ya hay un registro de disco con ese ID" << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingresar el ID del Artista: ";
    cin >> idArtista;
    Artista artista;
    if(archivoArtista.leerArtista(artista, idArtista) && artista.getEstado()){  /// 27/11/2024, ACA ESTABA EL PROBLEMA CON LA DADA DE ALTA DE DISCOS , FALTABA PONER artista.getEstado(), osea , que el artista esté ACTIVO.
        rlutil::setColor(rlutil::GREEN);
        cout << "Artista Encontrado: " << artista.getNombreArtista() << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }else{
        rlutil::setColor(rlutil::RED);
        cout << "Artista no encontrado, o Inactivo." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    reg.Cargar(idDisco,idArtista); /// Cargamos el registro con el método Cargar que esta en discos.cpp
    cout << "ID ingresado: " << reg.getIdDisco() << endl; /// Mini depuracion para mostrar qué id le pusimos. 27/11/2024
    if (archivo.grabarRegistro(reg)){
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

bool bajaRegistro(){  ///(LA B en ABML)
    Disco reg;
    ArchivoDisco archivo;
    int id;
    rlutil::setColor(rlutil::WHITE);
    cout<<"Ingresar ID del album a dar de Baja: ";
    cin>>id;
    int pos=archivo.buscarRegistro(id, ACTIVOS);
    if(pos==-1){
        rlutil::setColor(rlutil::RED);
        cout<<"No hay registros de album con ese ID"<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    reg=archivo.leerRegistro(pos);
    reg.setEstado(false);
    if(archivo.modificarRegistro(reg,pos))return true; ///Se modifica el registro.
    return false;
}

void listadoRegistros(){
    Disco reg;
    ArchivoDisco archivo;
    archivo.listarRegistros();
    pausarSistema();
}

bool modificacionRegistro(){
    Disco reg;
    ArchivoDisco archivo;
    int id;
    int nuevoStock;
    rlutil::setColor(rlutil::WHITE);
    cout<<"Ingresar el ID del registro del disco a Modificar: ";
    cin>>id;
    int pos=archivo.buscarRegistro(id, ACTIVOS);///Puede ser que se haya encontrado o no el registro.
    if(pos==-1){
        rlutil::setColor(rlutil::RED);
        cout<<"No hay registros de disco con ese ID"<<endl;
        rlutil::setColor(rlutil::RED);
        return false;
    }
    reg=archivo.leerRegistro(pos);///Se lee el registro y se lo copia en reg.
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el cambio de Stock: ";
    cin >> nuevoStock;
    reg.setStockDiscos(nuevoStock);
    if(archivo.modificarRegistro(reg,pos))return true;
    return false;
}
