#include <iostream>
#include <cstring>
#include <ctime>
#include "rlutil.h"
using namespace std;
#include "Artista.h"

void Artista::cargarArtista(int id){/// Funciones que permiten cargar y mostrar un artista y sus atributos.
    if(id == 0){
        rlutil::setColor(rlutil::WHITE);
        cout << "ID del artista: ";
        cin >> idArtista;
        cin.ignore();
    }else{
        idArtista = id;
    }
    cout << "Nombre y Apellido Artista: ";
    cin.ignore();
    cin.getline(nombreArtista, sizeof(nombreArtista));
    cout << "Nacionalidad Del Artista: ";
    //cin.ignore();
    cin.getline(nacionalidad, sizeof(nacionalidad));
    cout<<"Ingrese el Genero del artista: ";
    //cin.ignore();
    cin.getline(genero, sizeof(genero));
    estado = true;
}

void Artista::mostrarArtista(){
    if(estado == true){
        rlutil::setColor(rlutil::LIGHTMAGENTA);
        cout<<"---------------------------------------"<<endl;
        cout << "ID del artista: " << idArtista << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        cout << "Nombre y Apellido del artista: " << nombreArtista << endl;
        cout << "Nacionalidad del artista: " << nacionalidad << endl;
        cout << "Genero del Artista: " <<genero<<endl;
        cout<<"---------------------------------------"<<endl;
    }
}
