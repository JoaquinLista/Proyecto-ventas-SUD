#include "../includes/Operaciones.h"
#include <fstream>
#include <sstream>
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
