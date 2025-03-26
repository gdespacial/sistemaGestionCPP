#include <iostream>
#include <cstring>
#include <ctime>
#include "rlutil.h"
using namespace std;
#include "Artista.h"
#include "ArchivoArtista.h"

bool ArchivoArtista::grabarArtista(Artista reg){
    FILE *pArtista; // Puntero file.
    pArtista = fopen(nombre, "ab"); // Abrir archivo.
    if(pArtista == NULL){
    rlutil::setColor(rlutil::RED);
    cout << "Error" << endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    return false;}
    int escribio = fwrite(&reg, tamanioRegistro, 1, pArtista); // Escribir registro.
    fclose(pArtista); // Cerrar archivo.
    return escribio;
    }

bool ArchivoArtista::leerArtista(Artista &reg, int idArtista){
    FILE *pArtista;
    pArtista = fopen(nombre, "rb");
    if (pArtista == NULL) {
    return false;}
    while (fread(&reg, tamanioRegistro, 1, pArtista) == 1) {
    if (reg.getIdArtista() == idArtista) {
    fclose(pArtista);
    return true;}}
    fclose(pArtista);
    return false;
    }

int ArchivoArtista::contarArtistas(){
    FILE *pArtista;
    Artista reg;
    pArtista=fopen(nombre, "rb");
    if(pArtista==NULL){
    rlutil::setColor(rlutil::RED);
    cout<<"No se pudo abrir el Archivo "<<endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    return -1;}
    fseek(pArtista,0, 2);//Ubicar el puntero al final del archivo
    int cantByte=ftell(pArtista);
    fclose(pArtista);
    return cantByte/tamanioRegistro;
}

bool ArchivoArtista::listarArtistas(){
    FILE *pArtista;
    Artista reg;
    pArtista=fopen(nombre, "rb");
    if(pArtista==NULL){
        rlutil::setColor(rlutil::WHITE);
        cout<<"No se pudo abrir el Archivo"<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;}
    while(fread(&reg,tamanioRegistro,1,pArtista)==1){
    reg.mostrarArtista();
    cout<<endl;}
    fclose(pArtista);
    return true;
    }

int ArchivoArtista::buscarArtisas(int id, bool queHago){
    FILE *pArtista;
    Artista reg;
    int pos=0;
    pArtista=fopen(nombre, "rb");
    if(pArtista==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return -2;
    }
    if(queHago==true){
        while(fread(&reg,tamanioRegistro,1,pArtista)==1){
            if(reg.getIdArtista()==id &&reg.getEstado()){
                fclose(pArtista);
                return pos;
            }
            pos++;
        }
        fclose(pArtista);
        return -1;
    }else{
        while(fread(&reg,tamanioRegistro,1,pArtista)==1){
            if(reg.getIdArtista()==id){
                fclose(pArtista);
                return pos;
            }
            pos++;
        }
        fclose(pArtista);
        return -1;
    }
}

bool ArchivoArtista::buscarYMostrarArtistaPorId(int idArtista){
    FILE *pArtista;
    Artista reg;
    pArtista = fopen(nombre, "rb"); /// Abrir el archivo en modo lectura.
    if (pArtista == NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    while (fread(&reg, tamanioRegistro, 1, pArtista) == 1){
        if (reg.getIdArtista() == idArtista && reg.getEstado()){  /// Verificar si el artista existe y está activo.
            reg.mostrarArtista(); /// Llamar al método que muestra los datos del artista.
            fclose(pArtista);
            return true; /// Se encontró y se mostró el artista.
        }
    }
    fclose(pArtista);
    rlutil::setColor(rlutil::RED);
    cout << "Artista no Encontrado." << endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    return false;
}

Artista ArchivoArtista::leerArtistas(int ubicacion){
    FILE *pArtista;
    Artista reg;
    reg.setIdArtista(-1);
    pArtista=fopen(nombre, "rb");
    if(pArtista==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return reg;
    }
    int cuanto=ubicacion*tamanioRegistro;
    int desde_donde=0;
    fseek(pArtista,cuanto, desde_donde);
    fread(&reg, tamanioRegistro,1, pArtista);
    fclose(pArtista);
    return reg;
}

bool ArchivoArtista::modificarArtista(Artista reg,int pos){
    FILE *pArtista;
    pArtista=fopen(nombre, "rb+");
    if(pArtista==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    fseek(pArtista,pos*tamanioRegistro, 0);
    bool escribio=fwrite(&reg, tamanioRegistro,1, pArtista);
    fclose(pArtista);
    return escribio;
}

void buscarArtistaPorId(){
    ArchivoArtista archivoArtista;
    int idBuscado;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el ID del artista a buscar: ";
    cin >> idBuscado;
    if (!archivoArtista.buscarYMostrarArtistaPorId(idBuscado)){
        rlutil::setColor(rlutil::RED);
        cout << "No se encontro el artista con el ID ingresado." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
}
