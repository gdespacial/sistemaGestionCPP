#ifndef CLIENTE_H
#define CLIENTE_H
class Cliente{
private:
    int numeroCliente;
    int dniCliente;
    char nombre[50];
    char apellido[50];
    char email[50];
    char direccion[100];
    int telefono;
    int comprasRealizadas;
    bool estado;
public:
    Cliente() {
        numeroCliente = 0;
        comprasRealizadas = 0;
        estado = false;
    }
    void setNumeroCliente(int num){numeroCliente = num;}
    int getNumeroCliente(){return numeroCliente;}
    void setDniCliente(int d){dniCliente = d;}
    int getDniCliente(){return dniCliente;}
    const char* getNombre(){return nombre;}
    void setNombre(const char* nuevoNombre) {
    strncpy (nombre, nuevoNombre, sizeof(nombre) - 1);
    nombre [sizeof(nombre) -1] ='\0'; }
    const char* getApellido(){return apellido;}
     void setApellido(const char* nuevoApellido) {
    strncpy (apellido, nuevoApellido, sizeof(apellido) - 1);
    apellido [sizeof(apellido) -1] ='\0'; }
    void setDireccion(const char* nuevaDireccion) {
    strncpy(direccion, nuevaDireccion, sizeof(direccion) - 1);
    direccion[sizeof(direccion)- 1] = '\0';}
    const char* getDireccion(){return direccion;}
    void setEmail(const char *nuevoEmail) {
    strncpy(email, nuevoEmail, sizeof(email) - 1);
    email[sizeof(email) - 1] = '\0';}
    const char* getEmail(){return email;}                      /// getters, setters, mostrarCliente y cargarCliente.
    void setTelefono(int tel){telefono = tel;}
    int getTelefono(){return telefono;}
    void setComprasRealizadas(int c) { comprasRealizadas = c; }
    int getComprasRealizadas(){ return comprasRealizadas;}
    void setEstado(bool est){estado = est;}
    bool getEstado(){return estado;}
    void cargarCliente(int dni = 0);
    void mostrarCliente();
};
#endif // CLIENTE_H
