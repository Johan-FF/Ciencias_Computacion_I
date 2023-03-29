#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Estudiante {
public:
    Estudiante(string nombre, int codigo) : nombre_(nombre), codigo_(codigo) {}

    string getNombre() const { return nombre_; }
    int getCodigo() const { return codigo_; }

    void setNombre(string nombre) { nombre_ = nombre; }
    void setCodigo(int codigo) { codigo_ = codigo; }

private:
    string nombre_;
    int codigo_;
};

class ListaEstudiantes {
public:
    void insertar(Estudiante estudiante) {
        estudiantes_.push_back(estudiante);
    }

    void eliminar(int codigo) {
        for (auto it = estudiantes_.begin(); it != estudiantes_.end(); ++it) {
            if (it->getCodigo() == codigo) {
                estudiantes_.erase(it);
                break;
            }
        }
    }

    void modificar(int codigo, string nuevo_nombre) {
        for (auto& estudiante : estudiantes_) {
            if (estudiante.getCodigo() == codigo) {
                estudiante.setNombre(nuevo_nombre);
                break;
            }
        }
    }

    void imprimir() const {
        for (const auto& estudiante : estudiantes_) {
            cout << "Nombre: " << estudiante.getNombre() << ", Codigo: " << estudiante.getCodigo() << endl;
        }
    }

private:
    vector<Estudiante> estudiantes_;
};

int main() {
    ListaEstudiantes lista;

    // Insertar estudiantes
    lista.insertar(Estudiante("Juan", 1001));
    lista.insertar(Estudiante("Maria", 1002));
    lista.insertar(Estudiante("Carlos", 1003));

    // Imprimir lista
    cout << "Lista de estudiantes:" << endl;
    lista.imprimir();

    // Modificar estudiante
    lista.modificar(1002, "Mariana");

    // Imprimir lista actualizada
    cout << "Lista de estudiantes actualizada:" << endl;
    lista.imprimir();

    // Eliminar estudiante
    lista.eliminar(1003);

    // Imprimir lista final
    cout << "Lista de estudiantes final:" << endl;
    lista.imprimir();

    return 0;
}
