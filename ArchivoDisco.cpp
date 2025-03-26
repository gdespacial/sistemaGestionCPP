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

bool ArchivoDisco::grabarRegistro(Disco reg){
    FILE *pDisco; /// Puntero file.
    pDisco = fopen(nombre, "ab");
    if(pDisco == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "Error" << endl; /// Nunca omitir esta línea de código.
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    int escribio = fwrite(&reg, tamanioRegistro, 1, pDisco); /// Funcionalidad para que escriba registros.
    fclose(pDisco);
    return escribio;
}

bool ArchivoDisco::leerRegistro(Disco &reg, int id){
    FILE *pDisco = fopen(nombre, "rb");
    if (pDisco == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "No se pudo abrir el archivo de discos para leer." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    while (fread(&reg, sizeof(Disco), 1, pDisco) == 1){
        if (reg.getIdDisco() == id) {  /// verificar la coincidencia de los ids.
            fclose(pDisco);
            return true;
        }
    }
    fclose(pDisco);
    return false;
}

int ArchivoDisco::contarRegistros(){
    FILE *pDisco;
    Disco reg;
    pDisco=fopen(nombre, "rb");
    if(pDisco==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo"<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return -1;
    }
    fseek(pDisco,0, 2);
    int cantByte=ftell(pDisco);
    fclose(pDisco);
    return cantByte/tamanioRegistro;
}

bool ArchivoDisco::listarRegistros(){
    FILE *pDisco;
    Disco reg;
    pDisco=fopen(nombre, "rb");
    if(pDisco==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    while(fread(&reg,tamanioRegistro,1,pDisco)==1){
        reg.Mostrar();
        cout<<endl;
    }
    fclose(pDisco);
    return true;
}

int ArchivoDisco::buscarRegistro(int id, bool queHago){
    FILE *pDisco;
    Disco reg;
    int pos=0;
    pDisco=fopen(nombre, "rb");
    if(pDisco==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return -2;
    }
    if(queHago==true){
        while(fread(&reg,tamanioRegistro,1,pDisco)==1){
            if(reg.getIdDisco()==id &&reg.getEstado()){
                fclose(pDisco);
                return pos;
            }
            pos++;
        }
        fclose(pDisco);
        return -1;
    }else{
        while(fread(&reg,tamanioRegistro,1,pDisco)==1){
            if(reg.getIdDisco()==id){
                fclose(pDisco);
                return pos;
            }
            pos++;
        }
        fclose(pDisco);
        return -1;
    }
}

Disco ArchivoDisco::leerRegistro(int ubicacion){
    FILE *pDisco;
    Disco reg;
    reg.setIdDisco(-1);
    pDisco=fopen(nombre, "rb");
    if(pDisco==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return reg;
    }
    int cuanto=ubicacion*tamanioRegistro;
    int desde_donde=0;
    fseek(pDisco,cuanto, desde_donde);
    fread(&reg, tamanioRegistro,1, pDisco);
    fclose(pDisco);
    return reg;
}

bool ArchivoDisco::modificarRegistro(Disco reg,int pos){
    FILE *pDisco;
    pDisco=fopen(nombre, "rb+");
    if(pDisco==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    fseek(pDisco,pos*tamanioRegistro, 0);
    bool escribio=fwrite(&reg, tamanioRegistro,1, pDisco);
    fclose(pDisco);
    return escribio;
}

bool ArchivoDisco::listarDiscosPorArtista(int idArtista) {
    FILE *pDisco;
    Disco reg;
    ArchivoArtista archivoArtista;
    Artista artista;
    pDisco = fopen(nombre, "rb");
    if (pDisco == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "No se pudo abrir el Archivo " << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    bool hayDiscos = false;
    if (archivoArtista.leerArtista(artista, idArtista) && artista.getEstado()){  ///27/11/2024 MODIFICACION PARA QUE NO ENCUENTRE ARTISTAS QUE FUERON BORRADOS
    rlutil::setColor(rlutil::GREEN);
    cout << "Artista: " << artista.getNombreArtista() << endl; /// Mostrar nombre del artista
    rlutil::setColor(rlutil::LIGHTBLUE);
    }
    else{
        rlutil::setColor(rlutil::RED);
        cout <<"No se encontro al Artista" << endl;  /// DEPURACION / MENSAJE ACLARATORIO. MODIFICADO EL 27/11/2024
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
    cout << endl;
    while (fread(&reg, tamanioRegistro, 1, pDisco) == 1) {
        if (reg.getIdArtista() == idArtista) {
            reg.Mostrar();
            cout << endl;
            hayDiscos = true;
        }
    }
    fclose(pDisco);
    return hayDiscos;
}

void listarDiscosPorArtistaInteractivo(){
    ArchivoDisco archiD;
    int idArtista;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el ID del Artista: ";
    cin >> idArtista;
    rlutil::setColor(rlutil::LIGHTBLUE);
    if (!archiD.listarDiscosPorArtista(idArtista)){
        rlutil::setColor(rlutil::RED);
        cout << "No se encontraron discos para el artista con ID " << idArtista << "." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
}

bool ArchivoDisco::buscarYMostrarRegistro(int idDisco){
    FILE *pDisco;
    Disco reg;
    pDisco = fopen(nombre, "rb");
    if (pDisco == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "No se pudo abrir el Archivo" << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
   while (fread(&reg, tamanioRegistro, 1, pDisco) == 1) {
        if (reg.getIdDisco() == idDisco && reg.getEstado()){ /// Verificar si el artista existe y está activo.
            reg.Mostrar();  /// Llamar al método que muestra los datos del artista.
            fclose(pDisco);
            return true;
        }
    }
    fclose(pDisco);
    rlutil::setColor(rlutil::RED);
    cout << "Disco no Encontrado" << endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    return false;
}

void buscarDiscoPorId(){
  ArchivoDisco archivoDisco;
    int idBuscado;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el ID del disco a Buscar: ";
    cin >> idBuscado;
    if (!archivoDisco.buscarYMostrarRegistro(idBuscado)){
        rlutil::setColor(rlutil::RED);
        cout << "No se encontro el artista con el ID Ingresado" << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
}
