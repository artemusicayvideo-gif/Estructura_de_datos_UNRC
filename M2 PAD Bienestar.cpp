#include <iostream>
#include <string>

using namespace std;

// =============================================================
// REQUERIMIENTO 1: Uso de una estructura (struct) para la sesión
// =============================================================
struct Sesion {
    int numeroEquipo;       // Debe ser entre 1 y 12
    string nombreUsuario;   // Nombre del beneficiario
    Sesion* siguiente;      // Puntero que guarda la dirección de memoria de la siguiente sesión
};

// --- PROTOTIPOS DE FUNCIONES ---
// Pasamos el puntero 'cabeza' por referencia (&) para poder modificar la lista original
void darAlta(Sesion*& cabeza);
void darBaja(Sesion*& cabeza);
void mostrarSesiones(Sesion* cabeza);
void mostrarBienvenida();

int main() {
    // REQUERIMIENTO 2: Implementar el uso de punteros
    // 'cabeza' es nuestro puntero principal. Al inicio apunta a la nada (nullptr) porque no hay sesiones.
    Sesion* cabeza = nullptr; 
    int opcion = 0;

    do {
        mostrarBienvenida();
        cout << "1. Dar de alta una sesion" << endl;
        cout << "2. Dar de baja una sesion" << endl;
        cout << "3. Mostrar sesiones activas" << endl;
        cout << "4. Salir del sistema" << endl;
        cout << "Elige una opcion: ";

        // Blindaje contra caracteres inválidos (Reciclado de tu programa anterior)
        if (!(cin >> opcion)) {
            cin.clear(); 
            cin.ignore(10000, '\n'); 
            opcion = 0;
        }

        switch(opcion) {
            case 1: darAlta(cabeza); break;
            case 2: darBaja(cabeza); break;
            case 3: mostrarSesiones(cabeza); break;
            case 4: 
                cout << "\nCerrando el sistema SIG-Conecta. ¡Hasta pronto!" << endl;
                break;
            default: cout << "\n-> Error: Opcion no valida." << endl;
        }
    } while(opcion != 4);

    return 0;
}

// --- IMPLEMENTACIÓN DE FUNCIONES ---

void mostrarBienvenida() {
    cout << "\n==========================================" << endl;
    cout << "        SISTEMA PAD-BIENESTAR M2" << endl;
    cout << "     Gestor Dinamico de Sesiones" << endl;
    cout << "==========================================" << endl;
}

void darAlta(Sesion*& cabeza) {
    int numEquipo;
    string nombre;

    cout << "\n--- ALTA DE SESION ---" << endl;
    cout << "Ingresa el numero de equipo (1 al 12): ";
    cin >> numEquipo;

    // REQUERIMIENTO 3: Validar que el número esté dentro del rango permitido
    if (numEquipo < 1 || numEquipo > 12) {
        cout << "-> Error: Numero de equipo fuera de rango. Debe ser entre 1 y 12." << endl;
        return;
    }

    // Validación extra: Comprobar si el equipo ya está en uso recorriendo la lista
    Sesion* comprobacion = cabeza;
    while (comprobacion != nullptr) {
        if (comprobacion->numeroEquipo == numEquipo) {
            cout << "-> Error: El equipo " << numEquipo << " ya esta en uso." << endl;
            return;
        }
        comprobacion = comprobacion->siguiente;
    }

    cout << "Ingresa el nombre del usuario: ";
    getline(cin >> ws, nombre);

    // REQUERIMIENTO 2: Uso de Memoria Dinámica (new)
    // Pedimos memoria a la computadora JUSTO en este momento para crear un nuevo nodo
    Sesion* nuevaSesion = new Sesion;
    nuevaSesion->numeroEquipo = numEquipo;
    nuevaSesion->nombreUsuario = nombre;
    nuevaSesion->siguiente = nullptr; // Como es el último, no apunta a nadie más

    // Enlazar el nuevo nodo a nuestra lista
    if (cabeza == nullptr) {
        // Si la lista estaba vacía, el nuevo nodo es la cabeza
        cabeza = nuevaSesion;
    } else {
        // Si ya hay sesiones, recorremos la lista hasta llegar al final y lo "enganchamos"
        Sesion* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevaSesion;
    }
    cout << "-> ¡Exito! Sesion registrada en el equipo " << numEquipo << "." << endl;
}

void darBaja(Sesion*& cabeza) {
    if (cabeza == nullptr) {
        cout << "\n-> No hay sesiones activas para dar de baja." << endl;
        return;
    }

    int numEquipo;
    cout << "\n--- BAJA DE SESION ---" << endl;
    cout << "Ingresa el numero de equipo a liberar: ";
    cin >> numEquipo;

    Sesion* actual = cabeza;
    Sesion* anterior = nullptr;

    // Buscar el equipo en la lista enlazada
    while (actual != nullptr && actual->numeroEquipo != numEquipo) {
        anterior = actual;
        actual = actual->siguiente;
    }

    // Si llegamos al final y no lo encontramos
    if (actual == nullptr) {
        cout << "-> Error: No se encontro una sesion activa en el equipo " << numEquipo << "." << endl;
        return;
    }

    // REQUERIMIENTO 2: Ajuste de punteros y uso de delete
    if (anterior == nullptr) {
        // Reasignación del puntero principal: El registro a dar de baja ocupa la primera posición en la memoria.
        cabeza = actual->siguiente;
    } else {
        // Puenteamos el nodo que vamos a borrar
        anterior->siguiente = actual->siguiente;
    }

    // Liberamos la memoria física de la computadora para evitar fugas de memoria
    delete actual; 
    cout << "-> ¡Exito! Sesion finalizada. Equipo " << numEquipo << " liberado." << endl;
}

void mostrarSesiones(Sesion* cabeza) {
    cout << "\n--- SESIONES ACTIVAS ---" << endl;
    
    if (cabeza == nullptr) {
        cout << "No hay usuarios conectados en este momento." << endl;
        return;
    }

    // Recorremos la lista usando un puntero temporal
    Sesion* actual = cabeza;
    while (actual != nullptr) {
        cout << "Equipo " << actual->numeroEquipo << " | Usuario: " << actual->nombreUsuario << endl;
        actual = actual->siguiente; // Brincamos al siguiente nodo de la lista
    }
    cout << "------------------------" << endl;
}