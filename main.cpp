#include "includes/Operaciones.h"
#include <iostream>
using namespace std;

void mostrar_ventas(const vector<Venta>& ventas, int max_mostrar = 20) {
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

int main() {
    string archivo = "data/ventas_sudamerica.csv";
    vector<Venta> ventas = leer_csv(archivo);

    if (ventas.empty()) {
        cout << "No se pudieron cargar ventas." << endl;
    } else {
        cout << "Se cargaron " << ventas.size() << " ventas correctamente.\n";
        mostrar_ventas(ventas);
    }

    return 0;
}
