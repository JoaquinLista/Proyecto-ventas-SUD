//
// Created by Joako on 26/05/2025.
//

#include "Procesamiento.h"
using namespace std;





void listar_ventas(const vector<Venta>& ventas) {
    for (const auto& v : ventas) {
        cout << "==================" << endl;
        cout << "ID Venta: " << v.id_venta << endl;
        cout << "Fecha: " << v.fecha << endl;
        cout << "País: " << v.pais << endl;
        cout << "Ciudad: " << v.ciudad << endl;
        cout << "Cliente: " << v.cliente << endl;
        cout << "Producto: " << v.producto << endl;
        cout << "Categoría: " << v.categoria << endl;
        cout << "Cantidad: " << v.cantidad << endl;
        cout << "Precio unitario: $" << v.precio_unitario << endl;
        cout << "Monto total: $" << v.monto_total << endl;
        cout << "Medio de envío: " << v.medio_envio << endl;
        cout << "Estado de envío: " << v.estado_envio << endl;
    }
}
