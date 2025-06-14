#ifndef VENTAS_H
#define VENTAS_H

#include <string>
using namespace std;


/**
 * @brief struct de Ventas
 *
 */
struct Venta {
    string id_venta;
    string fecha;
    string pais;
    string ciudad;
    string cliente;
    string producto;
    string categoria;
    int cantidad;
    double precio_unitario;
    double monto_total;
    string medio_envio;
    string estado_envio;
};

#endif
