#ifndef ARCHIVOCLIENTE_H
#define ARCHIVOCLIENTE_H
#include "Cliente.h"
const bool CLIENTESACTIVOS=true;
const bool CLIENTESTODOS=false;

class ArchivoCliente{
private:
    char nombreCliente[50];
    int tamReg;
public:
    ArchivoCliente(const char *nC="clientes.dat"){
    strcpy(nombreCliente, nC);
    tamReg = sizeof(Cliente);}
    bool grabarRegistroCliente(Cliente regi);
    bool leerRegistroCliente(Cliente &regi, int numeroCliente);
    int contarRegistrosClientes();
    bool listarRegistrosClientes();
    int buscarRegistroCliente(int number, bool keHago);
    Cliente leerRegistroCliente(int ubicacion);
    bool modificarRegistroCliente(Cliente regi,int pos);
    bool buscarYMostrarCliente(int numeroCliente);
    bool modificarComprasCliente(int numeroCliente, int nuevasCompras);
};
#endif // ARCHIVOCLIENTE_H
