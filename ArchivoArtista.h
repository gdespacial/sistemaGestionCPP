#ifndef ARCHIVOARTISTA_H
#define ARCHIVOARTISTA_H
#include "Artista.h"
const bool ARTISTASACTIVOS=true;
const bool ARTISTASTODOS=false;

class ArchivoArtista{
private:
    char nombre[50];
    int tamanioRegistro;
public:
    ArchivoArtista(const char *n="artistas.dat"){ /// Constructor.
    strcpy(nombre, n);
    tamanioRegistro = sizeof(Artista);}  /// Esto sirve para no tener que hacer sizeof todo el tiempo.
    bool grabarArtista(Artista reg); /// Método para grabar registro.
    bool leerArtista(Artista &reg, int idArtista); /// Pasar como referencia y no por valor el parámetro.
    int contarArtistas(); /// Método para contar registros. acá voy a usar las funciones fseek y ftell vistas en clase.
    bool listarArtistas(); /// Método para listar todos los registros.
    int buscarArtisas(int id, bool queHago); /// Método que me va servir para poder hacer una baja logica.
    Artista leerArtistas(int ubicacion); /// Método necesario para la baja logica.
    bool modificarArtista(Artista reg,int pos); /// Modificar registro.
    bool buscarYMostrarArtistaPorId(int idArtista); /// Esta función me va a servir para hacer consultas.
};
#endif // ARCHIVOARTISTA_H
