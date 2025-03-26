#ifndef ARCHIVODISCO_H
#define ARCHIVODISCO_H
#include "Disco.h"
const bool ACTIVOS=true;  ///Necesario para abml.
const bool TODOS=false;

class ArchivoDisco{
private:
    char nombre[50];
    int tamanioRegistro;
public:
    ArchivoDisco(const char *n="discos.dat")    /// Constructor.
    {strcpy(nombre, n);
    tamanioRegistro = sizeof(Disco);}
    bool grabarRegistro(Disco reg);
    bool leerRegistro(Disco &reg, int id);
    int contarRegistros();
    bool listarRegistros();
    int buscarRegistro(int id, bool queHago);
    Disco leerRegistro(int ubicacion);
    bool modificarRegistro(Disco reg,int pos);
    bool listarDiscosPorArtista(int idArtista);
    bool buscarYMostrarRegistro(int idDisco);
};

#endif // ARCHIVODISCO_H
