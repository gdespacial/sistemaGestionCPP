#include <iostream>
#include <cstring>
#include <ctime>
#include "rlutil.h"
using namespace std;
#include "DesarrolloMenues.h"
#include "Artista.h"
#include "Disco.h"
#include "ArchivoArtista.h"
#include "ArchivoDisco.h"
#include "amblArtista.h"

bool altaArtista(){  /// (LA A EN ABML)
    Artista regi;
    ArchivoArtista archiA;
    int id;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingresar el ID del artista a dar de Alta: ";
    cin >> id;
    int pos = archiA.buscarArtisas(id, ARTISTASTODOS);
    if (pos != -1){
        rlutil::setColor(rlutil::RED);
        cout << "Este numero de ID ya fue Utilizado" << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    regi.cargarArtista(id);
    rlutil::setColor(rlutil::WHITE);
    cout << "Numero de Artista : " << regi.getIdArtista() << endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    if (archiA.grabarArtista(regi)){
        rlutil::setColor(rlutil::GREEN);
        cout << "Artista grabado Exitosamente." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return true;
    }
    rlutil::setColor(rlutil::RED);
    cout << "Error al grabar el Registro." << endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    return false;
}

bool bajaArtista(){                     ///(LA B en ABML)
    Artista reg;                       /// Creamos el registro de la clase ARTISTA.
    ArchivoArtista archivo;           /// Creamos el objeto de la clase ArchivoArtista.
    int id;
    rlutil::setColor(rlutil::WHITE);
    cout<<"Ingresar ID del artista a dar de Baja: ";
    cin>>id;                                              /// Volvemos a poner un cin para saber qué registro queremos borrar.
    int pos=archivo.buscarArtisas(id, ARTISTASACTIVOS);  /// Puede ser que se haya encontrado o no el registro.
    if(pos==-1){
        rlutil::setColor(rlutil::RED);
        cout<<"No hay registros de artista con ese ID"<<endl;    /// Si no hay registros q coincidan con el cin q hicimos, no borramos nada.
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    reg=archivo.leerArtistas(pos);                 ///Se lee el registro y se lo copia en reg.
    reg.setEstado(false);                         /// Poner el estado del registro en falso.
    if (archivo.modificarArtista(reg, pos)){     /// Si se modifica correctamente el artista:
        ///24/11/2024 Ahora buscar y dar de baja lógica a los discos asociados al artista
        ArchivoDisco archivoDisco;
        Disco disco;
        int cantidadDiscos = archivoDisco.contarRegistros();      /// Cantidad total de discos
        for (int i = 0; i < cantidadDiscos; i++){
            disco = archivoDisco.leerRegistro(i);
            if (disco.getIdArtista() == id && disco.getEstado()){
                /// Si el disco pertenece al artista y está activo:
                disco.setEstado(false); /// Baja lógica del disco
                archivoDisco.modificarRegistro(disco, i);
            }
        }
        return true;
    }
    rlutil::setColor(rlutil::RED);
    cout << "Error al dar de baja al Artista." << endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    return false;
}

bool modificarArtista(){ ///(la M en ABML).
    Artista reg;
    ArchivoArtista archivo;
    int id;
    char nuevoNombre[100];
    rlutil::setColor(rlutil::WHITE);
    cout<<"Ingresar el ID del Artista: ";
    cin>>id;
    int pos=archivo.buscarArtisas(id, ARTISTASACTIVOS);///Puede ser que se haya encontrado o no el registro.
    if(pos==-1){
        rlutil::setColor(rlutil::RED);
        cout<<"No hay registros de artista con ese ID"<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    reg=archivo.leerArtistas(pos);///Se lee el registro y se lo copia en reg.
    rlutil::setColor(rlutil::GREEN);
    cout << "Artista Encontrado: " << reg.getNombreArtista()<<endl;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el nuevo nombre del Artista: ";
    cin.ignore();
    cin.getline(nuevoNombre, 100);
    reg.setNombreArtista(nuevoNombre);
    if(archivo.modificarArtista(reg,pos))return true;
    return false;
}

void listadoArtistas(){ ///(LA L EN ABML)
    Artista reg;
    ArchivoArtista archivo;
    archivo.listarArtistas();
    pausarSistema();
}
