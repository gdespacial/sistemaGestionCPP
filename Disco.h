#ifndef DISCO_H
#define DISCO_H
class Disco{
private:
    int idDisco;
    int idArtista;
    char titulo[100];
    char genero[50];
    int precio;
    int stockDiscos;
    bool estado;
public:
    Disco() {
        idDisco = 0;
        idArtista = 0;
        precio = 0.0;
        stockDiscos = 0;
        estado = false;
        strcpy(titulo, "");
        strcpy(genero, "");
    }
    int getIdDisco(){return idDisco;}
    void setIdDisco(int i){idDisco = i;}
    int getIdArtista(){return idArtista;}
    void setIdArtista(int idArt){idArtista = idArt;}
    const char* getTitulo(){return titulo;}
    const char* getGenero(){return genero;}
    void setGenero(const char* nuevoGenero){
    strncpy(genero, nuevoGenero, sizeof(genero) - 1);
    genero[sizeof(genero) - 1] = '\0';}
    int getPrecio(){return precio;}
    void setPrecio(int p){precio = p;}
    bool getEstado(){return estado;}
    void setEstado(bool e){estado = e;}
    void setStockDiscos(int s){stockDiscos = s;}
    int getStockDiscos(){return stockDiscos;}
    void Cargar(int id, int idArtista);
    void Mostrar();
    };
#endif // DISCO_H
