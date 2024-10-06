#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Persona {
private:
    string nombre;
    int edad;
    string genero;
    string infoContacto;
    vector<string> historialMedico;
    double costoConsulta;
    double totalAPagar;
    string estado;
    string estadoPago; 

public:
    // Constructor
    Persona(const string& nombre, int edad, const string& genero, const string& infoContacto, double costoConsulta)
        : nombre(nombre), edad(edad), genero(genero), infoContacto(infoContacto), costoConsulta(costoConsulta), totalAPagar(0.0), estado("En espera"), estadoPago("Pago Pendiente") {}

    // Getters
    string getNombre() const {
        return nombre;
    }

    int getEdad() const {
        return edad;
    }

    string getGenero() const {
        return genero;
    }

    string getInfoContacto() const {
        return infoContacto;
    }

    string getEstado() const {
        return estado;
    }

    vector<string> getHistorialMedico() const {
        return historialMedico;
    }

    double getCostoConsulta() const {
        return costoConsulta;
    }

    double getTotalAPagar() const {
        return totalAPagar;
    }

    string getEstadoPago() const {
        return estadoPago;
    }

    // Setters
    void setEstado(const string& nuevoEstado) {
        estado = nuevoEstado;
    }

    void agregarHistorial(const string& historial) {
        historialMedico.push_back(historial);
    }

    void calcularTotalAPagar() {
        totalAPagar += costoConsulta;  
    }

    void cancelarPago() {
        estadoPago = "Cancelado";
    }

    void pagarConsulta() {
        estadoPago = "Pagado";
    }

 
    friend ostream& operator<<(ostream& os, const Persona& persona) {
        os << "Persona [Nombre: " << persona.nombre << ", Edad: " << persona.edad << ", Género: " << persona.genero
            << ", Contacto: " << persona.infoContacto << ", Costo de Consulta: $" << persona.costoConsulta
            << ", Total a Pagar: $" << persona.totalAPagar << ", Estado de Pago: " << persona.estadoPago
            << ", Estado: " << persona.estado << "]";
        return os;
    }
};

// Cola de personas en el consultorio
queue<Persona> colaPersonas;

void ingresarPersona() {
    string continuar;
    do {
        cout << "Ingrese los datos de la persona:" << endl;

        string nombre, genero, infoContacto;
        int edad;
        double costoConsulta;

        cout << "Nombre: ";
        cin >> nombre;
        cout << "Edad: ";
        cin >> edad;
        cout << "Género: ";
        cin >> genero;
        cout << "Información de contacto: ";
        cin >> infoContacto;
        cout << "Costo de consulta: ";
        cin >> costoConsulta;

        colaPersonas.push(Persona(nombre, edad, genero, infoContacto, costoConsulta));

        cout << "¿Deseas ingresar otra persona? (si - no): ";
        cin >> continuar;
    } while (continuar == "si");
}

void atenderPersona() {
    if (colaPersonas.empty()) {
        cout << "No hay personas en la cola." << endl;
    }
    else {
        Persona personaAtendida = colaPersonas.front();
        colaPersonas.pop();

        personaAtendida.setEstado("Atendido");
        personaAtendida.calcularTotalAPagar();

        cout << personaAtendida << " ha sido atendido." << endl;

        if (!colaPersonas.empty()) {
            cout << "Siguiente persona a ser atendida: " << colaPersonas.front().getNombre() << endl;
        }
        else {
            cout << "No hay más personas en espera." << endl;
        }
    }
}

void mostrarLista() {
    if (colaPersonas.empty()) {
        cout << "No hay personas en la cola." << endl;
    }
    else {
        cout << "Personas en la cola:" << endl;
        queue<Persona> copiaCola = colaPersonas;  
        while (!copiaCola.empty()) {
            Persona persona = copiaCola.front();
            cout << persona << endl;
            copiaCola.pop();
        }
    }
}

void cambiarEstadoPago() {
    if (colaPersonas.empty()) {
        cout << "No hay personas en la cola para actualizar el estado de pago." << endl;
        return;
    }

    string nombre;
    cout << "Ingrese el nombre de la persona a la que desea cambiar el estado de pago: ";
    cin >> nombre;

    queue<Persona> copiaCola;
    bool encontrado = false;

    while (!colaPersonas.empty()) {
        Persona persona = colaPersonas.front();
        colaPersonas.pop();

        if (persona.getNombre() == nombre) {
            encontrado = true;
            int opcionPago;
            cout << "Elija el nuevo estado de pago para " << nombre << ":\n";
            cout << "1. Marcar como Pagado\n";
            cout << "2. Marcar como Cancelado\n";
            cin >> opcionPago;

            if (opcionPago == 1) {
                persona.pagarConsulta();
            }
            else if (opcionPago == 2) {
                persona.cancelarPago();
            }
            else {
                cout << "Opción no válida. Estado de pago no cambiado.\n";
            }
        }

        copiaCola.push(persona);
    }

    colaPersonas = copiaCola;

    if (!encontrado) {
        cout << "Persona no encontrada en la cola.\n";
    }
}

int main() {
    cout << "\tBIENVENIDO AL CONSULTORIO DEL DR. SIMI" << endl;
    cout << "**********************************************" << endl;

    int opcion = -1;
    while (opcion != 0) {
        cout << "Escriba la opción deseada:" << endl;
        cout << "1. Ingresar nueva Persona" << endl;
        cout << "2. Atender siguiente Persona" << endl;
        cout << "3. Mostrar cola de Personas" << endl;
        cout << "4. Cambiar estado de pago" << endl;
        cout << "0. Salir" << endl;
        cin >> opcion;
        cout << "**********************************************" << endl;

        switch (opcion) {
        case 1:
            ingresarPersona();
            break;
        case 2:
            atenderPersona();
            break;
        case 3:
            mostrarLista();
            break;
        case 4:
            cambiarEstadoPago();
            break;
        case 0:
            cout << "Hasta luego!" << endl;
            break;
        default:
            cout << "Ingrese una opción válida" << endl;
            break;
        }
    }

    return 0;
}
