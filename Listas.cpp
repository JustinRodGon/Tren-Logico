#include <iostream>
#include <string>
#include <list>
using namespace std;

// ESTRUCTURAS NECESARIAS

list<string> amenidadesTren;

struct Amenidad
{
    string nombre;
    int cantidad;

    Amenidad(string n, int c) : nombre(n), cantidad(c) {}
};

struct Pasajero
{
    string nombre;
    string cedula;
    int asiento;
    int lugarParadaId;

    Pasajero(string n, string c, int a, int lp)
        : nombre(n), cedula(c), asiento(a), lugarParadaId(lp) {}
};

struct LugarParada
{
    int id;
    string nombre;

    LugarParada(int i, string n) : id(i), nombre(n) {}
};

// Nodo de la lista circular
struct NodoAmenidad
{
    Amenidad info;
    NodoAmenidad *sig;

    NodoAmenidad(Amenidad a) : info(a), sig(nullptr) {}
};

// CLASE VAGON

class Vagon
{
public:
    string nombre;
    int numero;
    NodoAmenidad *inicioAmenidades;
    list<Pasajero> pasajeros;

    Vagon(string n, int num) : nombre(n), numero(num), inicioAmenidades(nullptr) {}

    // -------------------- LOGICA DE PASAJEROS ---------------

    // verificar que el lugar exista al meter un pasajero
    bool verificarExistenciaLugar(Pasajero pasajero, const list<LugarParada> &lugares)
    {
        for (const auto &lugar : lugares)
        {
            if (lugar.id == pasajero.lugarParadaId)
            {
                return true;
            }
        }
        return false;
    }

    void reasignarPasajeros(int idEliminado, const list<LugarParada> &lugares)
    {
        // Busco la siguiente parada que este disponivle
        const LugarParada *siguienteLugar = nullptr;
        for (const auto &lugar : lugares)
        {
            if (lugar.id > idEliminado)
            {
                siguienteLugar = &lugar;
                break;
            }
        }

        if (!siguienteLugar && !lugares.empty())
            siguienteLugar = &lugares.front();
        // busco el pasajero con el id eliminado del lugar y reasigno el siguiente lugar
        for (auto &p : pasajeros)
        {
            if (p.lugarParadaId == idEliminado)
            {
                cout << "El pasajero " << p.nombre
                     << " se reasignará al lugar: "
                     << (siguienteLugar ? siguienteLugar->nombre : "ninguno") << endl;

                if (siguienteLugar)
                    p.lugarParadaId = siguienteLugar->id;
            }
        }
    }

    void agregarPasajeros(Pasajero pasajero, const list<LugarParada> &lugares)
    {

        if (verificarExistenciaLugar(pasajero, lugares))
        {

            pasajeros.push_back(pasajero);
            cout << "Se agrego correctamente" << endl;
        }
        else
        {

            cout << "El lugar no existe" << endl;
        }
    }

    void mostrarPasajeros()
    {

        if (!pasajeros.empty())
        {
            for (const auto &pasajero : pasajeros)
            {
                cout << pasajero.nombre << " ";
            }
            cout << endl;
        }
        else

            cout << "No hay pasajeros" << endl;

        {
        }
    }

    void eliminarPasajeros(string idAEliminar)
    {

        auto it = pasajeros.begin();
        // recorro todo
        while (it != pasajeros.end())
        { // si es igual los id lo elimino
            if (it->cedula == idAEliminar)
            {
                pasajeros.erase(it);
                cout << "Eliminado Correctamente" << endl;
                break;
            }
            else
            {
                ++it;
            }
        }
    }

    //--------------- LOGICA AMENIDADES -----------------

    void agregarGlobalAmenidad(string amenidadN)
    {
        auto it = amenidadesTren.begin(); // creo el it que apunte al primer elemento
        bool bandera = true;
        while (it != amenidadesTren.end()) // recorro toda la lista
        {
            if (*it == amenidadN)
            {
                bandera = false;
                break;
            }

            ++it;
        }

        if (bandera)
        {
            amenidadesTren.push_back(amenidadN);
        }
    }

    void agregarAmenidad(Amenidad amenidad)
    {

        NodoAmenidad *nuevo = new NodoAmenidad(amenidad);

        if (inicioAmenidades == nullptr)
        {
            inicioAmenidades = nuevo;
            inicioAmenidades->sig = inicioAmenidades;
        }
        else
        {
            NodoAmenidad *temp = inicioAmenidades;
            while (temp->sig != inicioAmenidades) // recorro hasta el último
            {
                temp = temp->sig;
            }
            temp->sig = nuevo;             // último apunta al nuevo
            nuevo->sig = inicioAmenidades; // nuevo apunta al inicio
        }
    }

    string selectAmenidad(int seleccion)
    {

        switch (seleccion)
        {
        case 1:
            return "Cocinas";
            break;
        case 2:
            return "Baños";
            break;
        case 3:
            return "Asientos de Primera Clase";
            break;
        case 4:
            return "Asientos de Clase Turista";
            break;
        case 5:
            return "WiFi a bordo";
            break;
        case 6:
            return "Vagónes Restaurante";
            break;
        case 7:
            return "Espacios para Equipaje";
            break;
        default:
            return "Amenidades no disponible";
        }
    }

    void mostrarListaAmenidades()
    {
        NodoAmenidad *actual = inicioAmenidades;
        if (actual != nullptr)
        {
            do
            {
                cout << actual->info.nombre << " ";
                cout << actual->info.cantidad << " ";
                actual = actual->sig;

            } while (actual != inicioAmenidades);
        }
    }

    int mostrarListaAmenidadesPorNombre(string nombre)
    {
        NodoAmenidad *actual = inicioAmenidades;
        int num;
        if (actual != nullptr)
        {
            do
            {
                if (actual->info.nombre == nombre)
                {

                    num = actual->info.cantidad;
                    break;
                }

                actual = actual->sig;

            } while (actual != inicioAmenidades);
        }
        return num;
    }

    void eliminarAmenidad(string nombre)
    {
        if (inicioAmenidades == nullptr)
            return; // lista vacía

        NodoAmenidad *actual = inicioAmenidades;
        NodoAmenidad *anterior = nullptr;

        do
        {
            if (actual->info.nombre == nombre)
            {
                if (actual == inicioAmenidades)
                {
                    // Si solo hay un nodo
                    if (inicioAmenidades->sig == inicioAmenidades)
                    {
                        delete inicioAmenidades;
                        inicioAmenidades = nullptr;
                        return;
                    }
                    else
                    {
                        // Buscar el último nodo para reconectar
                        NodoAmenidad *ultimo = inicioAmenidades;
                        while (ultimo->sig != inicioAmenidades)
                            ultimo = ultimo->sig;

                        // Saltar el inicio
                        ultimo->sig = inicioAmenidades->sig;
                        NodoAmenidad *temp = inicioAmenidades;
                        inicioAmenidades = inicioAmenidades->sig;
                        delete temp;
                        actual = inicioAmenidades;
                    }
                }
                else // eliminar en medio o final
                {
                    anterior->sig = actual->sig;
                    delete actual;
                    actual = anterior->sig;
                }
            }
            else
            {
                anterior = actual;
                actual = actual->sig;
            }
        } while (actual != inicioAmenidades);
    }

    bool modificarAmenidad(string nombreVerificar, string nuevoNombre, int nuevaCantidad)
    {
        NodoAmenidad *actual = inicioAmenidades;
        if (actual != nullptr)
        {
            do
            {
                if (actual->info.nombre == nombreVerificar)
                {
                    actual->info.nombre = nuevoNombre;
                    actual->info.cantidad = nuevaCantidad;
                    return true;
                }
                actual = actual->sig;
            } while (actual != inicioAmenidades);
        }
        return false;
    }
};

// nodo de la lista doble
struct Nodo
{
    Vagon info;
    Nodo *sig;
    Nodo *ant;

    Nodo(Vagon v) : info(v), sig(nullptr), ant(nullptr) {}
};

// CLASE TREN
class Tren
{
private:
    Nodo *ptr;                       // final
    Nodo *posicion;                  // posicion para jugar
    Nodo *inicio;                    // inicio
    list<LugarParada> lugaresParada; // Lista STL para lugares de parada

public:
    Tren() : ptr(nullptr), posicion(nullptr), inicio(nullptr) {}

    // ordenar por id

    // ----------------- LOGICA DE LOD LUGRARES -----------------

    bool existeDup(LugarParada lugar)
    {

        bool existe = false;             // dejo la variable false
        auto it = lugaresParada.begin(); // creo el it que apunte al primer elemento

        while (it != lugaresParada.end()) // recorro toda la lista
        {
            if (lugar.id == it->id) // si el id del lugar que voy a agregar es igual a alguno que existe se acaba del ciclo y retorna verdader
            {
                existe = true;
                break;
            }
            ++it; // incremento entre elementos
        }
        return existe;
    }

    void insertarLugarParada(LugarParada lugar)
    {
        if (!existeDup(lugar))
        {

            auto it = lugaresParada.begin(); // creo un iterador esto apunta al inicio de la lista

            while (it != lugaresParada.end() && it->id < lugar.id) // recorro la lista donde no sea el final y donde el id de lugar sea menor  al siguiente
            {
                ++it; // va pasando entre lugares por asi decirjo
            }

            lugaresParada.insert(it, lugar);

            // ejemplo 1, 3, 6, 7 numero 4
            // salida de eso 1, 3 , 4 , 6 ,7 llega hasta el 6 como no es menor a 4 lo inserta atras
        }
        else
        {
            cout << "Existen duplicados" << endl;
        }
    }

    void mostrarLugares()
    {
        cout << "Ordenado ascendente por identificador:" << endl;

        // ordeno por id
        lugaresParada.sort([](const LugarParada &a, const LugarParada &b)
                           { return a.id < b.id; });

        // Mostrar
        for (const auto &lugar : lugaresParada)
        {
            cout << "ID: " << lugar.id << " - " << lugar.nombre << endl;
        }

        cout << "\nOrdenado ascendente por nombre:" << endl;

        // Ordeno por el nombre
        lugaresParada.sort([](const LugarParada &a, const LugarParada &b)
                           { return a.nombre < b.nombre; });

        // Mostrar
        for (const auto &lugar : lugaresParada)
        {
            cout << "ID: " << lugar.id << " - " << lugar.nombre << endl;
        }
    }

    void eliminarLugar(int idAEliminar)
    {
        // punteor o iterador por asi decirlo
        auto it = lugaresParada.begin();
        // recorro todo
        while (it != lugaresParada.end())
        { // si es igual los id lo elimino
            if (it->id == idAEliminar)
            {
                lugaresParada.erase(it);
                cout << "Lugar eliminado correctamente" << endl;
                break;
            }
            else
            {
                ++it;
            }
        }

        // Reasigno pasajeros de todos los vagones
        Nodo *actual = ptr;

        while (actual != nullptr)
        {
            actual->info.reasignarPasajeros(idAEliminar, lugaresParada);
            actual = actual->sig;
        }
    }

    // --------- LOGICA DE VAGON ---------------

    // insertar despues de la posicion en la que esta la posicion
    void insertar(Vagon dato)
    {
        Nodo *nuevo = new Nodo(dato);

        if (ptr == nullptr)
        {
            // si es nulo o sea el primero se agrega al principio el es el seg y ant
            ptr = nuevo;
            inicio = nuevo;
            posicion = nuevo;
            ptr->sig = nullptr;
            ptr->ant = nullptr;
        }

        // aqui si el actual es el ultimo de la lista
        else if (posicion->sig == nullptr)
        {
            posicion->sig = nuevo;
            nuevo->ant = posicion;
            nuevo->sig = nullptr;
            ptr = nuevo;
        }
        else
        {
            Nodo *primero = posicion->sig; // guardo la posicion del actual siguiente

            posicion->sig = nuevo; // el siguiente del actual ahora es el nuevo
            nuevo->ant = posicion; // y el anterior del nuevo es el actual ya ahi lo meto de siguiente dell actual
            nuevo->sig = primero;  // el siguiente del nuevo ahora es el primero que era el que le seguia antes al actual
            primero->ant = nuevo;  // y ahor el anterior es el nuevo hice esto

            // original ejemplo 3, 4, 6, 7  y quiero meter el 5 y mi actual es el 4
            // 3,4,5,6,7 cambio de posiciones
        }
    }

    void modificarVagon(string nombre, int numero)
    {
        getVagonActual()->nombre = nombre;
        getVagonActual()->numero = numero;
    }

    // mi version (no se nada de c++)
    void eliminar()
    {
        // verifico que no sea nulo
        if (posicion == nullptr)
        {
            cout << "La lista esta vacia" << endl;
        }
        else
        {
            // hago que en el que estoy el anterior apunte al siguiente del que estoy
            // y el siguiente al anterior al que estoy
            posicion->ant->sig = posicion->sig;
            posicion->sig->ant = posicion->ant;
        }
    }

    // eliminacion con el correcto uso de memoria
    void eliminarConmemoria()
    {
        if (posicion == nullptr)
        {
            cout << "La lista está vacía" << endl;
            return;
        }

        Nodo *aEliminar = posicion;      // guardo el nodo que voy a borrar
        Nodo *siguiente = posicion->sig; // guardo el siguiente para mover la posición

        if (posicion == posicion->sig)
        { // solo hay un nodo
            inicio = nullptr;
            ptr = nullptr;
            posicion = nullptr;
        }
        else
        {
            // actualizo enlaces del anterior y siguiente
            posicion->ant->sig = posicion->sig;
            posicion->sig->ant = posicion->ant;

            if (aEliminar == inicio)
            {
                inicio = aEliminar->sig; // actualizo inicio si estoy borrando el primero
            }

            posicion = siguiente; // muevo la posición a siguiente
        }

        delete aEliminar; // libero la memoria
    }

    void mostrar()
    {
        if (inicio == nullptr)
        {
            cout << "La lista está vacía" << endl;
            return;
        }

        Nodo *p = inicio;

        while (p != nullptr)
        {
            cout << p->info.nombre << endl;
            p = p->sig;
        }
    }

    // muestra en consola cual es la posicion actual
    void mostrarPosicion()
    {
        if (posicion == nullptr)
        {
            cout << "No hay ninguna posicion actual" << endl;
        }
        else
        {
            cout << "Posicion actual -> " << posicion->info.nombre
                 << " (" << posicion->info.numero << ")" << endl;
        }
    }

    void moverIzq()
    {
        Nodo *p = posicion;

        if (posicion->ant == nullptr)
        {
            cout << "No existen mas elementos a la izquierda" << endl;
        }
        else
        {
            posicion = p->ant;
        }
    }

    void moverDer()
    {
        Nodo *p = posicion;

        if (posicion->sig == nullptr)
        {
            cout << "No existen mas elementos a la derecha" << endl;
        }
        else
        {
            posicion = p->sig;
        }
    }

    Vagon *getVagonActual()
    {
        if (posicion != nullptr)
        {
            return &(posicion->info);
        }
        return nullptr;
    }

    bool hayVagones()
    {
        return inicio != nullptr;
    }

    list<LugarParada> &getLugaresParada()
    {
        return lugaresParada;
    }

    // --------REPORTES-----------

    // reporte 1
    // recorrer y ver cuales amenidades hay creadas
    // enumerar las amenidades que existen en todo el tren
    // enviar una opcion de la lista de las amenidades disponibles y poner numero de espacios

    void acumularAmenidades()
    {
        amenidadesTren.clear();

        if (inicio == nullptr)
        {
            cout << "La lista está vacía" << endl;
            return;
        }

        Nodo *p = inicio;

        while (p != nullptr)
        {
            NodoAmenidad *actualAmenidad = p->info.inicioAmenidades;

            if (actualAmenidad != nullptr)
            {
                do
                {

                    p->info.agregarGlobalAmenidad(actualAmenidad->info.nombre);
                    actualAmenidad = actualAmenidad->sig;
                } while (actualAmenidad != p->info.inicioAmenidades);
            }

            p = p->sig;
        }
    }

    void mostraMenuAmenidades()
    {
        cout << " Bienvenido elija la amenidad que desea detallar " << endl;
        int contador = 1;
        for (string amenidad : amenidadesTren)
        {
            cout << contador << ". " << amenidad << endl;
            ++contador;
        }
    }

    string tenerElementoPorPosicion(int pos)
    {
        if (pos <= 0 || pos > amenidadesTren.size())
        {
            throw out_of_range("Índice fuera de rango");
        }

        auto it = amenidadesTren.begin(); // me pongo en el primero
        advance(it, pos - 1); // con advance me muevo en la list
        return *it; // returna esa posiciion a la que me movi 
    }

    void reporteAmenidades(int eleccion)
    {
        string amen = tenerElementoPorPosicion(eleccion);
        string resultados;

        if (inicio == nullptr)
        {
            cout << "La lista está vacía" << endl;
            return;
        }
        Nodo *p = inicio;

        while (p != nullptr)
        {
            
           cout << p->info.nombre << ": " << p->info.mostrarListaAmenidadesPorNombre(amen) << " " << amen << endl;
            p = p->sig;
        }
        
    }
};

// DECLARACIONES DE FUNCIONES
void mostrarMenuPrincipal();
void menuAdministracion(Tren &tren);
void mostrarMenuAdministracion(Tren &tren);
void submenuVagones(Tren &tren);
void submenuPasajeros(Tren &tren);
void submenuAmenidades(Tren &tren);
void submenuLugaresParada(Tren &tren);
void menuReportes(Tren &tren);

int main()
{
    Tren miTren;

    miTren.insertarLugarParada(LugarParada(1, "San Jorge"));
    miTren.insertarLugarParada(LugarParada(2, "San Pedro"));

    int opcion;

    do
    {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            menuAdministracion(miTren);
            break;
        case 2:
            menuReportes(miTren);
            break;
        case 0:
            cout << "Gracias por usar el sistema" << endl;
            break;
        default:
            cout << "Opción inválida, intente de nuevo" << endl;
        }
    } while (opcion != 0);

    return 0;
}

void mostrarMenuPrincipal()
{
    cout << "\n===================================================" << endl;
    cout << "    SISTEMA DE GESTIÓN DE TRENES" << endl;
    cout << "===================================================" << endl;
    cout << "1. Administración de Información" << endl;
    cout << "2. Generación de Reportes" << endl;
    cout << "0. Salir" << endl;
    cout << "===================================================" << endl;
    cout << "Seleccione una opción: ";
}

void menuAdministracion(Tren &tren)
{
    int opcion;

    do
    {
        // Verificar si hay vagones antes de mostrar el menú
        if (!tren.hayVagones())
        {
            cout << "\n No existen vagones" << endl;
            cout << "Debe crear al menos un vagón para comenzar la gestión." << endl;
        }

        mostrarMenuAdministracion(tren);
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            submenuVagones(tren);
            break;
        case 2:
            submenuPasajeros(tren);
            break;
        case 3:
            submenuAmenidades(tren);
            break;
        case 4:
            submenuLugaresParada(tren);
            break;
        case 5:
            // Moverse al vagón siguiente
            tren.moverDer();
            break;
        case 6:
            // Moverse al vagón anterior
            tren.moverIzq();
            break;
        case 0:
            cout << "Volviendo al menú principal..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);
}

void mostrarMenuAdministracion(Tren &tren)
{
    cout << "\n===================================================" << endl;
    cout << "    ADMINISTRACIÓN DE INFORMACIÓN" << endl;
    cout << "===================================================" << endl;

    // Mostrar vagón actual
    tren.mostrarPosicion();

    cout << "===================================================" << endl;
    cout << "1. Gestión de Vagones" << endl;
    cout << "2. Gestión de Pasajeros" << endl;
    cout << "3. Gestión de Amenidades" << endl;
    cout << "4. Gestión de Lugares de Parada" << endl;
    cout << "5. Ir al siguiente vagón" << endl;
    cout << "6. Ir al vagón anterior" << endl;
    cout << "0. Volver al menú principal" << endl;
    cout << "===================================================" << endl;
    cout << "Seleccione una opción: ";
}

void submenuVagones(Tren &tren)
{
    int opcion;

    do
    {
        cout << "\n========================================" << endl;
        cout << "    GESTIÓN DE VAGONES" << endl;
        cout << "========================================" << endl;
        cout << "1. Agregar Vagón" << endl;
        cout << "2. Eliminar Vagón" << endl;
        cout << "3. Modificar Vagón" << endl;
        cout << "4. Mostrar Vagones" << endl;
        cout << "0. Volver" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            // Agregar vagon
            {
                string nombre;
                int numero;
                cout << "Ingrese el nombre del vagón: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese el número del vagón: ";
                cin >> numero;

                Vagon nuevoVagon(nombre, numero);
                tren.insertar(nuevoVagon);
                cout << "Vagón agregado correctamente." << endl;
            }
            break;
        case 2:
            // Eliminar vagon
            {
                char confirmacion;
                cout << "¿Está seguro que desea eliminar el vagón actual? (s/n): ";
                cin >> confirmacion;
                if (confirmacion == 's' || confirmacion == 'S')
                {
                    tren.eliminarConmemoria();
                    cout << "Vagón eliminado." << endl;
                }
            }
            break;
        case 3:
            // hacer el metodo de este
            {
                Vagon *vagonActual = tren.getVagonActual();
                if (vagonActual != nullptr)
                {
                    string nuevoNombre;
                    int nuevoNumero;
                    cout << "Nombre actual: " << vagonActual->nombre << endl;
                    cout << "Ingrese el nuevo nombre: ";
                    cin.ignore();
                    getline(cin, nuevoNombre);
                    cout << "Numero actual: " << vagonActual->numero << endl;
                    cout << "Ingrese el nuevo número del vagón: ";
                    cin >> nuevoNumero;
                    tren.modificarVagon(nuevoNombre, nuevoNumero);
                    cout << "Nombre modificado correctamente." << endl;
                }
                else
                {
                    cout << "No hay vagón actual para modificar." << endl;
                }
            }
            break;
        case 4:
            // Mostrar todos los vagones
            tren.mostrar();
            break;
        case 0:
            cout << "Volviendo..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);
}

void submenuPasajeros(Tren &tren)
{
    int opcion;

    do
    {
        cout << "\n========================================" << endl;
        cout << "    GESTIÓN DE PASAJEROS" << endl;
        cout << "========================================" << endl;
        cout << "1. Agregar Pasajero" << endl;
        cout << "2. Eliminar Pasajero" << endl;
        cout << "3. Mostrar Pasajeros" << endl;
        cout << "0. Volver" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            // Agregar pasajero al vagón actual
            {
                Vagon *vagonActual = tren.getVagonActual();
                if (vagonActual != nullptr)
                {
                    string nombre, cedula;
                    int asiento, lugarParadaId;

                    cout << "Ingrese el nombre del pasajero: ";
                    cin.ignore();
                    getline(cin, nombre);
                    cout << "Ingrese la cédula: ";
                    getline(cin, cedula);
                    cout << "Ingrese el número de asiento: ";
                    cin >> asiento;
                    cout << "Ingrese el ID del lugar de parada: ";
                    cin >> lugarParadaId;

                    vagonActual->agregarPasajeros(Pasajero(nombre, cedula, asiento, lugarParadaId), tren.getLugaresParada());
                }
                else
                {
                    cout << "No hay vagón actual para agregar pasajeros." << endl;
                }
            }
            break;
        case 2:
            // Eliminar pasajero por identificador
            {
                Vagon *vagonActual = tren.getVagonActual();
                if (vagonActual != nullptr)
                {
                    string cedula;
                    cout << "Ingrese el nombre del pasajero: ";
                    cin.ignore();
                    getline(cin, cedula);
                    vagonActual->eliminarPasajeros(cedula);
                }
                else
                {
                    cout << "No hay vagón actual." << endl;
                }
            }

            break;
        case 3:
            // Mostrar lista de pasajeros del vagón actual
            {
                Vagon *vagonActual = tren.getVagonActual();
                if (vagonActual != nullptr)
                {
                    cout << "Pasajeros en el vagón actual:" << endl;
                    vagonActual->mostrarPasajeros();
                }
                else
                {
                    cout << "No hay vagón actual." << endl;
                }
            }
            break;
        case 0:
            cout << "Volviendo..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);
}

void submenuAmenidades(Tren &tren)
{
    int opcion;

    do
    {
        cout << "\n========================================" << endl;
        cout << "    GESTIÓN DE AMENIDADES" << endl;
        cout << "========================================" << endl;
        cout << "1. Agregar Amenidad" << endl;
        cout << "2. Modificar Amenidad" << endl;
        cout << "3. Eliminar Amenidad" << endl;
        cout << "4. Mostrar Amenidades" << endl;
        cout << "0. Volver" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            Vagon *vagonActual = tren.getVagonActual();
            if (vagonActual != nullptr)
            {

                int cantidad, seleccion;

                cout << "Ingrese el numero de espacios/espacio: ";
                cin >> cantidad;

                cout << "===== Reporte de Amenidades Disponibles en el Tren =====" << endl;
                cout << "1. Cocinas" << endl;
                cout << "2. Baños" << endl;
                cout << "3. Asientos de Primera Clase" << endl;
                cout << "4. Asientos de Clase Turista" << endl;
                cout << "5. WiFi a bordo" << endl;
                cout << "6. Vagónes Restaurante" << endl;
                cout << "7. Espacios para Equipaje" << endl;
                cout << "========================================================" << endl;
                cout << "Seleccione una opción: ";

                cin >> seleccion;
                string nombre = vagonActual->selectAmenidad(seleccion);

                vagonActual->agregarAmenidad(Amenidad(nombre, cantidad));
            }
            else
            {
                cout << "No hay vagón actual." << endl;
            }
        }

        break;
        case 2:
        {
            Vagon *vagonActual = tren.getVagonActual();
            if (vagonActual != nullptr)
            {
                string nombreVerificar, nuevoNombre;
                int nuevaCantidad;

                cout << "Ingrese el nombre de la amenidad a modificar: ";
                cin.ignore();
                getline(cin, nombreVerificar);

                cout << "Ingrese el nuevo nombre de la amenidad: ";
                getline(cin, nuevoNombre);

                cout << "Ingrese la nueva cantidad: ";
                cin >> nuevaCantidad;

                if (vagonActual->modificarAmenidad(nombreVerificar, nuevoNombre, nuevaCantidad))
                    cout << "Amenidad modificada correctamente." << endl;
                else
                    cout << "La amenidad '" << nombreVerificar << "' no existe." << endl;
            }
            else
            {
                cout << "No hay vagón actual." << endl;
            }
        }
        break;
        case 3:
        {
            Vagon *vagonActual = tren.getVagonActual();
            if (vagonActual != nullptr)
            {
                string nombre;
                cout << "Ingrese el nombre de la amenidad: ";
                cin.ignore();
                getline(cin, nombre);

                vagonActual->eliminarAmenidad(nombre);
            }
            else
            {
                cout << "No hay vagón actual." << endl;
            }
        }
        break;
        case 4:

        {
            Vagon *vagonActual = tren.getVagonActual();
            if (vagonActual != nullptr)
            {

                vagonActual->mostrarListaAmenidades();
            }
            else
            {
                cout << "No hay vagón actual." << endl;
            }
        }

        break;
        case 0:
            cout << "Volviendo..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);
}

void submenuLugaresParada(Tren &tren)
{
    int opcion;

    do
    {
        cout << "\n========================================" << endl;
        cout << "    GESTIÓN DE LUGARES DE PARADA" << endl;
        cout << "========================================" << endl;
        cout << "1. Agregar Lugar" << endl;
        cout << "2. Eliminar Lugar" << endl;
        cout << "3. Mostrar Lugares" << endl;
        cout << "0. Volver" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            // Agregar lugar con ID único, inserción ordenada por ID
            {
                int id;
                string nombre;
                cout << "Ingrese el ID del lugar: ";
                cin >> id;
                cout << "Ingrese el nombre del lugar: ";
                cin.ignore();
                getline(cin, nombre);

                tren.insertarLugarParada(LugarParada(id, nombre));
            }
            break;
        case 2:
        {
            int id;
            cout << "Ingrese el ID del lugar que desea eliminar: ";
            cin >> id;
            tren.eliminarLugar(id);
        }
        break;
        case 3:
            // Mostrar lugares ordenados por ID y luego por nombre
            {
                tren.mostrarLugares();
            }
            break;
        case 0:
            cout << "Volviendo..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);
}

void menuReportes(Tren &tren)
{
    int opcion;

    do
    {
        cout << "\n===================================================" << endl;
        cout << "    GENERACIÓN DE REPORTES" << endl;
        cout << "===================================================" << endl;
        cout << "1. Reporte de Amenidades Totales por Tipo" << endl;
        cout << "2. Número Total de Pasajeros" << endl;
        cout << "3. Vagón con Más Pasajeros" << endl;
        cout << "4. Distribución de Pasajeros por Vagón" << endl;
        cout << "5. Reporte de Lugares de Parada" << endl;
        cout << "0. Volver al menú principal" << endl;
        cout << "===================================================" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            int eleccion;
            string name;

            tren.acumularAmenidades();
            tren.mostraMenuAmenidades();
    
            cin >> eleccion;

            tren.reporteAmenidades(eleccion);

            break; 
        }
        case 2:
            // Contar total de pasajeros en el tren

            break;
        case 3:
            // Identificar vagón con mayor número de pasajeros

            break;
        case 4:
            // Mostrar cantidad de pasajeros por vagón

            break;
        case 5:
            // Mostrar lugares de parada con cantidad de pasajeros

            break;
        case 0:
            cout << "Volviendo al menú principal..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);
}