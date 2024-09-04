
#include<iostream>
#include<queue>
#include<string>

using namespace std;

int main() {

    queue<std::string> nombres; // Vector para almacenar los nombres
    string nombre;

    cout << "\tCONSULTORIO DR. SIMI" << endl;
    cout << "Lista de pacientes por orden de llegada: " << endl;

    while (true) {
    getline(cin, nombre);
        if (nombre.empty()) {
            break; // Salir del bucle si se ingresa una línea vacía
        }
    nombres.push(nombre); // Agregar el nombre al vector
    }

    cout << "\nNombres almacenados (en orden de ingreso):\n";
    while (!nombres.empty()) {
        cout << "- " << nombres.front() << "\n";
        nombres.pop(); // Eliminar el nombre de la cola
    }



	return 0;
}

