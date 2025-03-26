#include <iostream>
#include "rlutil.h"
#include <ctime>
using namespace std;
#include "menu.h"

void limpiarPantalla(){     /// Esta es la función que permite limpiar la pantalla tanto en Windows como en Ubuntu.
#ifdef _WIN32 // Para Windows
    system("cls");
#else // Para Linux
    system("clear");
#endif
}

void mostrarMenuPrincipal(){

    limpiarPantalla();
    rlutil::setColor(rlutil::LIGHTBLUE); /// Usamos Rlutil para darle color e implementar algunos caracteres ASCII.
    cout << "  -------------------------------" << endl;
    cout << " |      ~  VINTAGE RECORDS ~     |" << endl;
    cout << " |-------------------------------|" << endl;
    cout << " | 1. Gestion de Artistas        |" << endl;
    cout << " | 2. Gestion de Discos          |" << endl;
    cout << " | 3. Gestion de Clientes        |" << endl;
    cout << " | 4. Gestion de Ventas          |" << endl;
    cout << " | 5. Recaudacion                |" << endl;
    cout << " | 0. Salir del Programa         |" << endl;
    cout << "  -------------------------------" << endl;
    cout << " | Seleccione una Opcion         |" <<endl;
    cout << "  -------------------------------"  << endl;
    }

void mostrarMenuArtistas(){

    limpiarPantalla();
    cout << " -------------------------------------" << endl;
    cout << "|      ~  GESTION DE ARTISTAS  ~      |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "| 1. Alta de Artistas                 |" << endl;
    cout << "| 2. Baja de Artistas                 |" << endl;
    cout << "| 3. Modificar Artistas               |" << endl;
    cout << "| 4. Listar Artistas                  |" << endl;
    cout << "| 5. Consultas                        |" << endl;
    cout << "| 0. Volver al Menu Principal         |" << endl;
    cout << " -------------------------------------"  << endl;
    cout << "| Seleccione una Opcion               |" <<endl;
    cout << " -------------------------------------"  << endl;
    }

void mostrarMenuDiscos(){

    limpiarPantalla();
    cout << " -----------------------------------" << endl;
    cout << "|      ~  GESTION DE DISCOS  ~      |" << endl;
    cout << "|-----------------------------------|" << endl;
    cout << "|  1. Alta de Disco                 |" << endl;
    cout << "|  2. Baja de Disco                 |" << endl;
    cout << "|  3. Modificar Disco               |" << endl;
    cout << "|  4. Listar Disco                  |" << endl;
    cout << "|  5. Consultas                     |" << endl;
    cout << "|  6. Listar Discos Por Artista     |" << endl;
    cout << "|  0. Volver al Menu Principal      |" << endl;
    cout << " -----------------------------------"  << endl;
    cout << "| Seleccione una Opcion             |" <<endl;
    cout << " -----------------------------------"  << endl;
    }

void mostrarMenuClientes(){

    limpiarPantalla();
    cout << " -------------------------------------" << endl;
    cout << "|      ~  GESTION DE CLIENTES  ~      |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "|  1. Alta de Cliente                 |" << endl;
    cout << "|  2. Baja de Cliente                 |" << endl;
    cout << "|  3. Modificar Datos del Cliente     |" << endl;
    cout << "|  4. Listar Clientes                 |" << endl;
    cout << "|  5. Consultas                       |" << endl;
    cout << "|  0. Volver al Menu Principal        |" << endl;
    cout << " ------------------------------------ "  << endl;
    cout << "| Seleccione una Opcion               |" <<endl;
    cout << " -------------------------------------"  << endl;
    }

void mostrarMenuVentas(){
   limpiarPantalla();
    cout <<"  -----------------------------------" << endl;
    cout << "|      ~  GESTION DE VENTAS  ~      |" << endl;
    cout << "|-----------------------------------|" << endl;
    cout << "|  1. Alta de Venta                 |" << endl;
    cout << "|  2. Baja de Venta                 |" << endl;
    cout << "|  3. Modificar Datos de Ventas     |" << endl;
    cout << "|  4. Listar Ventas                 |" << endl;
    cout << "|  5. Consultas                     |" << endl;
    cout << "|  6. Listar Ventas por Cliente     |" << endl;
    cout << "|  0. Volver al Menu Principal      |" << endl;
    cout << " -----------------------------------"  << endl;
    cout << "| Seleccione una Opcion             |" <<endl;
    cout << " -----------------------------------"  << endl;
    }

void mostrarMenuConsultasArtistas(){
    limpiarPantalla();
    cout << " ---------------------------------------" << endl;
    cout << "|      ~  CONSULTAS POR ARTISTAS  ~     |" << endl;
    cout << "|---------------------------------------|" << endl;
    cout << "|  1. Buscar Artistas por ID            |" << endl;
    cout << "|  0. Volver al Menu Anterior           |" << endl;
    cout << " ---------------------------------------"  << endl;
    cout << "| Seleccione una Opcion                 |" <<endl;
    cout << " ---------------------------------------"  << endl;
}

void mostrarMenuConsultasDiscos(){
    limpiarPantalla();
    cout << " --------------------------------------" << endl;
    cout << "|      ~  CONSULTAS POR DISCOS  ~      |" << endl;
    cout << "|--------------------------------------|" << endl;
    cout << "|  1. Buscar Discos por ID             |" << endl;
    cout << "|  0. Volver al Menu Anterior          |" << endl;
    cout << " --------------------------------------" << endl;
    cout << "| Seleccione una Opcion                |" <<endl;
    cout << " --------------------------------------"  << endl;
}

void mostrarMenuConsultasClientes(){
    limpiarPantalla();
    cout <<"  -----------------------------------------" << endl;
    cout << "|      ~  CONSULTAS POR CLIENTES  ~       |" << endl;
    cout << "|-----------------------------------------|" << endl;
    cout << "|  1. Buscar Clientes por Numero          |" << endl;
    cout << "|  0. Volver al Menu Anterior             |" << endl;
    cout << " -----------------------------------------" << endl;
    cout << "| Seleccione una Opcion                   |" <<endl;
    cout << " -----------------------------------------"  << endl;
}

void mostrarMenuConsultasVentas(){
    limpiarPantalla();
    cout <<"  --------------------------------------"  << endl;
    cout << "|      ~  CONSULTAS POR VENTAS  ~      |" << endl;
    cout << "|--------------------------------------|" << endl;
    cout << "|  1. Buscar Ventas por ID             |" << endl;
    cout << "|  0. Volver al Menu Anterior          |" << endl;
    cout << " --------------------------------------"  << endl;
    cout << "| Seleccione una Opcion                |" <<endl;
    cout << " --------------------------------------"  << endl;
}

void mostrarMenuListadosDiscos(){
    limpiarPantalla();
    cout <<"  -------------------------------------"  << endl;
    cout << "|      ~  LISTADOS DE DISCOS  ~       |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "|  1. Listar Discos por Artista       |" << endl;
    cout << "|  0. Volver al Menu Anterior         |" << endl;
    cout << " -------------------------------------"  << endl;
    cout << "| Seleccione una Opcion               |" <<endl;
    cout << " -------------------------------------"  << endl;

}

void mostrarMenuListadosVentas(){
    limpiarPantalla();
    cout <<"  -------------------------------------"  << endl;
    cout << "|      ~  LISTADOS DE VENTAS  ~       |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "|  1. Listar Ventas por Cliente       |" << endl;
    cout << "|  0. Volver al Menu Anterior         |" << endl;
    cout << " -------------------------------------"  << endl;
    cout << "| Seleccione una Opcion               |" <<endl;
    cout << " -------------------------------------"  << endl;

}

void mostrarMenuRecaudacion(){
    limpiarPantalla();
    cout <<"  ----------------------------------------" << endl;
    cout << "|            ~  RECAUDACION  ~           |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|  1. Recaudacion por rango de Fechas    |" << endl;
    cout << "|  2. Recaudacion por Anio               |" << endl;
    cout << "|  3. Recaudacion por Mes                |" << endl;
    cout << "|  4. Recaudacion por Dia                |" << endl;
    cout << "|  0. Volver al Menu Principal           |" << endl;
    cout << " ----------------------------------------" << endl;
    cout << "| Seleccione una Opcion                  |" <<endl;
    cout << " ----------------------------------------"  << endl;
}
