#include "rlutil.h"
#ifndef VENTA_H
#define VENTA_H
class Fecha{
private:
int dia, mes, anio;
public:
 Fecha(int d = 0, int m = 0, int a = 0){dia = d;mes = m;anio = a;}
 void setDia(int d){dia = d;}
 void setMes(int m){mes = m;}
 void setAnio(int a){anio = a;}
 int getDia(){return dia;}
 int getMes(){return mes;}
 int getAnio(){return anio;}
 bool esMayorQueHoy() const;
 bool esFechaValida() const;

void cargarFecha(){    /// 2/12/2024 VALIDACIONES NUEVAS INCLUIDAS,SE USO LA LIBRERIA CTIME, AÑO MINIMO PERMITIDO Y MODIFICABLE, NO SE PUEDE CARGAR VENTAS EN DIAS QUE SEAN SUPERIORES A LA FECHA ACTUAL, Y AHORA SE RESPETAN LOS MESES DEL AÑO Y LOS DIAS DEL MES.
    const int ANIO_MINIMO = 2020;  /// Año mínimo permitido
    do{
        do {
            rlutil::setColor(rlutil::WHITE);
            cout << "dia: ";
            cin >> dia;
            if (dia < 1 || dia > 31) {
                rlutil::setColor(rlutil::RED);
                cout << "Error: El dia debe estar entre 1 y 31. Intente nuevamente.";
                rlutil::setColor(rlutil::WHITE);
            }
        } while (dia < 1 || dia > 31);

        do{
            cout << "mes: ";
            cin >> mes;
            if (mes < 1 || mes > 12){
                rlutil::setColor(rlutil::RED);
                cout << "Error: El mes debe estar entre 1 y 12. Intente nuevamente.";
                rlutil::setColor(rlutil::WHITE);
            }
        } while (mes < 1 || mes > 12);
        do{
            rlutil::setColor(rlutil::WHITE);
            cout << "anio: ";
            cin >> anio;
            if (anio < ANIO_MINIMO){
                rlutil::setColor(rlutil::RED);
                cout << "Error: El anio debe ser mayor o igual a " << ANIO_MINIMO << ". Intente nuevamente.\n";
                rlutil::setColor(rlutil::WHITE);
            }

        if (!esFechaValida()){
            rlutil::setColor(rlutil::RED);
            cout << "Error: La fecha ingresada no es valida. Intente nuevamente.\n";
            rlutil::setColor(rlutil::WHITE);
        }else if (esMayorQueHoy()){
            rlutil::setColor(rlutil::RED);
            cout << "Error: La fecha no puede ser posterior al dia de hoy. Intente nuevamente.\n";
            rlutil::setColor(rlutil::WHITE);
        }
        }while (anio < ANIO_MINIMO);

    } while (!esFechaValida() || esMayorQueHoy());
}

 void mostrarFecha(){
    cout << dia << "/"<<mes<<"/"<<anio << endl;
}
    /// Sobrecarga del operador >=
    bool operator>=(const Fecha& otra) const{
        if (anio > otra.anio) return true;
        if (anio == otra.anio && mes > otra.mes) return true;
        if (anio == otra.anio && mes == otra.mes && dia >= otra.dia) return true;
        return false;
    }
    /// Sobrecarga del operador <=
    bool operator<=(const Fecha& otra) const{
        if (anio < otra.anio) return true;
        if (anio == otra.anio && mes < otra.mes) return true;
        if (anio == otra.anio && mes == otra.mes && dia <= otra.dia) return true;
        return false;
    }

    bool operator>(const Fecha& otra) const{
        if (anio > otra.anio) return true;
        if (anio == otra.anio && mes > otra.mes) return true;
        if (anio == otra.anio && mes == otra.mes && dia > otra.dia) return true;
        return false;
    }
};

class VentaDetalle{
private:
    int idVentaDetalle;
    int idVenta;
    int idDisco;
    float monto;
    int cantidad;
    bool estado;
public:
    VentaDetalle(){
        idVentaDetalle = 0;
        idVenta = 0;
        idDisco = 0;
        monto = 0.0;
        cantidad = 0;
        estado = false;
    }
    void setIdVentaDetalle(int idVenDet){idVentaDetalle = idVenDet;}
    int getIdVentaDetalle(){return idVentaDetalle;}
    void setIdVenta(int idVen){idVenta = idVen;}
    int getIdVenta(){return idVenta;}
    void setIdDisco(int i){idDisco = i;}
    int getIdDisco(){return idDisco;}
    void setMonto(float m){monto = m;}
    float getMonto(){return monto;}
    void setCantidad(int c){cantidad = c;}
    int getCantidad(){return cantidad;}
    void setEstado(bool est){estado = est;}
    bool getEstado(){return estado;}
    void cargarDetalle(int idV, int nuevoIdVentaDetalle);
    void mostrarDetalle();
};

class Venta{
private:
    int idVenta;
    Fecha fechaVenta;
    int numeroCliente;
    float montoTotal;
    bool estado;
    VentaDetalle detalles[10];
    int cantidadDetalles;
    Cliente cliente;
public:
    Venta(){
        idVenta = 0;
        numeroCliente = 0;
        montoTotal = 0.0;
        cantidadDetalles = 0;
        estado = false;
    }
    void setIdVenta(int idVen){idVenta = idVen;}
    int getIdVenta(){return idVenta;}
    void setFecha(Fecha f){fechaVenta = f;}
    Fecha getFecha(){return fechaVenta;}
    void setMontoTotal(float mT){montoTotal = mT;}
    float getMontoTotal(){return montoTotal;}
    void setNumeroCliente(int num){numeroCliente = num;}
    int getNumeroCliente(){return numeroCliente;}
    void setEstado(bool est){estado = est;}
    bool getEstado(){return estado;}
    void cargarVenta(int id, int numeroCliente);
    void mostrarVenta();
    void agregarDetalle();
    void aumentarComprasCliente(int numeroCliente);
    float calcularMontoTotal();
};
#endif // VENTA_H
