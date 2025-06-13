#include "../includes/Operaciones.h"
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Reemplaza comas por puntos (para poder usar stod con números decimales)
static string reemplazar_coma_por_punto(const string& texto) {
    string resultado = texto;
    replace(resultado.begin(), resultado.end(), ',', '.');
    return resultado;
}

bool buscar_en_indice(const unordered_map<string, int>& indice, const string& id, int& posicion) {
    auto it = indice.find(id);
    if (it != indice.end()) {
        posicion = it->second;
        return true;
    }
    return false;
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

void eliminar_ventas(vector<Venta>& ventas, unordered_map<string, int>& indice) {
    string id;
    cout << "Ingrese el ID de la venta a eliminar: ";
    cin >> id;

    int pos;
    if (buscar_en_indice(indice, id, pos)) {
        ventas.erase(ventas.begin() + pos);  // borrás la venta del vector

        // reconstruís el índice
        indice.clear();
        for (int i = 0; i < ventas.size(); ++i)
            indice[ventas[i].id_venta] = i;

        cout << "✅ Venta eliminada correctamente.\n";
        // (opcional) reescribir el CSV si querés persistir
    } else {
        cout << "❌ No se encontró ninguna venta con ese ID.\n";
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