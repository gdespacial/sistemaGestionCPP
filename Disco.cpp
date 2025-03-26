#include <iostream>
#include <cstring>
#include <cstdio>
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

void Disco::Cargar(int id, int idArtista){
    this->idArtista = idArtista;
    rlutil::setColor(rlutil::WHITE);
    cout << "ID del Artista recibido: " << this->idArtista << endl;  /// Mini depuracion.
        if (id == 0) {
            cout << "Id del Disco/Album: ";
            cin >> idDisco;
            cin.ignore();
        }else{
            idDisco = id;
        }

    cout << "Titulo del Disco: ";
    cin.ignore();
    cin.getline(titulo, sizeof(titulo)); /// Usar getline.
    cout << "Genero musical: ";
    cin.getline(genero, sizeof(genero));
    cout << "Precio: $";
    cin >> precio;
    cout << "Stock disponible: ";
    cin >> stockDiscos;
    estado = true;
}

void Disco::Mostrar(){
    if(estado==true){
        Artista artista;
        ArchivoArtista archivoArtista;
        rlutil::setColor(rlutil::LIGHTMAGENTA);
        cout<<"-----------------------------------"<<endl;
        cout << "Id del Disco/Album: "<< idDisco << endl;
        cout << "Id del Artista: "<< idArtista << endl;

        int pos = archivoArtista.buscarArtisas(idArtista,ARTISTASTODOS);
        if (pos != -1 && archivoArtista.leerArtista(artista, idArtista)&& artista.getEstado()){  /// 10/12/2024 NUEVO ERROR CORREGIDO
            rlutil::setColor(rlutil::GREEN);
            cout << "Nombre del Artista: " << artista.getNombreArtista() << endl;

            rlutil::setColor(rlutil::LIGHTBLUE);
        }
         rlutil::setColor(rlutil::LIGHTBLUE);
        cout << "Titulo del disco: "<< titulo << endl;
        cout << "Genero Musical: " << genero << endl;
        cout << "Precio: $ " << precio << endl;
        cout << "Stock Disponible: " <<stockDiscos<<endl;
        cout<<"-----------------------------------"<<endl;
    }
}
