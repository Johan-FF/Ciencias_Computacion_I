#include "Lista.h"
#include <stdexcept>

struct Ingrediente {
    string nombre;
    float cantidad;
    string medida;
};

struct Receta {
    string nombre;
    int tiempo_preparacion;
    int cantidad_personas;
    Lista<Ingrediente>* ingredientes;

    // Constructor de copia para la lista de ingredientes
    Receta(const Receta& otra) : nombre(otra.nombre), tiempo_preparacion(otra.tiempo_preparacion),
    cantidad_personas(otra.cantidad_personas), ingredientes(otra.ingredientes) {}
    //Constructor por defecto
    Receta() : nombre(""), tiempo_preparacion(0), cantidad_personas(0) {}
};

class MultilistaRecetas {
private:
    Lista<Receta*> recetas;
public:
	void agregarReceta(string nombre, int tiempo_preparacion, int cantidad_personas, Lista<Ingrediente>& lista_ingredientes);
    Receta buscarReceta(string nombre);
    ~MultilistaRecetas() {
        Nodo<Receta*>* actual = recetas.getInicio();
        while (actual != nullptr) {
            delete actual->valor;
            actual = actual->siguiente;
        }
    }
};

void MultilistaRecetas::agregarReceta(string nombre, int tiempo_preparacion, int cantidad_personas,Lista<Ingrediente>& lista_ingredientes) {
    Receta* receta = new Receta();
    receta->nombre = nombre;
    receta->tiempo_preparacion = tiempo_preparacion;
    receta->cantidad_personas = cantidad_personas;
    receta->ingredientes = &lista_ingredientes;
    recetas.insertar_inicio(receta);
}



Receta MultilistaRecetas::buscarReceta(string nombre) {
    Nodo<Receta*>* actual = recetas.getInicio();
    while (actual != nullptr) {
        if (actual->valor->nombre == nombre) {
            return *actual->valor;
        }
        actual = actual->siguiente;
    }
    throw std::runtime_error("Receta no encontrada");
}

int main() {
    // Inicializamos nuestro objeto MiLista de la clase MultilistaRecetas
    MultilistaRecetas miLista;
    // Inicializamos nuestra lista de ingredientes
    Lista<Ingrediente> listaIngredientesArrozHuevo;
    
    Lista<Ingrediente> listaIngredientesArrozHuevoo;
    // Creamos unos ingredientes iniciales
    Ingrediente Arroz;
    Arroz.cantidad = 500;
    Arroz.medida = "Gramos";
    Arroz.nombre = "Arroz Diana";

    Ingrediente Huevo;
    Huevo.cantidad = 2;
    Huevo.medida = "Doble A";
    Huevo.nombre = "Huevo";

    // Insertamos nuestros ingredientes en la lista
    listaIngredientesArrozHuevo.insertar_inicio(Arroz);
    listaIngredientesArrozHuevo.insertar_final(Huevo);
    
    miLista.agregarReceta("Arroz Con Huevo",30,1,listaIngredientesArrozHuevo);
    cout<<miLista.buscarReceta("Arroz Con Huevo").ingredientes->buscar(0).nombre<<endl;

}
