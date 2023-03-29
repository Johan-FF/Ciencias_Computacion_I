#include <iostream>
#include <string>

using namespace std;

struct Estudiante {
    string nombre;
    int codigo;
    Estudiante* siguiente = nullptr;
    Estudiante(string nom, int cod) : nombre(nom), codigo(cod), siguiente(nullptr) {}
};

class ListaEstudiantes {

private:
    Estudiante* primero_ = nullptr;
    
    
public:
    void insertar(Estudiante* estudiante) {
        // Caso especial: lista vacía
        if (primero_ == nullptr) {
            primero_ = estudiante;
            return;
        }

        // Caso especial: insertar al principio
        if (estudiante->codigo < primero_->codigo) {
            estudiante->siguiente = primero_;
            primero_ = estudiante;
            return;
        }

        // Caso general: insertar en medio o al final
        Estudiante* actual = primero_;
        while (actual->siguiente != nullptr && estudiante->codigo > actual->siguiente->codigo) {
            actual = actual->siguiente;
        }
        estudiante->siguiente = actual->siguiente;
        actual->siguiente = estudiante;
    }

    void eliminar(int codigo) {
        if (primero_ == nullptr) {
            return;
        }

        // Caso especial: eliminar el primero
        if (primero_->codigo == codigo) {
            Estudiante* temp = primero_;
            primero_ = primero_->siguiente;
            delete temp;
            return;
        }

        // Caso general: buscar y eliminar
        Estudiante* actual = primero_;
        while (actual->siguiente != nullptr && actual->siguiente->codigo != codigo) {
            actual = actual->siguiente;
        }
        if (actual->siguiente != nullptr) {
            Estudiante* temp = actual->siguiente;
            actual->siguiente = actual->siguiente->siguiente;
            delete temp;
        }
    }

    Estudiante* buscar(int codigo) const {
        Estudiante* actual = primero_;
        while (actual != nullptr && actual->codigo != codigo) {
            actual = actual->siguiente;
        }
        return actual;
    }

    void modificar(int codigo, string nuevo_nombre) {
        Estudiante* estudiante = buscar(codigo);
        if (estudiante != nullptr) {
            estudiante->nombre = nuevo_nombre;
        }
    }

    void imprimir() const {
        cout << "Lista de estudiantes (ordenada por codigo):" << endl;
        Estudiante* actual = primero_;
        while (actual != nullptr) {
            cout << "Nombre: " << actual->nombre << ", Codigo: " << actual->codigo << endl;
            actual = actual->siguiente;
        }
    }
};

int main() {
    ListaEstudiantes lista;

    // Insertar estudiantes
    lista.insertar(new Estudiante{ "Juan", 1003 });
    lista.insertar(new Estudiante{ "Maria", 1001 });
    lista.insertar(new Estudiante{ "Carlos", 1002 });

    // Imprimir lista
    lista.imprimir();

    // Modificar estudiante
    lista.modificar(1002, "Mariana");

    // Imprimir lista actualizada
    lista.imprimir();

    // Eliminar estudiante
    lista.eliminar(1003);

    // Imprimir lista final
    lista.imprimir();

	
	return 0;
}
