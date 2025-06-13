#include "../includes/Operaciones.h"
#include <fstream>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

// Reemplaza comas por puntos (para poder usar stod con números decimales)
static string reemplazar_coma_por_punto(const string& texto) {
    string resultado = texto;
    replace(resultado.begin(), resultado.end(), ',', '.');
    return resultado;
}

vector<Venta> leer_csv(const string& path) {
    ifstream archivo(path);
    vector<Venta> ventas;
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir el archivo " << path << endl;
        return ventas;
    }

    getline(archivo, linea); // Saltear encabezado

    while (getline(archivo, linea)) {
        stringstream stream(linea);
        Venta v;
        string campo;

        try {
            getline(stream, v.id_venta, ',');
            getline(stream, v.fecha, ',');
            getline(stream, v.pais, ',');
            getline(stream, v.ciudad, ',');
            getline(stream, v.cliente, ',');
            getline(stream, v.producto, ',');
            getline(stream, v.categoria, ',');

            getline(stream, campo, ',');
            v.cantidad = stoi(campo);

            getline(stream, campo, ',');
            v.precio_unitario = stod(reemplazar_coma_por_punto(campo));

            getline(stream, campo, ',');
            v.monto_total = stod(reemplazar_coma_por_punto(campo));

            getline(stream, v.medio_envio, ',');
            getline(stream, v.estado_envio);

            ventas.push_back(v);
        } catch (const exception& e) {
            cerr << "Error al procesar línea:\n" << linea << "\nMotivo: " << e.what() << endl;
        }
    }

    archivo.close();
    return ventas;
}

void mostrar_ventas(const vector<Venta>& ventas, int max_mostrar) {
    for (int i = 0; i < ventas.size() && i < max_mostrar; ++i) {
        const Venta& v = ventas[i];
        cout << "==========================" << endl;
        cout << "ID Venta:        " << v.id_venta << endl;
        cout << "Fecha:           " << v.fecha << endl;
        cout << "País:            " << v.pais << endl;
        cout << "Ciudad:          " << v.ciudad << endl;
        cout << "Cliente:         " << v.cliente << endl;
        cout << "Producto:        " << v.producto << endl;
        cout << "Categoría:       " << v.categoria << endl;
        cout << "Cantidad:        " << v.cantidad << endl;
        cout << "Precio Unitario: $" << v.precio_unitario << endl;
        cout << "Monto Total:     $" << v.monto_total << endl;
        cout << "Medio de Envío:  " << v.medio_envio << endl;
        cout << "Estado Envío:    " << v.estado_envio << endl;
    }
}

void agregar_ventas (vector<Venta>& ventas) {
    string nuevo_id_venta,nuevo_fecha,nuevo_pais,nuevo_ciudad,nuevo_cliente,nuevo_producto,nuevo_categoria, nuevo_medio_envio, nuevo_estado_envio;
    int nuevo_cantidad;
    double nuevo_precio_unitario;
    double nuevo_monto_total;
    Venta nueva;                                 // ahora vamos a actualizar mi vector ventas de mi ventas.h para que al momento de imprimir este actualizado con la venta nueva


    cout << "Ingrese el ID de venta: "<<endl;
    cin >> nueva.id_venta;          // cargo en nueva.id_venta asi no manejo variables temporales y lo mando directamente a la base de datos
    cout << "Ingrese la fecha de la compra: "<<endl;
    cin >>nueva.fecha;
    cin.ignore();
    cout << "Ingrese el pais: "<<endl;
    getline(cin, nueva.pais);
    cout << "Ingrese la ciudad: "<<endl;
    getline (cin, nueva.ciudad);
    cout << "Ingrese el cliente: "<<endl;
    getline(cin, nueva.cliente);
    cout << "Ingrese el producto: "<<endl;
    getline(cin, nueva.producto);
    cout << "Ingrese la categoria: "<<endl;
    getline(cin, nueva.categoria);
    cout << "Ingrese la cantidad: "<<endl;
    cin >> nueva.cantidad;
    cout << "Ingrese el Precio Unitario: "<<endl;
    cin >> nueva.precio_unitario;
    cout << "Ingrese el monto total: "<<endl;
    cin >> nueva.monto_total;
    cin.ignore();
    cout << "ingrese el medio de envio: "<<endl;
    getline(cin,nueva.medio_envio);
    cout << "ingrese el estado del envio: "<<endl;
    getline(cin, nueva.estado_envio);


    ofstream archivo("data/ventas_sudamerica.csv", ios::app);
    if (archivo.fail()) {                                                               // usamos fail porque comprueba si se abre bien el archivo como is_open pero tambien chequea que se escriba correctamente
        cout << "error al intentar escribir en el archivo. ";
        exit(1);
    }

    archivo << nueva.id_venta << ","
            << nueva.fecha << ","
            << nueva.pais << ","
            << nueva.ciudad << ","
            <<nueva.cliente << ","
            <<nueva.producto << ","
            <<nueva.categoria << ","
            <<nueva.cantidad << ","
            <<nueva.precio_unitario << ","
            <<nueva.monto_total << ","
            <<nueva.medio_envio << ","
            <<nueva.estado_envio << "\n";

    archivo.close();
    ventas.push_back(nueva);    // Pusheo a la base de datos los nuevos registros sin manejo de errores porque no falla nunca, solo si no tenes suficiente ram.
    cout << "La venta se agrego correctamente y se actualizo la base de datos!." << endl;

    cout << "\n📦 Última venta registrada:\n";
    const Venta& v = ventas.back();
    cout << "Producto: " << v.producto << " | Cliente: " << v.cliente << endl;

}
void modificar_venta(vector<Venta>& ventas) {
    unordered_map<string, int> mapa_indices;

    // Mapear ID_Venta a su posición en el vector
    for (int i = 0; i < ventas.size(); ++i) {
        mapa_indices[ventas[i].id_venta] = i;
    }

    cout << "Ingrese el ID de la venta a modificar: ";
    string id;
    cin >> id;

    if (mapa_indices.find(id) == mapa_indices.end()) {
        cout << "No se encontró ninguna venta con ese ID." << endl;
        return;
    }

    int idx = mapa_indices[id];
    Venta &venta = ventas[idx];

    // Mostrar los campos actuales
    cout << "\n📄 Campos actuales de la venta:\n";
    mostrar_ventas({venta}, 1);

    // Menú de edición (recursivo simple)
    function<void()> editar = [&]() {
        int opcion;
        cout << "\n¿Qué campo desea modificar?\n";
        cout
                << "1. Fecha\n2. País\n3. Ciudad\n4. Cliente\n5. Producto\n6. Categoría\n7. Cantidad\n8. Precio Unitario\n9. Monto Total\n10. Medio de Envío\n11. Estado de Envío\n0. Finalizar\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore(); // limpiar buffer

        switch (opcion) {
            case 1:
                cout << "Nueva fecha: ";
                getline(cin, venta.fecha);
                break;
            case 2:
                cout << "Nuevo país: ";
                getline(cin, venta.pais);
                break;
            case 3:
                cout << "Nueva ciudad: ";
                getline(cin, venta.ciudad);
                break;
            case 4:
                cout << "Nuevo cliente: ";
                getline(cin, venta.cliente);
                break;
            case 5:
                cout << "Nuevo producto: ";
                getline(cin, venta.producto);
                break;
            case 6:
                cout << "Nueva categoría: ";
                getline(cin, venta.categoria);
                break;
            case 7:
                cout << "Nueva cantidad: ";
                cin >> venta.cantidad;
                cin.ignore();
                break;
            case 8:
                cout << "Nuevo precio unitario: ";
                cin >> venta.precio_unitario;
                cin.ignore();
                break;
            case 9:
                cout << "Nuevo monto total: ";
                cin >> venta.monto_total;
                cin.ignore();
                break;
            case 10:
                cout << "Nuevo medio de envío: ";
                getline(cin, venta.medio_envio);
                break;
            case 11:
                cout << "Nuevo estado de envío: ";
                getline(cin, venta.estado_envio);
                break;
            case 0:
                return;
            default:
                cout << "⚠️ Opción inválida.\n";
                break;
        }
        editar(); // llamada recursiva
    };

    editar();

    // Reescribir el archivo CSV
    ofstream archivo("data/ventas_sudamerica.csv");
    if (!archivo) {
        cout << "Error al abrir el archivo para escribir." << endl;
        return;
    }

    // Escribir encabezado
    archivo
            << "ID_Venta,Fecha,Pais,Ciudad,Cliente,Producto,Categoria,Cantidad,Precio_Unitario,Monto_Total,Medio_Envio,Estado_Envio\n";
    for (const auto &v: ventas) {
        archivo << v.id_venta << "," << v.fecha << "," << v.pais << "," << v.ciudad << "," << v.cliente << ","
                << v.producto << "," << v.categoria << "," << v.cantidad << "," << v.precio_unitario << ","
                << v.monto_total << "," << v.medio_envio << "," << v.estado_envio << "\n";
    }

    archivo.close();
    cout << "Venta modificada exitosamente." << endl;

}

void listar_ventas_por_ciudad(const vector<Venta>& ventas) {
    cout << "Ingrese la ciudad a buscar: ";
    string ciudad;
    cin.ignore();
    getline(cin, ciudad);

    cout << "\nVentas realizadas en la ciudad '" << ciudad << "':\n";
    bool encontrada = false;

    for (const auto& v : ventas) {
        if (v.ciudad == ciudad) {
            mostrar_ventas({v}, 1);
            encontrada = true;
        }
    }
    if (!encontrada) {
        cout << "No se encontraron ventas en esa ciudad." << endl;
    }
}

void listar_ventas_por_pais_rango_fechas(const vector<Venta>& ventas) {
    cout << "Ingrese el país a buscar: ";
    string pais;
    cin.ignore();
    getline(cin, pais);

    string fecha_inicio, fecha_fin;
    cout << "Ingrese la fecha inicial (dd/mm/yyyy): ";
    getline(cin, fecha_inicio);
    cout << "Ingrese la fecha final (dd/mm/yyyy): ";
    getline(cin, fecha_fin);

    cout << "\nVentas en '" << pais << "' desde " << fecha_inicio << " hasta " << fecha_fin << ":\n";

    bool encontrada = false;

    for (const auto& v : ventas) {
        if (v.pais == pais && v.fecha >= fecha_inicio && v.fecha <= fecha_fin) {
            mostrar_ventas({v}, 1);
            encontrada = true;
        }
    }
    if (!encontrada) {
        cout << "No se encontraron ventas para ese país en ese rango de fechas." << endl;
    }
}


int menu () {
    int opcion_menu;
    cout << "========= MENÚ PRINCIPAL ========="<<endl;
    cout << "1. Mostrar todas las ventas"<<endl;
    cout << "2. Agregar una nueva venta"<<endl;
    cout << "3. Eliminar una venta"<<endl;
    cout << "4. Modificar una venta"<<endl;
    cout << "5. Estadísticas generales (procesamiento del punto 5)"<<endl;
    cout << "6. Consultas dinámicas (punto 7)"<<endl;
    cout << "0. Salir"<<endl;
    cout << "================================="<<endl;
    cout << "Ingrese una opción:";
    cin >> opcion_menu;
    return opcion_menu;

}