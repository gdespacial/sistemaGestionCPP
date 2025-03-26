#include <iostream>
#include <cstring>
#include <ctime>
#include "rlutil.h"
using namespace std;
#include "Cliente.h"
#include "Disco.h"
#include "Venta.h"
#include "ArchivoVenta.h"

void Cliente::cargarCliente(int number){
    if (number == 0){
        rlutil::setColor(rlutil::WHITE);
        cout << "Numero de Cliente: ";
        cin >> numeroCliente;
        cin.ignore();
    }else{
        numeroCliente = number;
    }
    cout << "DNI del cliente: ";
    cin >> dniCliente;
    cin.ignore();
    cout << "Nombre del cliente: ";
    cin.getline(nombre, sizeof(nombre));
    cout << "Apellido del cliente: ";
    cin.getline(apellido,sizeof(apellido));
    cout << "Email del cliente: ";
    cin.getline(email,sizeof(email));
    cout << "Direccion del cliente: ";
    cin.getline(direccion,sizeof(direccion));
    cout << "Telefono del cliente: ";
    cin >> telefono;
    estado = true;
}

void Cliente::mostrarCliente(){
    if(estado == true){
        rlutil::setColor(rlutil::LIGHTMAGENTA);
        cout<<"---------------------------------------"<<endl;
        cout << "Numero de cliente: " << numeroCliente<<endl;
        rlutil::setColor(rlutil::LIGHTBLUE);
        cout << "DNI del cliente: " << dniCliente << endl;
        cout << "Nombre del cliente: " << nombre << endl;
        cout << "Apellido del cliente: " << apellido<<endl;
        cout << "Email del cliente: "<<email<< endl;
        cout << "Direccion del cliente: "<< direccion << endl;
        cout << "Telefono del cliente: " << telefono << endl;
        cout << "Compras Realizadas: " << comprasRealizadas << endl;
        ArchivoVenta archivoVenta;
        float gastoTotal = archivoVenta.calcularGastoTotal(numeroCliente);
        cout << "Gasto total en compras: " << gastoTotal << " $" << endl;
        cout<<"---------------------------------------"<<endl;
    }
}
