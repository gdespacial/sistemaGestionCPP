#ifndef ARTISTA_H
#define ARTISTA_H
class Artista{
private:
    int idArtista;
    char nombreArtista[100];
    char nacionalidad[100];
    char genero[50];
    bool estado;
public:
    void setIdArtista(int idArt){idArtista = idArt;}
    int getIdArtista(){return idArtista;}
    void setNombreArtista(const char* nuevoNombre){
    strncpy(nombreArtista, nuevoNombre, sizeof(nombreArtista) - 1);
    nombreArtista[sizeof(nombreArtista) - 1] = '\0';}
    const char* getNombreArtista(){return nombreArtista;}
    const char* getGenero(){return genero;}
    void setGenero(const char* nuevoGenero){
    strncpy(genero, nuevoGenero, sizeof(genero) - 1);
    genero[sizeof(genero) - 1] = '\0';}
    void setNacionalidad(const char* nuevaNac){
    strncpy(nacionalidad, nuevaNac, sizeof(nacionalidad) -1);
    nacionalidad[sizeof(nacionalidad) - 1] = '\0';}
    const char* getNacionalidad(){return nacionalidad;}
    void setEstado(bool e){estado = e;}
    bool getEstado(){return estado;}
    void cargarArtista(int id = 0);
    void mostrarArtista();
};
#endif // ARTISTA_H
