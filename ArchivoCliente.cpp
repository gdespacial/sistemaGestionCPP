#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;
#include "Disco.h"
#include "Cliente.h"
#include "Venta.h"
#include "ArchivoDisco.h"
#include "ArchivoCliente.h"
#include "ArchivoVenta.h"
#include "abmlDisco.h"
#include "abmlCliente.h"
#include "abmlVenta.h"

bool ArchivoCliente::grabarRegistroCliente(Cliente regi){
    FILE *pCliente; /// Puntero file.
    pCliente = fopen(nombreCliente, "ab"); /// abrir archivo.
    if(pCliente == NULL){
        rlutil::setColor(rlutil::RED);
        cout << "Error" << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    int escribio = fwrite(&regi, tamReg, 1, pCliente);
    fclose(pCliente);
    return escribio;
}

bool ArchivoCliente::leerRegistroCliente(Cliente &regi, int numeroCliente){
    FILE *pCliente = fopen(nombreCliente, "rb");
    if (pCliente == NULL) {
        rlutil::setColor(rlutil::RED);
        cout << "No se pudo abrir el archivo de clientes para leer. " << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    while (fread(&regi, sizeof(Cliente), 1, pCliente) == 1){
        if (regi.getNumeroCliente() == numeroCliente){  // verificar la coincidencia de los numeros de clientes.
            fclose(pCliente);
            return true;
        }
    }
    fclose(pCliente);
    return false;
}

int ArchivoCliente::contarRegistrosClientes(){
    FILE *pCliente;
    Cliente regi;
    pCliente=fopen(nombreCliente, "rb");
    if(pCliente==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return -1;
    }
    fseek(pCliente,0, 2);
    int cantidadByte=ftell(pCliente);
    fclose(pCliente);
    return cantidadByte/tamReg;
}

bool ArchivoCliente::listarRegistrosClientes(){
    FILE *pCliente;
    Cliente regi;
    pCliente=fopen(nombreCliente, "rb");
    if(pCliente==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    while(fread(&regi,tamReg,1,pCliente)==1){   /// Este while me permite listar todos los registros.
        regi.mostrarCliente();
        cout<<endl;
    }
    fclose(pCliente);
    return true;
}

int ArchivoCliente::buscarRegistroCliente(int number, bool keHago){  /// HECHA.
    FILE *pCliente;
    Cliente regi;
    int pos=0;
    pCliente=fopen(nombreCliente, "rb");
    if(pCliente==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return -2;
    }
    if(keHago==true){
        while(fread(&regi,tamReg,1,pCliente)==1){
            if(regi.getNumeroCliente()==number &&regi.getEstado()){
                fclose(pCliente);
                return pos;
            }pos++;
        }
        fclose(pCliente);
        return -1;
    }else{
        while(fread(&regi,tamReg,1,pCliente)==1){
            if(regi.getNumeroCliente()==number){
                fclose(pCliente);
                return pos;
            }
            pos++;
        }
        fclose(pCliente);
        return -1;
    }
}

Cliente ArchivoCliente::leerRegistroCliente(int ubicacion){
    FILE *pCliente;
    Cliente reg;
    reg.setNumeroCliente(-1);
    pCliente=fopen(nombreCliente, "rb");
    if(pCliente==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return reg;
    }
    int cuanto=ubicacion*tamReg;
    int desde_donde=0;
    fseek(pCliente,cuanto, desde_donde);
    fread(&reg, tamReg,1, pCliente);
    fclose(pCliente);
    return reg;
}

bool ArchivoCliente::modificarRegistroCliente(Cliente reg,int pos){
    FILE *pCliente;
    pCliente=fopen(nombreCliente, "rb+");
    if(pCliente==NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    fseek(pCliente,pos*tamReg, 0);
    bool escribio=fwrite(&reg, tamReg,1, pCliente);
    fclose(pCliente);
    return escribio;
 }

bool ArchivoCliente::modificarComprasCliente(int numeroCliente, int nuevasCompras) {
    FILE *pCliente;
    pCliente = fopen(nombreCliente, "rb+");
    if (pCliente == NULL){
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
    Cliente cliente;
    //bool encontrado = false;
    /// Leer registros hasta encontrar el cliente
    while (fread(&cliente, tamReg, 1, pCliente) == 1){
        if (cliente.getNumeroCliente() == numeroCliente){
            /// Actualiza solo el número de compras
            cliente.setComprasRealizadas(nuevasCompras);
            /// Vuelve al inicio del registro del cliente
            fseek(pCliente, -static_cast<long>(tamReg), SEEK_CUR);
            /// Escribe el registro actualizado
            bool escribio = fwrite(&cliente, tamReg, 1, pCliente);
            fclose(pCliente);
            return escribio; /// Retorna true si se escribió correctamente
        }
    }
    fclose(pCliente);
    rlutil::setColor(rlutil::RED);
    cout << "Cliente no encontrado." << endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    return false; /// Retorna false si no se encontró el cliente
}

bool ArchivoCliente::buscarYMostrarCliente(int numeroCliente) {
    FILE *pCliente;
    Cliente reg;
    pCliente = fopen(nombreCliente, "rb");
    if (pCliente == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"No se pudo abrir el Archivo "<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        return false;
    }
   while (fread(&reg, tamReg, 1, pCliente) == 1){
        if (reg.getNumeroCliente() == numeroCliente && reg.getEstado()){
            reg.mostrarCliente();
            fclose(pCliente);
            return true;
        }
    }
    fclose(pCliente);
    rlutil::setColor(rlutil::RED);
    cout << "Cliente no Encontrado" << endl;
    rlutil::setColor(rlutil::LIGHTBLUE);
    return false;
}

void buscarClientePorId(){
  ArchivoCliente archivoCliente;
    int numBuscado;
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el numero del cliente a buscar: ";
    cin >> numBuscado;
    if (!archivoCliente.buscarYMostrarCliente(numBuscado)){
        rlutil::setColor(rlutil::RED);
        cout << "No se encontro un cliente con el numero ingresado." << endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
}
